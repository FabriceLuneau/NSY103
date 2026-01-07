#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "spectacle.h"
#include "request.h"
#include "response.h"
#include "bridge.h"

/*
 * Version question 1 avec tubes anonymes
 */
int main(int argc, char **argv)
{
    /* ================= INITIALISATION ================= */

    /* déclaration des tubes */
    int outcoming[2]; /* serveur -> client */
/* client -> serveur */
    int incoming[2]; 

    if (pipe(outcoming) == -1) {
        perror("pipe outcoming failed");
        return errno;
    }

    if (pipe(incoming) == -1) {
        perror("pipe incoming failed");
        return errno;
    }

    /* création du processus enfant */
    //pid_t res = fork();
    int res = fork();
    if (res == -1) {
        perror("fork failed");
        return errno;
    }

    /* ==================================================
     * ===================== CLIENT =====================
     * ================================================== */
    if (res == 0)
    {
        printf("Lancement du processus client PID=%d\n", getpid());

        /* tableau local client */
        //struct spectacle tabSpectacleClient[10];
        //size_t capacite = 10;

        //spectacle_initialiser(tabSpectacleClient, capacite);
        spectacle_initTabGlobal();
        
        /* fermeture des descripteurs inutiles côté client */
        /* lecture serveur */
close(incoming[0]);   
/* écriture serveur */
close(outcoming[1]);  

        int specSelect = -1;
        int choix = -1;

        while (choix != 0)
        {
            struct request req;
            struct response resp;

            printf("\nMenu\n");

            if (specSelect != -1) {
                printf("Spectacle selectionne: %d %s (%d places)\n",
                       specSelect,
                       
                       tabSpectacles[specSelect].intitule,
                       tabSpectacles[specSelect].nbPlaces);
            } else {
                printf("Pas de spectacle selectionne\n");
            }

            printf("1 Selectionner un spectacle\n");
            printf("2 Afficher les spectacles\n");
            if (specSelect != -1)
                printf("3 Retirer des places\n");
            printf("0 Quitter\n");

            printf("Entrez votre choix: ");
            scanf("%d", &choix);

            switch (choix)
            {
            case 1: {
                printf("Entrez l'id du spectacle: ");
                scanf("%d", &specSelect);
                break;
            }

            case 2:
                spectacle_afficher();
                    //tabSpectacles,
                    ////spectacle_compter(tabSpectacleClient, capacite)
                //);
                break;

            case 3:
                if (specSelect != -1) {
                    int nbPlaces;
                    printf("Entrez le nombre de places: ");
                    scanf("%d", &nbPlaces);

                    request_createReserver(&req, specSelect, nbPlaces);
                    write(incoming[1], &req, sizeof(req));

                    read(outcoming[0], &resp, sizeof(resp));

                    if (resp.code == 201) 
                    {
                        printf("Reservation effectuee avec succes\n");
                        spectacle_reserver(specSelect, nbPlaces);
                    } else if (resp.code == 401) {
                        printf("Echec: places insuffisantes\n");
                    } else if (resp.code == 404) {
                        printf("Echec: spectacle non trouve\n");
                    } else {
                        printf("Erreur inconnue\n");
                    }
                }
                break;

            case 0:
                close(incoming[1]);
                close(outcoming[0]);

                return 0;
            default:
                printf("Operation non supportee\n");
            }
        }
    }

    /* ==================================================
     * ===================== SERVEUR ====================
     * ================================================== */
    else
    {
        /* redirection sortie serveur vers server.log */
        int logfd = open("server.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (logfd == -1) {
            perror("open server.log failed");
            exit(EXIT_FAILURE);
        }
        dup2(logfd, STDOUT_FILENO);
        dup2(logfd, STDERR_FILENO);
        close(logfd);

        printf("Serveur demarre PID=%d\n", getpid());

        /* tableau local serveur */
        //struct spectacle tabSpectacleServeur[10];
        //size_t capacite = 10;
        spectacle_initTabGlobal();

        /* fermeture des descripteurs inutiles côté serveur */
        close(incoming[1]);
        close(outcoming[0]);

        while (1)
        {
            struct request req;
            struct response resp;

            ssize_t n = read(incoming[0], &req, sizeof(req));

            if (n <= 0) 
            {
                printf("Client deconnecte, arret du serveur\n");
                break;
            }

            request_afficher(&req);

            if (strcmp(req.action, "getSpectacles") == 0) {
                response_init(&resp, 200);
                bridge_encodeSpectaclesResponse(
                    &resp,
                    tabSpectacles, spectacle_getTailleTableauGlobal
                );
            }
            else if (strcmp(req.action, "getSpectacle") == 0) {
                int id = request_getId(&req);
                struct spectacle spec =  tabSpectacles[id];
                response_init(&resp, 200);
                bridge_encodeUnSpectacleResponse(
                    &resp,
                    spec
                );
            }
            else if (strcmp(req.action, "reserver") == 0) 
            {
                int id = request_getId(&req);
                int nbPlaces = request_getNbPlaces(&req);

                int r = spectacle_reserver(
                    tabSpectacles,
                    spectacle_getTailleTableauGlobal,
                    id
                );

                if (r == 0)
                    response_init(&resp, 201);
                else if (r == -1)
                    response_init(&resp, 404);
                else
                    response_init(&resp, 401);
            }
            else 
            {
                response_init(&resp, 400);
            }

            response_afficher(&resp);
            write(outcoming[1], &resp, sizeof(resp));
        }
    }

    return 0;
}



