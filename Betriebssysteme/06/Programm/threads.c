#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "threads.h"
#include "miniz.h"

const char ext[] = "compr";

void *readerThread(void *arguments)
{

    ReaderArgs *args = (ReaderArgs *)arguments;
    MutexQueue *queue = args->queue;

    printf("Reader Thread gestartet\n");

    struct dirent *dir;
    while ((dir = readdir(args->directory)) != NULL)
    {

        struct stat path_stat;
        char *fullPath = getFullPath(args->basename, dir->d_name);
        stat(fullPath, &path_stat);
        /* Nur für reguläre und unkomprimierte Dateien */
        if ((S_ISREG(path_stat.st_mode) != 0) && (strcmp(get_filename_ext(fullPath), ext) != 0))
        {

            printf("readerThread: Bearbeite %s\n", dir->d_name);

            /* Job erstellen */
            Job *job = malloc(sizeof(Job));
            if (!job)
            {
                printf("readerThread: Fehler beim Speicherallozieren\n");
                exit(EXIT_FAILURE);
            }
            job->path = strdup(fullPath);
            job->content = get_file_content(fullPath);

            /* Sperre holen */
            if (pthread_mutex_lock(queue->mutex))
            {
                perror("Queue konnte nicht gesperrt werden");
                return NULL;
            }

            /* Job kann hinzugefügt werden */
            if (!(queue_insert(queue->queue, job)))
            {
                printf("readerThread: Konnte Job nicht zu Queue hinzufügen\n");
            }
            queue->empty = 0;

            /* Aufheben der Sperre*/
            if (pthread_mutex_unlock(queue->mutex))
            {
                perror("Fehler beim Entsperren der Queue");
                return NULL;
            }

            /* Senden des Signals */
            if (pthread_cond_signal(queue->notEmpty))
            {
                perror("Fehler beim Senden eines Signals: ");
            }
        }

        free(fullPath);

        /* Nur zum Testen Anfang */
        while (!queue_empty(queue->queue))
        {
            Job *test = queue_head(queue->queue);
            printf("%s\n", test->path);
            queue_delete(queue->queue);
        }
        /* Nur zum Testen Ende */
    }

    void deleteJob(Job * job)
    {
        free(job->path);
        free(job->content);
        free(job);
    }

    // TODO: Diese beiden Methoden könnte man eventuell auslagern...
    char *getFullPath(const char *base, const char *name)
    {
        char *realBase = realpath(base, NULL);
        char *fullPath = malloc(strlen(realBase) + strlen(name) + 2);
        if (!fullPath)
        {
            printf("Fehler beim Holen des Speichers\n");
            exit(EXIT_FAILURE);
        }

        strcpy(fullPath, realBase);
        strcat(fullPath, "/");
        strcat(fullPath, name);
        free(realBase);
    }

    return fullPath;
}

char *get_file_content(const char *filename)
{

    char *buffer = "";

    /* Öffne Datei zum Lesen */
    FILE *infile = fopen(filename, "r");

    /* Abbruch, falls Datei nicht existiert */
    if (infile == NULL)
    {
        perror("Fehler beim Lesen der Datei: ");
        return buffer;
    }

    /* Suche Dateiender */
    if (fseek(infile, 0, SEEK_END))
    {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Länge der Datei*/
    long length = ftell(infile);
    if (length < 0)
    {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Zurück zum Anfang */
    if (fseek(infile, 0, SEEK_SET))
    {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Datei einlesen */
    buffer = malloc(length);
    if (buffer)
    {
        fread(buffer, 1, length, infile);
    }
    else
    {
        perror("Fehler beim Lesen der Datei: ");
    }

    /* Datei schließen */
    fclose(infile);

    /* Rückgabe */
    return buffer;
}

char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}