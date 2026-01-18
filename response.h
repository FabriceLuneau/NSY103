#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listeCleValeur.h"
#include "cleValeur.h"

/*
 * Réponse envoyée par le serveur au client.
 *
 * Codes possibles :
 *  200 : requête acceptée, contenu retourné
 *  201 : réservation réussie
 *  400 : opération non supportée
 *  401 : réservation échouée (pas assez de places)
 *  404 : spectacle non trouvé
 *
 * Le contenu est représenté par une liste clé / valeur.
 *
 * La liste peut contenir :
 *  - rien : par exemple en cas de succès d’une réservation
 *  - un tableau logique (clé = "array")
 *  - des items représentant des spectacles (clé = "item")
 *
 * Le format exact du contenu est volontairement simple ici :
 * l’objectif est la compilation et la cohérence de l’API.
 */
struct response
{
    /*
     * Code de la réponse (ex : "200", "404", ...)
     */
    char code[16];

    /*
     * Contenu de la réponse sous forme clé / valeur
     */
    ListeCleValeur contenu;
};

/*
 * Crée une réponse initialisée avec un code.
 */
static inline struct response response_create(int code)
{
    struct response resp;

    /* Initialisation du code */
    snprintf(resp.code, sizeof(resp.code), "%d", code);

    /* Initialisation du contenu */
    resp.contenu = listeCleValeur_create();

    return resp;
}

/*
 * Initialise une réponse à partir d’un code et d’un contenu brut.
 *
 * Pour l’instant :
 *  - le contenu n’est pas parsé
 *  - seule l’initialisation est effectuée
 *
 * Retour :
 *   1  -> succès
 *   0  -> erreur
 */
static inline int response_createDepuisChaine(
    struct response *resp,
    int code,
    const char *contenu
)
{
    (void)contenu; /* contenu non utilisé pour l’instant */

    if (resp == NULL)
    {
        return 0;
    }

    snprintf(resp->code, sizeof(resp->code), "%d", code);
    resp->contenu = listeCleValeur_create();

    return 1;
}

/*
 * Recherche une valeur dans le contenu de la réponse par sa clé.
 *
 * Retour :
 *  - pointeur sur la valeur
 *  - NULL si la clé est absente
 */
static inline const char *response_getContenuValue(
    const struct response *resp,
    const char *cle
)
{
    if (resp == NULL || cle == NULL)
    {
        return NULL;
    }

    return listeCleValeur_getValeur(&resp->contenu, cle);
}

/*
 * Ajoute un élément clé / valeur au contenu de la réponse.
 *
 * Retour :
 *   1  -> succès
 *   0  -> erreur
 */
static inline int response_ajouterContenu(
    struct response *resp,
    const struct cleValeur *cv
)
{
    if (resp == NULL || cv == NULL)
    {
        return 0;
    }

    return listeCleValeur_add(&resp->contenu, *cv);
}

/*
 * Affiche une réponse (debug / test).
 */
static inline void response_afficher(const struct response *resp)
{
    if (resp == NULL)
    {
        return;
    }

    printf("Response :\n");
    printf("Code : %s\n", resp->code);
    printf("Contenu :\n");

    listeCleValeur_afficher(&resp->contenu);
}

/*
 * Libère le contenu de la réponse.
 */
static inline void response_free(struct response *resp)
{
    if (resp == NULL)
    {
        return;
    }

    listeCleValeur_free(&resp->contenu);
}

#endif /* RESPONSE_H */
