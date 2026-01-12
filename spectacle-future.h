#ifndef SPECTACLE
#define SPECTACLE
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct spectacle {
    char intitule[50];
    int nbPlaces;
};

/*
* constructeur pour une structure spectacle
*/
struct spectacle spectacle_creer(const char *intitule, int nbPlaces) 
{
    struct spectacle s
    strncpy(s.intitule, intitule, sizeof(s.intitule) - 1);
    s.intitule[sizeof(s.intitule) - 1] = '\0';
    s.nbPlaces = nbPlaces;
    return s;
}

/*
*  Test si la quantité de places est disponible pour le  spectacle
*/
bool spectacle_quantiteEstDisponible(struct spectacle *spectacle, dSpectacle, int quantiteDemandee) 
{
        return quantiteDemandee <= spectacle.nbPlaces;
}

/*
 * Décrémente le nombre de places demandées pour l'id spectacle si disponible, retourne un booléen
 */
bool spectacle_retirerPlaces(struct spectacle *spc, int quantiteDemandee) {
    if(spectacle_quantiteEstDisponible(spec, quantiteDemandee)) 
    {
        spec.nbPlaces  = spec.nbPlaces - quantiteDemandee

        return true;
    } 
    else 
    {
        return false;
    }
}

#endif /*BRIDGE*/

#endif /*SPECTACLE*/