#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>

#include "queue.h"
#include "threads.h"

const unsigned int NTHREADS = 4;


int main(int argc, char *argv[]) {

    /* Anzahl der Argumente testen */
    if( argc < 2 ) {
        printf("Kein Pfad angegeben! - ./main <Pfad>\n");
        return EXIT_SUCCESS;
    }

    DIR *directory = opendir(argv[1]);

    if (directory) {
        MutexQueue *queue = mutexQueueInit();

        /* Starte Zeitmessung */
        time_t start_t, end_t;
        double diff_t;
        time(&start_t);

        /* Reader Thread */
        pthread_t reader;
        ReaderArgs readerArgs;
        readerArgs.directory = directory;
        readerArgs.basename = argv[1];
        readerArgs.queue = queue;
        if (pthread_create(&reader, NULL, readerThread, &readerArgs)) {
            perror("Reader Thread konnte nicht erzeugt werden");
        }



        /* Warten auf Ende des Readerthreads */
        pthread_join(reader, NULL);
        printf("Alle Threads beendet.\n");


        /* Ende Zeitmessung */
        time(&end_t);
        diff_t = difftime(end_t, start_t);
        printf("Laufzeit war: %f\n", diff_t);

        /* Speicher freigeben */
        Cleanup(queue);

    } else if (ENOENT == errno) {
        perror("Das Verzeichnis existiert nicht");
        return EXIT_FAILURE;
    } else {
        perror("Verzeichnis konnte nicht geöffnet werden");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}