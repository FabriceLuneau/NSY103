#ifndef CLE_VALEUR_H
#define CLE_VALEUR_H

#include <stdio.h>
#include <string.h>

/*
 * Paire clé / valeur
 * Exemple : id=1
 */
struct cleValeur {
    char cle[50];
    char valeur[50];
};

/* Affichage */
static inline void afficherCleValeur(const struct cleValeur *item)
{
    if (item == NULL) return;
    printf("  %s = %s\n", item->cle, item->valeur);
}

#endif




