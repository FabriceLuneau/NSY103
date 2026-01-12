#ifndef SPECTACLE_H
#define SPECTACLE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Nombre maximum de spectacles gérés
 */
const int maxSpectacles = 100;

/*
 * Nombre courant de spectacles
 */
int nbSpec = 0;

/*
 * Structure représentant un spectacle
 */
struct spectacle {
    char intitule[50];
    int nbPlaces;
};

/*
 * Tableau global des spectacles
 * TODO : éviter l'usage d'un global, trouver une meilleure solution
 */
struct spectacle tabSpectaclesGlobal[100];

/*
 * Teste si un spectacle existe à partir de son identifiant
 *
 * L'identifiant doit être compris entre 0 et le nombre d'éléments
 * actuellement présents dans le tableau global.
 */
bool spectacle_exists(int idSpectacle)
{
    return (idSpectacle >= 0 && idSpectacle < nbSpec);
}

void spectacle_afficherTout() {
    printf("Liste des spectacles :\n");
    for (int i = 0; i < nbSpec; i++) {
        printf("%d - %s (%d places)\n",
               i,
               tabSpectaclesGlobal[i].intitule,
               tabSpectaclesGlobal[i].nbPlaces);
    }
}

void spectacle_initTabGlobal() {
    struct spectacle tabTemp[] = {
        {"En attendant Gotot", 10},
        {"Tant qu'il y aura des pommes", 4},
        {"Le cercle des poètes dix par rues", 7},
        {"Notre spam de Paris", 7},
        {"Pouple fiction", 17},
        {"Les oiseaux se crashent pour mourrir", 29}
    };

    int taille = sizeof(tabTemp) / sizeof(tabTemp[0]);
    for (int i = 0; i < taille; i++) 
    {
        tabSpectaclesGlobal[i] = tabTemp[i];
    }
    nbSpec = taille;
}

/*
* / Test si la quantité de places est disponible pour le spectacle 
 *retourne un booléen si vrais si a
*/
bool spectacle_quantiteEstDisponible(int idSpectacle, int quantiteDemandee) {
    if (idSpectacle < 0 || idSpectacle >= nbSpec) {
        return false;
    }
    return quantiteDemandee <= tabSpectaclesGlobal[idSpectacle].nbPlaces;
}

/*
* Décrémente le nombre de places demandées pour le spectacle  si disponible
* retourne un booléen vrai si réussie
*/
bool spectacle_retirerPlaces(int idSpectacle, int quantiteDemandee) {
    if(spectacle_quantiteEstDisponible(idSpectacle, quantiteDemandee)) {
        tabSpectaclesGlobal[idSpectacle].nbPlaces -= quantiteDemandee;
        return true;
    } else {
        return false;
    }
}

#endif
