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

    printf("Client FIFO démarré (PID=%d)\n", getpid());

    int specSelect = -1;
    int choix = -1;

    while (choix != 0)
    {
        printf("\nMenu\n");

        if (specSelect >= 0)
        {
            printf("Spectacle sélectionné : %d %s (%d places)\n",
                   specSelect,
                   tabSpectacles[specSelect].intitule,
                   tabSpectacles[specSelect].nbPlaces);
        }
        else
        {
            printf("Aucun spectacle sélectionné\n");
        }

        printf("1 - Sélectionner un spectacle\n");
        printf("2 - Afficher les spectacles\n");

        if (specSelect >= 0)
        {
            printf("3 - Réserver des places\n");
        }
        printf("0 - Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Id du spectacle : ");
            scanf("%d", &specSelect);
            break;
        case 2:
            afficherTabSpectacles();
            break;
        case 3:
            if (specSelect >= 0)
            {
                struct request req;
                int nbPlaces;

                printf("Nombre de places : ");
                scanf("%d", &nbPlaces);

                req.idSpectacle = specSelect;
                req.nbPlaces = nbPlaces;

                /* Envoi requête */
                int fd_out = open(FIFO_IN, O_WRONLY);

                if (fd_out == -1)
                {
                    perror("open FIFO_IN");
                    break;
                }

                write(fd_out, &req, sizeof(req));
                close(fd_out);

                /* Lecture réponse */
                bool resultat;
                int fd_in = open(FIFO_OUT, O_RDONLY);
                if (fd_in == -1) {
                    perror("open FIFO_OUT");
                    break;
                }

                read(fd_in, &resultat, sizeof(resultat));

                close(fd_in);

                if (resultat)
                {
                    printf("Réservation réussie\n");
                    retirerPlaces(specSelect, nbPlaces); // synchro locale
                }
                else
                {
                    printf("Échec : places insuffisantes\n");
                }
            }
            break;
        case 0:
            printf("Fin du client\n");
            break;
        default:
            printf("Choix invalide\n");
        }
    }

    return 0;
}
