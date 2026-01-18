#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listeCleValeur.h"
#include "cleValeur.h"

/*
 * Représente une requête client
 *
 * Exemples :
 *   getSpectacles
 *   getSpectacle?id=1
 *   reserver?id=1&nbPlaces=2
 */
struct request
{
    char action[50];          /* action demandée (obligatoire) */
    ListeCleValeur arguments; /* liste des arguments clé/valeur */
};

/* =============================
   Prototype interne
   ============================= */
static inline int request_ajouterArgument(
    struct request *req,
    const struct cleValeur *cv
);

/*
 * Crée une requête avec une action obligatoire
 */
static inline struct request request_create(const char *action)
{
    struct request req;

    if (action == NULL)
    {
        /* action obligatoire mais sécurisée */
        req.action[0] = '\0';
    }
    else
    {
        strncpy(req.action, action, sizeof(req.action) - 1);
        req.action[sizeof(req.action) - 1] = '\0';
    }

    req.arguments = listeCleValeur_create();
    return req;
}

/*
 * Analyse une chaîne de type :
 *   action?cle=valeur&cle2=valeur2
 *
 * Retour :
 *   0  -> succès
 *  -1  -> erreur
 */
static inline int request_createDepuisChaine(
    struct request *req,
    const char *chaine
)
{
    char buffer[256];

    if (req == NULL || chaine == NULL)
    {
        return -1;
    }

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    /* séparation action / arguments */
    char *p = strtok(buffer, "?");
    if (p == NULL)
    {
        return -1;
    }

    strncpy(req->action, p, sizeof(req->action) - 1);
    req->action[sizeof(req->action) - 1] = '\0';

    /* pas d'arguments */
    p = strtok(NULL, "?");
    if (p == NULL)
    {
        return 0;
    }

    /* découpage clé=valeur */
    char *arg = strtok(p, "&");
    while (arg != NULL)
    {
        struct cleValeur cv = cleValeur_createDepuisChaine(arg);
        request_ajouterArgument(req, &cv);
        arg = strtok(NULL, "&");
    }

    return 0;
}

/*
 * Recherche la valeur d’un argument par sa clé
 */
static inline const char *request_getArgumentValue(
    const struct request *req,
    const char *cle
)
{
    if (req == NULL || cle == NULL)
    {
        return NULL;
    }

    return listeCleValeur_getValeur(&req->arguments, cle);
}

/*
 * Affichage debug de la requête
 */
static inline void request_afficher(const struct request *req)
{
    if (req == NULL)
        return;

    printf("Request :\n");
    printf("Action : %s\n", req->action);
    printf("Arguments :\n");

    listeCleValeur_afficher(&req->arguments);
}

/*
 * Ajoute un argument à la requête
 */
static inline int request_ajouterArgument(
    struct request *req,
    const struct cleValeur *cv
)
{
    if (req == NULL || cv == NULL)
    {
        return 0;
    }

    return listeCleValeur_add(&req->arguments, *cv);
}

#endif /* REQUEST_H */
