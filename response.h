#include <stdlib.h>
#include <string.h>
#include "cleValeur.h"

ListeCleValeur listeCleValeur_create(void) {
    ListeCleValeur l;
    l.items = NULL;
    l.taille = 0;
    l.capacite = 0;
    return l;
}

int listeCleValeur_add(ListeCleValeur *l,
                       const char *cle,
                       const char *valeur) {
    if (!l) return 0;

    if (l->taille == l->capacite) {
        size_t new_cap = l->capacite ? l->capacite * 2 : 4;
        CleValeur *tmp = realloc(l->items, new_cap * sizeof(*tmp));
        if (!tmp) return 0;

        l->items = tmp;
        l->capacite = new_cap;
    }

    l->items[l->taille].cle = strdup(cle);
    l->items[l->taille].valeur = strdup(valeur);

    if (!l->items[l->taille].cle || !l->items[l->taille].valeur)
        return 0;

    l->taille++;
    return 1;
}

const char *listeCleValeur_get(const ListeCleValeur *l,
                               const char *cle) {
    if (!l) return NULL;

    for (size_t i = 0; i < l->taille; i++) {
        if (strcmp(l->items[i].cle, cle) == 0)
            return l->items[i].valeur;
    }
    return NULL;
}

void listeCleValeur_free(ListeCleValeur *l) {
    if (!l) return;

    for (size_t i = 0; i < l->taille; i++) {
        free(l->items[i].cle);
        free(l->items[i].valeur);
    }
    free(l->items);
}
