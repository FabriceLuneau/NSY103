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

