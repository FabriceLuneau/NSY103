#ifndef LISTE_CLE_VALEUR_H
#define LISTE_CLE_VALEUR_H

#include <stddef.h>    /* pour size_t */
#include <stdlib.h>    /* pour malloc, realloc, free */
#include <string.h>    /* pour strcmp */
#include "cleValeur.h" /* pour struct cleValeur */

/* 
 * Liste dynamique de paires clé/valeur
 */
typedef struct
{
    struct cleValeur *items; /* tableau dynamique de cleValeur */
    size_t taille;           /* nombre d'éléments utilisés */
    size_t capacite;         /* capacité du tableau */
} ListeCleValeur;

/* Crée une liste vide */
static inline ListeCleValeur listeCleValeur_create(void)
{
    ListeCleValeur l;
    l.items = NULL;
    l.taille = 0;
    l.capacite = 0;
    return l;
}

/* Ajoute un item à la liste
 * Renvoie 1 si succès, 0 sinon
 */
static inline int listeCleValeur_add(ListeCleValeur *l, struct cleValeur cv)
{
    if (l == NULL)
    {
        return 0;
    }

    /* Agrandissement du tableau si nécessaire */
    if (l->taille == l->capacite)
    {
        size_t nouvelle_capacite = (l->capacite == 0) ? 4 : l->capacite * 2;
        struct cleValeur *nouveaux_items = 
            realloc(l->items, nouvelle_capacite * sizeof(struct cleValeur));

        if (nouveaux_items == NULL)
        {
            return 0; /* échec allocation */
        }

        l->items = nouveaux_items;
        l->capacite = nouvelle_capacite;
    }

    /* Copie directe de la structure dans le tableau */
    l->items[l->taille] = cv;
    l->taille++;

    return 1;
}

/* Récupère la valeur associée à une clé
 * Renvoie NULL si la clé n'existe pas
 */
static inline const char *listeCleValeur_getValeur(const ListeCleValeur *l, const char *cle)
{
    if (l == NULL || cle == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < l->taille; i++)
    {
        if (strcmp(l->items[i].cle, cle) == 0)
        {
            return l->items[i].valeur;
        }
    }

    return NULL;
}

/* Libère la mémoire du tableau de la liste */
static inline void listeCleValeur_free(ListeCleValeur *l)
{
    if (l == NULL)
    {
        return;
    }

    free(l->items);
    l->items = NULL;
    l->taille = 0;
    l->capacite = 0;
}

//afffiche toutes les clefs valeur de la liste
static inline void listeCleValeur_afficher(const ListeCleValeur *l)
{
    if (l == NULL)
        return;

    for (size_t i = 0; i < l->taille; i++)
    {
        /* soit tu utilises une fonction dédiée */
        cleValeur_afficher(&l->items[i]);

        /* soit en direct :
        printf("clé: %s | valeur: %s\n",
               l->items[i].cle,
               l->items[i].valeur);
        */
    }
}

#endif /* LISTE_CLE_VALEUR_H */
