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

    if (pipe(outcoming) == -1)
    {
        perror("pipe outcoming failed");
        return errno;
    }

    if (pipe(incoming) == -1)
    {
        perror("pipe incoming failed");
        return errno;
    }

    /* création du processus enfant */
    // pid_t res = fork();
    int res = fork();
    if (res == -1)
    {
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
        // struct spectacle tabSpectacleClient[10];
        // size_t capacite = 10;

        // spectacle_initialiser(tabSpectacleClient, capacite);
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

            if (specSelect != -1)
            {
                printf("Spectacle selectionne: %d %s (%d places)\n",
                       specSelect,

                       tabSpectaclesGlobal[specSelect].intitule,
                       tabSpectaclesGlobal[specSelect].nbPlaces);
            }
            else
            {
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
            case 1:
            {
                printf("Entrez l'id du spectacle: ");
                scanf("%d", &specSelect);
                break;
            }

            case 2:
                spectacle_afficherTout();
                // tabSpectacles,
                ////spectacle_compter(tabSpectacleClient, capacite)
                //);
                break;

            case 3:
                if (specSelect != -1)
                {
                    int nbPlaces;
                    printf("Entrez le nombre de places: ");
                    scanf("%d", &nbPlaces);
                    
                    request_createDepuisChaine("getSpectacles",& req);(&req, specSelect, nbPlaces);
                    write(incoming[1], &req, sizeof(req));

                    read(outcoming[0], &resp, sizeof(resp));

                    if (resp.code == 201)
                    {
                        printf("Reservation effectuee avec succes\n");
                        spectacle_retirerPlaces(specSelect, nbPlaces);
                    }
                    else if (resp.code == 401)
                    {
                        printf("Echec: places insuffisantes\n");
                    }
                    else if (resp.code == 404)
                    {
                        printf("Echec: spectacle non trouve\n");
                    }
                    else
                    {
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
        if (logfd == -1)
        {
            perror("open server.log failed");
            exit(EXIT_FAILURE);
        }
        dup2(logfd, STDOUT_FILENO);
        dup2(logfd, STDERR_FILENO);
        close(logfd);

        printf("Serveur demarre PID=%d\n", getpid());

        /* tableau local serveur */
        // struct spectacle tabSpectacleServeur[10];
        // size_t capacite = 10;
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

            //teste de l'action et branchement surle traitement
            //retourne tous les spectacles
            if (strcmp(req.action, "getSpectacles") == 0)
            {
                response_init(&resp, 200);
                bridge_encodeSpectaclesResponse(
                    &resp,
                    tabSpectaclesGlobal,
//spectacle_getTailleTableauGlobal
                );
            }
            //retourne un spectacle as            //else if (strcmp(req.action, "getSpectacle") == 0)
            //{
                //int id = request_getId(&req);
                //struct spectacle spec = tabSpectaclesGlobal[id];

                //response_init(&resp, 200);
                //bridge_encodeUnSpectacleResponse(
                    //&resp,
                    //spec);
            //}
            //retirer des place si disponible
            else if(strcmp(req.action, "reserver") == 0)
            {
                int id = request_getId(&req);
                int nbPlaces = request_getNbPlaces(&req);
                
                    //si le spectacle n'existe pas on sort
//                    //todo il n'ya pas de fonction pour tester l'id si le spectacle existe ap
                    //if(spectacle_exists(id)) 
                   //{
                        //response_init(&resp, 404201);
                                            //}
                    //si il n'y a pas asse de places
                    //todo penser à ajouter le elseif en dessous lors de l'intégration
                    if(!spectacle_quantiteEstDisponible(id, nbPlaces) )
                        {
response_init(&resp, 401);
                        } 
                        else {
                            spectacle_retirerPlaces(id, nbPlaces);

                    response_init(&resp, 201);
                        }
                    
                    //si on est là l'action est

                    //fin des testdes actions

   //affichagee pour toutes les responses
                    response_afficher(&resp);

            write(outcoming[1], &resp, sizeof(resp));
        }
    }
}

    return 0;
}
