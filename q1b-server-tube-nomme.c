
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "spectacle.h"
#include "request.h"
#include "response.h"
#include "fifo.h"

int main(void)
{
    initTabSpectacles();

    /* Création des FIFO (si inexistantes) */
    if (mkfifo(FIFO_IN, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo_in");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_OUT, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo_out");
        exit(EXIT_FAILURE);
    }

    printf("Serveur FIFO démarré (PID=%d)\n", getpid());

    while (1)
    {
        /* 1. Attente requête client */
        int fd_in = open(FIFO_IN, O_RDONLY);

        if (fd_in == -1) {
            perror("open FIFO_IN");
            continue;
        }

        struct request req;
        ssize_t n = read(fd_in, &req, sizeof(req));

        close(fd_in);

        if (n != sizeof(req))
        {
            printf("Client déconnecté\n");
            continue;
        }

        printf("Requête reçue : spectacle=%d, nbPlaces=%d\n",
               req.idSpectacle, req.nbPlaces);

        /* 2. Traitement */
        bool ok = retirerPlaces(req.idSpectacle, req.nbPlaces);

        printf("Résultat : %s\n", ok ? "SUCCESS" : "FAIL");

        /* 3. Réponse au client */
        int fd_out = open(FIFO_OUT, O_WRONLY);

        if (fd_out == -1)
        {
            perror("open FIFO_OUT");
            continue;
        }

        write(fd_out, &ok, sizeof(ok));
        close(fd_out);
    }

    return 0;
}
