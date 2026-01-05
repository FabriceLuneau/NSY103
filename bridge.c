#include <stdio.h>
#include <string.h>
#include "response.h"
#include "spectacle.h"

static inline void intToString(int value, char *buffer, size_t size)
{
    snprintf(buffer, size, "%d", value);
}

void bridge_encodeSpectaclesResponse(
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

        intToString(0, tmp, sizeof(tmp));
        responseAjouterCleValeur(resp, creerCleValeur("id", tmp));

        responseAjouterCleValeur(
            resp,
            creerCleValeur("intitule", spectacles[0].intitule)
        );

        intToString(spectacles[0].nbPlaces, tmp, sizeof(tmp));
        responseAjouterCleValeur(
            resp,
            creerCleValeur("nbPlaces", tmp)
        );
        return;
    }

    /* ===== PLUSIEURS SPECTACLES ===== */
    for (int i = 0; i < nbSpectacles; i++) {
        char tmp[16];
        char item[128];

        item[0] = '\0';

        /* id = index */
        intToString(i, tmp, sizeof(tmp));
        strcat(item, "id=");
        strcat(item, tmp);
        strcat(item, ";");

        /* intitule */
        strcat(item, "intitule=");
        strcat(item, spectacles[i].intitule);
        strcat(item, ";");

        /* nbPlaces */
        intToString(spectacles[i].nbPlaces, tmp, sizeof(tmp));
        strcat(item, "nbPlaces=");
        strcat(item, tmp);

        /* concat à la chaîne globale */
        strcat(buffer, item);

        if (i < nbSpectacles - 1)
            strcat(buffer, "|");
    }

    responseAjouterCleValeur(
        resp,
        creerCleValeur("array", buffer)
    );
}

