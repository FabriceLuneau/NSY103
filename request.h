#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <string.h>
#include "cleValeur.h"

/*
 * Requête client
 * Exemple :
 *   getSpectacle?id=1&nbPlaces=2
 */
struct request {
    char action[50];
    struct cleValeur arguments[10];
    int nbArguments;
};

/*
 * Analyse une chaîne et remplit une requête
 */
static inline void createRequest(const char *chaine, struct request *req)
{
    char buffer[256];

    if (chaine == NULL || req == NULL)
        return;

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    req->nbArguments = 0;
    req->action[0] = '\0';

    /* Séparation action / arguments */
    char *p = strtok(buffer, "?");
    if (p == NULL)
        return;

    strncpy(req->action, p, 49);
    req->action[49] = '\0';

    /* Pas d’arguments */
    p = strtok(NULL, "?");
    if (p == NULL)
        return;

    /* Découpage clé=valeur */
    char *arg = strtok(p, "&");

    while (arg != NULL && req->nbArguments < 10) {

        char *egal = strchr(arg, '=');
        if (egal != NULL) {
            *egal = '\0';

            strncpy(req->arguments[req->nbArguments].cle, arg, 49);
            req->arguments[req->nbArguments].cle[49] = '\0';

            strncpy(req->arguments[req->nbArguments].valeur, egal + 1, 49);
            req->arguments[req->nbArguments].valeur[49] = '\0';

            req->nbArguments++;
        }

        arg = strtok(NULL, "&");
    }
}

/* Affichage */
static inline void afficherRequest(const struct request *req)
{
    if (req == NULL) return;

    printf("Request :\n");
    printf("Action : %s\n", req->action);
    printf("Arguments (%d) :\n", req->nbArguments);

    for (int i = 0; i < req->nbArguments; i++) {
        afficherCleValeur(&req->arguments[i]);
    }
}

#endif


