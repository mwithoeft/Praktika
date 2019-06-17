#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "main.h"
#include "methods.h"

int main(int argc, char *argv[])
{

    /* Anzahl der Argumente testen */
    if (argc < 3)
    {
        char *usage = "Nutzung: ./main <Quelle> <Ziel>\n";
        if (write(IOOUT, usage, strlen(usage)) != strlen(usage))
        {
            char *error = "Fehler bei der Ausgabe\n";
            write(IOERR, error, strlen(error));
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    /* Öffnen der Eingabe-Datei */
    char *src = argv[1];
    int filedescriptor_in = open(src, O_RDONLY);
    if (filedescriptor_in < -1)
    {
        char *error = "Datei konnte nicht geöffnet werden\n";
        write(IOERR, error, strlen(error));
        return EXIT_FAILURE;
    }

    printSecondHalfPrintFirstHalf(filedescriptor_in);

    /* Öffnen der Ausgabe-Datei */
    char *dest = argv[2];
    int filedescriptor_out = open(dest, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (filedescriptor_out < -1)
    {
        char *error = "Datei konnte nicht geöffnet werden\n";
        write(IOERR, error, strlen(error));
        return EXIT_FAILURE;
    }

    /* Schließen der Eingabe-Datei */
    if (close(filedescriptor_in))
    {
        char *error = "Eingabe-Datei konnte nicht geschlossen werden\n";
        write(IOERR, error, strlen(error));
        return EXIT_FAILURE;
    }
    /*  Schließen der Ausgabe-Datei */
    if (close(filedescriptor_out))
    {
        char *error = "Ausgabe-Datei konnte nicht geschlossen werden\n";
        write(IOERR, error, strlen(error));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
