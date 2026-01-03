#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include "cleValeur.h"

/*
 * Réponse serveur
 *
 * Codes :
 * 200 -> GET OK (spectacle ou liste)
 * 201 -> réservation réussie
 * 401 -> pas assez de places
 * 404 -> spectacle introuvable
 */
struct response {
    int code;
    struct cleValeur content[10];
    int nbContent;
};

/* Affichage */
static inline void afficherResponse(const struct response *resp)
{
    if (resp == NULL) return;

    printf("Response :\n");
    printf("Code : %d\n", resp->code);
    printf("Contenu (%d) :\n", resp->nbContent);

    for (int i = 0; i < resp->nbContent; i++) {
        afficherCleValeur(&resp->content[i]);
    }
}

#endif




