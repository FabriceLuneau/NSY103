#ifndef RESPONSE_H
#define RESPONSE_H
#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listeCleValeur.h"
#include "cleValeur.h"

/*
 * Représente une réponse serveur
 *
 * Exemples :
 *   200
 *   404
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20,
 *             item:id=2;intitule=Concert;nbPlaces=100
 */
struct response
{
    char code[8];          /* code de réponse (200, 404, ...) */
    ListeCleValeur contenu; /* contenu clé/valeur */
};

/* =============================
   Prototypes internes
   ============================= */
static inline int response_ajouterContenu(
    struct response *resp,
    const struct cleValeur *cv
);

/*
 * Crée une réponse avec un code obligatoire
 */
static inline struct response response_create(const char *code)
{
    struct response resp;

    if (code == NULL)
    {
        resp.code[0] = '\0';
    }
    else
    {
        strncpy(resp.code, code, sizeof(resp.code) - 1);
        resp.code[sizeof(resp.code) - 1] = '\0';
    }

    resp.contenu = listeCleValeur_create();
    return resp;
}

/*
 * Analyse une réponse sous la forme :
 *   code?cle=valeur&cle2=valeur2
 *
 * Exemple :
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20
 */
static inline int response_createDepuisChaine(
    struct response *resp,
    const char *chaine
)
{
    char buffer[512];

    if (resp == NULL || chaine == NULL)
    {
        return -1;
    }

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    /* séparation code / contenu */
    char *p = strtok(buffer, "?");
    if (p == NULL)
    {
        return -1;
    }

    strncpy(resp->code, p, sizeof(resp->code) - 1);
    resp->code[sizeof(resp->code) - 1] = '\0';

    /* pas de contenu */
    p = strtok(NULL, "?");
    if (p == NULL)
    {
        return 0;
    }

    /* découpage cle=valeur (& séparateur) */
    char *arg = strtok(p, "&");
    while (arg != NULL)
    {
        struct cleValeur cv = cleValeur_createDepuisChaine(arg);
        response_ajouterContenu(resp, &cv);
        arg = strtok(NULL, "&");
    }

    return 0;
}

/*
 * Récupère une valeur du contenu
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
 * Affichage debug de la réponse
 */
static inline void response_afficher(const struct response *resp)
{
    if (resp == NULL)
        return;

    printf("Response :\n");
    printf("Code : %s\n", resp->code);
    printf("Contenu :\n");

    listeCleValeur_afficher(&resp->contenu);
}

/*
 * Ajoute un contenu clé/valeur à la réponse
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

#endif /* RESPONSE_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listeCleValeur.h"
#include "cleValeur.h"

/*
 * Représente une réponse serveur
 *
 * Exemples :
 *   200
 *   404
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20,
 *             item:id=2;intitule=Concert;nbPlaces=100
 */
struct response
{
    char code[8];          /* code de réponse (200, 404, ...) */
    ListeCleValeur contenu; /* contenu clé/valeur */
};

/* =============================
   Prototypes internes
   ============================= */
static inline int response_ajouterContenu(
    struct response *resp,
    const struct cleValeur *cv
);

/*
 * Crée une réponse avec un code obligatoire
 */
static inline struct response response_create(const char *code)
{
    struct response resp;

    if (code == NULL)
    {
        resp.code[0] = '\0';
    }
    else
    {
        strncpy(resp.code, code, sizeof(resp.code) - 1);
        resp.code[sizeof(resp.code) - 1] = '\0';
    }

    resp.contenu = listeCleValeur_create();
    return resp;
}

/*
 * Analyse une réponse sous la forme :
 *   code?cle=valeur&cle2=valeur2
 *
 * Exemple :
 *   200?array=item:id=1;intitule=Opera;nbPlaces=20
 */
static inline int response_createDepuisChaine(
    struct response *resp,
    const char *chaine
)
{
    char buffer[512];

    if (resp == NULL || chaine == NULL)
    {
        return -1;
    }

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    /* séparation code / contenu */
    char *p = strtok(buffer, "?");
    if (p == NULL)
    {
        return -1;
    }

    strncpy(resp->code, p, sizeof(resp->code) - 1);
    resp->code[sizeof(resp->code) - 1] = '\0';

    /* pas de contenu */
    p = strtok(NULL, "?");
    if (p == NULL)
    {
        return 0;
    }

    /* découpage cle=valeur (& séparateur) */
    char *arg = strtok(p, "&");
    while (arg != NULL)
    {
        struct cleValeur cv = cleValeur_createDepuisChaine(arg);
        response_ajouterContenu(resp, &cv);
        arg = strtok(NULL, "&");
    }

    return 0;
}

/*
 * Récupère une valeur du contenu
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
 * Affichage debug de la réponse
 */
static inline void response_afficher(const struct response *resp)
{
    if (resp == NULL)
        return;

    printf("Response :\n");
    printf("Code : %s\n", resp->code);
    printf("Contenu :\n");

    listeCleValeur_afficher(&resp->contenu);
}

/*
 * Ajoute un contenu clé/valeur à la réponse
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

#endif /* RESPONSE_H */
