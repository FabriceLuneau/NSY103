#include <stdbool.h>
#include <stdio.h>
#include "spectacle.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "request.h"
#include "response.h"

/*
Version client avec tubes nommés (FIFO)
*/

#define FIFO_IN  "incoming.fifo"
#define FIFO_OUT "outcoming.fifo"

int main(void)
{
    init();

    /* création des FIFO si absents */
    if (mkfifo(FIFO_IN, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo incoming");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_OUT, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo outcoming");
        exit(EXIT_FAILURE);
    }

    printf("Client demarre PID=%d\n", getpid());

    /* ouverture des FIFO */
    int fd_out = open(FIFO_IN, O_WRONLY);
    if (fd_out == -1) {
        perror("open FIFO_IN");
        exit(EXIT_FAILURE);
    }

    int fd_in = open(FIFO_OUT, O_RDONLY);
    if (fd_in == -1) {
        perror("open FIFO_OUT");
        exit(EXIT_FAILURE);
    }

    int specSelect = -1;
    int choix = 99;

    while (choix != 0) {
        struct request req;
        struct response resp;

        printf("\nMenu\n");

        if (specSelect >= 0) {
            printf("Spectacle selectionne: %d %s (%d places)\n",
                   specSelect,
                   tabSpectacles[specSelect].intitule,
                   tabSpectacles[specSelect].nbPlaces);
        } else {
            printf("Pas de spectacle selectionne\n");
        }

        printf("1 Selectionner un spectacle\n");
        printf("2 Afficher les spectacles\n");
        if (specSelect >= 0) {
            printf("3 Retirer des places\n");
        }
        printf("0 Quitter\n");

        printf("Choix: ");
        scanf("%d", &choix);

        switch (choix) {

            case 1: {
                printf("Id du spectacle: ");
                scanf("%d", &specSelect);
                break;
            }

            case 2:
                afficher();
                break;

            case 3:
                if (specSelect >= 0) {
                    int nb;
                    printf("Nombre de places: ");
                    scanf("%d", &nb);

                    req.idSpectacle = specSelect;
                    req.nbPlaces = nb;

                    if (write(fd_out, &req, sizeof(req)) != sizeof(req)) {
                        perror("write request");
                        break;
                    }

                    if (read(fd_in, &resp, sizeof(resp)) != sizeof(resp)) {
                        perror("read response");
                        break;
                    }

                    if (resp.success) {
                        printf("Reservation OK\n");
                        retirerPlaces(specSelect, nb); // synchro locale
                    } else {
                        printf("Echec: places insuffisantes ou id invalide\n");
                    }
                }
                break;

            case 0:
                printf("Client termine\n");
                close(fd_out);
                close(fd_in);
                return 0;

            default:
                printf("Choix invalide\n");
        }
    }

    return 0;
}
