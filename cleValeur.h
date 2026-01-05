#ifndef CLE_VALEUR_H
#define CLE_VALEUR_H

#include <stdio.h>
#include <string.h>

/*
 * Paire clé / valeur pour les requêtes et réponses
 * Exemple :
 *   id=1
 *   nbPlaces=50
 */
struct cleValeur {
    char cle[50];
    char valeur[50];
};

/*
 * Affichage d'une paire clé / valeur
 */
static inline void cleValeur_afficher(const struct cleValeur *item)
{
    if (item == NULL) return;
    printf("  %s = %s\n", item->cle, item->valeur);
}

/*
 * Création d'une paire clé / valeur à partir de deux chaînes
 */
static inline struct cleValeur  cleValeur_create(const char *cle, const char *valeur)
{
    struct cleValeur item;

    item.cle[0] = '\0';
    item.valeur[0] = '\0';

    if (cle != NULL) {
        strncpy(item.cle, cle, sizeof(item.cle) - 1);
        item.cle[sizeof(item.cle) - 1] = '\0';
    }

    if (valeur != NULL) {
        strncpy(item.valeur, valeur, sizeof(item.valeur) - 1);
        item.valeur[sizeof(item.valeur) - 1] = '\0';
    }

    return item;
}

/*
 * Création d'une paire clé / valeur à partir d'une chaîne "cle=valeur"
 * ⚠️ La chaîne passée est copiée (elle n'est pas modifiée)
 */
static inline struct cleValeur cleValeur_createDepuisChaine(const char *chaine)
{
    struct cleValeur item;
    char buffer[100];

    item.cle[0] = '\0';
    item.valeur[0] = '\0';

    if (chaine == NULL) {
        return item;
    }

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *egal = strchr(buffer, '=');
    if (egal == NULL) {
        return item; // format invalide
    }

    *egal = '\0';

    strncpy(item.cle, buffer, sizeof(item.cle) - 1);
    item.cle[sizeof(item.cle) - 1] = '\0';

    strncpy(item.valeur, egal + 1, sizeof(item.valeur) - 1);
    item.valeur[sizeof(item.valeur) - 1] = '\0';

    return item;
}

#endif /* CLE_VALEUR_H */

