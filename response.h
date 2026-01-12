#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include "cleValeur.h"

/* Réponse serveur
 * Codes :
 * 200 -> GET OK (spectacle ou liste)
 * 201 -> réservation réussie
 * 400 -> opération non supportée, bad request
 * 401 -> pas assez de places
 * 404 -> spectacle introuvable
 */
struct response
{
    int code;
    struct cleValeur content[100];
    int nbContent;
};

/*
 * Retourne une réponse initialisée avec le code en argument
 */
static inline struct response response_create(int code)
{
    struct response resp;

    resp.code = code;
    resp.nbContent = 0;

    return resp;
}

/*
 * Ajoute une paire clé / valeur à la réponse
 */
static inline int response_ajouterCleValeur(
    struct response *resp,
    struct cleValeur item
)
{
    if (resp == NULL)
    {
        return -1;
    }

    if (resp->nbContent >= 100)
    {
        return -1;
    }

    resp->content[resp->nbContent] = item;
    resp->nbContent++;

    return 0;
}

/*
 * Affichage (debug / test)
 */
static inline void response_afficher(const struct response *resp)
{
    if (resp == NULL)
    {
        return;
    }

    printf("Response :\n");
    printf("Code : %d\n", resp->code);
    printf("Contenu (%d) :\n", resp->nbContent);

    for (int i = 0; i < resp->nbContent; i++)
    {
        cleValeur_afficher(&resp->content[i]);
    }
}

#endif /* RESPONSE_H */
