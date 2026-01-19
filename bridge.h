#ifndef BRIDGE_H
#define BRIDGE_H

#include <stdio.h>
#include <string.h>
#include "response.h"
#include "spectacle.h"

/* =========================================================
 * Encodage d'un ou plusieurs spectacles dans une response
 * ========================================================= */

/*
 * Encodage d'un tableau de spectacles
 */
static inline void bridge_encodeSpectaclesResponse(
    struct response *resp,
    const struct spectacle *spectacles,
    int nbSpectacles
) {
    if (!resp || !spectacles || nbSpectacles <= 0)
        return;

    char buffer[512];
    buffer[0] = '\0';

    /* ===== UN SEUL SPECTACLE ===== */
    if (nbSpectacles == 1) {
        char tmp[16];

        snprintf(tmp, sizeof(tmp), "%d", 0);
        response_ajouterCleValeur(
            resp,
            cleValeur_create("id", tmp)
        );

        response_ajouterCleValeur(
            resp,
            cleValeur_create("intitule", spectacles[0].intitule)
        );

        snprintf(tmp, sizeof(tmp), "%d", spectacles[0].nbPlaces);
        response_ajouterCleValeur(
            resp,
            cleValeur_create("nbPlaces", tmp)
        );

        return;
    }

    /* ===== PLUSIEURS SPECTACLES ===== */
    for (int i = 0; i < nbSpectacles; i++) {
        char tmp[16];
        char item[128];
        item[0] = '\0';

        /* id */
        snprintf(tmp, sizeof(tmp), "%d", i);
        strcat(item, "id=");
        strcat(item, tmp);
        strcat(item, ";");

        /* intitule */
        strcat(item, "intitule=");
        strcat(item, spectacles[i].intitule);
        strcat(item, ";");

        /* nbPlaces */
        snprintf(tmp, sizeof(tmp), "%d", spectacles[i].nbPlaces);
        strcat(item, "nbPlaces=");
        strcat(item, tmp);

        strcat(buffer, item);
        if (i < nbSpectacles - 1)
            strcat(buffer, "|");
    }

    response_ajouterCleValeur(
        resp,
        cleValeur_create("array", buffer)
    );
}

/*
 * Wrapper : encodage d'un seul spectacle
 */
static inline void bridge_encodeUnSpectacleResponse(
    struct response *resp,
    const struct spectacle spectacle
) {
    struct spectacle tabSpectacle[1];
    tabSpectacle[0] = spectacle;

    bridge_encodeSpectaclesResponse(resp, tabSpectacle, 1);
}

#endif /* BRIDGE_H */
