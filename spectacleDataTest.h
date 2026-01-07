#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"spectacle.h"


int spectacleinitDataTest(struct spectacle* tabSpectacle []) 
{
    struct spectacle tabTemp[] = {
        {"En attendant Gotot", 10},
        {"Tant qu'il y aura des pommes", 4},
        {"Le cercle des poètes dix par rues", 7},
        {"Notre spam de Paris", 7},
        {"Pouple fiction", 17},
        {"Les oiseaux se crashent pour mourrir", 29}
    };

    int taille = sizeof(tabTemp) / sizeof(tabTemp[0]);
    for (int i = 0; i < taille; i++) {
        tabSpectacles[i] = tabTemp[i];
    }
    nbSpec = taille;

    retturn taille;
}
