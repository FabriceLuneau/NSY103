#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <string.h>
#include "cleValeur.h"

/*
 * Requête client
 *
 * Exemple :
 *   getSpectacle?id=1&nbPlaces=2
 */
struct request {
    char action[50];                 // action (ex: getSpectacle, reserver)
    struct cleValeur arguments[10];  // paires clé / valeur
    int nbArguments;                 // nombre réel d'arguments
};

/*
 * Initialise une requête
 */
static inline void request_init(struct request *req)
{
    if (req == NULL) return;

    req->action[0] = '\0';
    req->nbArguments = 0;
}

/*
 * Analyse une chaîne et remplit une requête
 *
 * Retour :
 *   0  -> succès
 *  -1  -> erreur de format
 */
static inline int request_createDepuisChaine(
    const char *chaine,
    struct request *req
)
{
    char buffer[256];

    if (chaine == NULL || req == NULL)
        return -1;

    request_init(req);

    /* strtok modifie la chaîne → copie locale */
    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    /* Séparation action / arguments */
    char *p = strtok(buffer, "?");
    if (p == NULL)
        return -1;

    strncpy(req->action, p, sizeof(req->action) - 1);
    req->action[sizeof(req->action) - 1] = '\0';

    /* Aucun argument */
    p = strtok(NULL, "?");
    if (p == NULL)
        return 0;

    /* Découpage clé=valeur séparé par '&' */
    char *arg = strtok(p, "&");

    while (arg != NULL && req->nbArguments < 10) {

        struct cleValeur item;
        cleValeur_createDepuisChaine(arg);

        //if (creerCleValeurDepuisChaine(arg) == 0) {
            //req->arguments[req->nbArguments] = item;
            //req->nbArguments++;
        //}

        arg = strtok(NULL, "&");
    }

    return 0;
}

/*
 * Recherche la valeur d’un argument par sa clé
 *
 * Retourne :
 *   pointeur sur la valeur
 *   NULL si absent
 */
static inline const char *getArgumentValue(
    const struct request *req,
    const char *cle
)
{
    if (req == NULL || cle == NULL)
        return NULL;

    for (int i = 0; i < req->nbArguments; i++) {
        if (strcmp(req->arguments[i].cle, cle) == 0) {
            return req->arguments[i].valeur;
        }
    }

    return NULL;
}

/*
 * Affichage (debug / test)
 */
static inline void request_afficher(const struct request *req)
{
    if (req == NULL) return;

    printf("Request :\n");
    printf("Action : %s\n", req->action);
    printf("Arguments (%d) :\n", req->nbArguments);

    for (int i = 0; i < req->nbArguments; i++) {
cleValeur_afficher(&req->arguments[i]);
    }
}

#endif /* REQUEST_H */

