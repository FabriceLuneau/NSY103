#include <stdbool.h>

#include <stdio.h>
#include "spectacle.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "request.h"
#include "response.h"

/*
Version question 1 avec tubes anonymes
*/

int main(int argc, char** argv)
{
    // initialisation des données
    //le tableau des spectacles sera dupliquéd dans chaque processus
    initTabSpectacles();

    // déclaration des tubes
    //on se place cote serveur pour les noms
    int outcoming[2];
    if (pipe(outcoming) == -1) {
        perror("pipe outcoming failed");
        return errno;
    }

    int incoming[2];
    if (pipe(incoming) == -1) {
        perror("pipe incoming failed");
        return errno;
    }

    // création du processus enfant
    pid_t res = fork();
    if (res == -1) {
        perror("fork failed");
        return errno;
    }

    /* ===================== CLIENT ===================== */
    if (res == 0)
    {
        printf("Lancement du processus client PID=%d\n", getpid());

        // fermeture des descripteurs inutiles
        close(incoming[0]);   // lecture serveur
        close(outcoming[1]);  // écriture serveur

//valeur impossible
        int specSelect = -1;
        //valeur de choix impossible pour lancer la boucle
        int choix = -1;

        while (choix != 0) {

            struct request req;

            printf("\nMenu\n");
            if (specSelect != -1)
            {
                printf("Spectacle selectionne: %d %s (%d places)\n",
                       specSelect,
                       tabSpectacles[specSelect].intitule,
                       tabSpectacles[specSelect].nbPlaces);
            } else {
                printf("Pas de spectacle selectionne\n");
            }

            printf("1 Selectionner un spectacle\n");
            printf("2 Afficher les spectacles\n");
            if (specSelect != 9999)
            {
                printf("3 Retirer des places\n");
            }

            printf("0 Quitter\n");

            printf("Entrez votre choix: ");
            scanf("%d", &choix);

            switch (choix)
            {
                case 1: {
                    int id;
                    printf("Entrez l'id du spectacle: ");
                    scanf("%d", &id);
                    specSelect = id;
                    break;
                }

                case 2:
                    afficherTabSpectacles();
                    break;

                case 3:
                    if (specSelect != -1) {
                        int nbPlaces;
                        printf("Entrez le nombre de places: ");
                        scanf("%d", &nbPlaces);

                        req.idSpectacle = specSelect;
                        req.nbPlaces = nbPlaces;

                        write(incoming[1], &req, sizeof(req));

                        bool resultat;
                        read(outcoming[0], &resultat, sizeof(resultat));

                        if (resultat)
                        {
                            printf("Reservation effectuee avec succes\n");
                            retirerPlaces(specSelect, nbPlaces); // synchro locale
                        }
                        else
                        {
                            printf("Echec: places insuffisantes\n");
                        }
                    }
                    break;

                case 0:
                    //avant de quitter on ferme les descripteurs, cela se répercute sur le serveur qui n'a plus de lecteurs pour son tube
                    close(incoming[1]);
                    close(outcoming[0]);
                    return 0;

                default:
                    printf("Operation non supportee\n");
            }
        }
    }

    /* ===================== SERVEUR ===================== */
    else
    {

        // redirection sortie serveur vers server.log
        int logfd = open("server.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (logfd == -1) {
            perror("open server.log failed");
            exit(EXIT_FAILURE);
        }
        dup2(logfd, STDOUT_FILENO);
        dup2(logfd, STDERR_FILENO);
        close(logfd);

        printf("Serveur demarre PID=%d\n", getpid());

        // fermeture des descripteurs inutiles
        close(incoming[1]);   // écriture client
        close(outcoming[0]);  // lecture client

        while (1)
        {
            struct request req;
            ssize_t n = read(incoming[0], &req, sizeof(req));

            if (n <= 0)
            {
                printf("Client deconnecte, arret du serveur\n");
                break;
            }

            printf("Requete recue: spectacle=%d, nbPlaces=%d\n",
                   req.idSpectacle, req.nbPlaces);

            bool ok = retirerPlaces(req.idSpectacle, req.nbPlaces);

            printf("Resultat traitement: %s\n", ok ? "SUCCESS" : "FAIL");

            write(outcoming[1], &ok, sizeof(ok));
        }
    }

    return 0;
}


******


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


********

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
