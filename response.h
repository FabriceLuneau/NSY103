
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
 * 400 opération non suportes, bbad request
 * 401 -> pas assez de places
 * 404 -> spectacle introuvable
 */
struct response {
    int code;
    struct cleValeur content[100];
    int nbContent;
};

/*
 * Initialise une réponse
 */
static inline void response_init(struct response *resp, int code)
{
    if (resp == NULL) return;
    resp->code = code;
    resp->nbContent = 0;
}

/*
 * Ajoute une paire clé / valeur à la réponse
 */
static inline int response_ajouterCleValeur(
    struct response *resp,
    struct cleValeur item
) {
    if (resp == NULL) return -1;
    if (resp->nbContent >= 100) return -1;

    resp->content[resp->nbContent] = item;
    resp->nbContent++;
    return 0;
}

/*
 * Affichage (debug / test)
 */
static inline void response_afficher(const struct response *resp)
{
    if (resp == NULL) return;

    printf("Response :\n");
    printf("Code : %d\n", resp->code);
    printf("Contenu (%d) :\n", resp->nbContent);

    for (int i = 0; i < resp->nbContent; i++) {
        cleValeur_afficher(&resp->content[i]);
    }
}

//doit retourner unenouvelle response
struct response response_create(int code) 
{
    //tod implements 
    //resp->code = code;
    //tod initialiser le tableau pour eviter les erreurs de segmenetation
////resp .content = 
//resp->nbContent = 0;

//return resp;

}

#endif /* RESPONSE_H */

