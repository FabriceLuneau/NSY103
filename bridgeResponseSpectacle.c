#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cleValeur.h"
#include "response.h"
#include "spectacle.h"

//Fonction utilitaire pourconvertir un nombre en chaine
char[] convertIntToString(int intToconvert) 
{
    char chaine[4];
    
 snprintf(chain

    return chaine;

 }
/*
 * Extrait les spectacles contenus dans une response.
 *
 * Retourne le nombre de spectacles extraits.
 * - 0 : aucun (normalement erreur 4xx)
 * - 1 : un seul spectacle
 * - >1 : plusieurs spectacles
 */
int extractSpectaclesResponse(
    const struct response *rep,
    struct spectacle *result,
    int maxSpectacles
) {
    if (!rep || !result || maxSpectacles <= 0)
        return 0;

    /* Cas 1 : un seul spectacle (pas de "array") */
    int isArray = 0;
    for (int i = 0; i < rep->nbContent; i++) {
        if (strcmp(rep->content[i].cle, "array") == 0) {
            isArray = 1;
            break;
        }
    }

    /* ======== SPECTACLE UNIQUE ======== */
    if (!isArray) {
        struct spectacle sp = {0};

        for (int i = 0; i < rep->nbContent; i++) {
            struct cleValeur *cv = &rep->content[i];

            if (strcmp(cv->cle, "id") == 0) {
                //sp.id = atoi(cv->valeur);
            }
            else if (strcmp(cv->cle, "intitule") == 0) {
                strncpy(sp.intitule, cv->valeur, sizeof(sp.intitule) - 1);
            }
            else if (strcmp(cv->cle, "nbPlaces") == 0) {
                sp.nbPlaces = atoi(cv->valeur);
            }
        }

        result[0] = sp;
        return 1;
    }

    /* ======== TABLEAU DE SPECTACLES ======== */
    for (int i = 0; i < rep->nbContent; i++) {

        if (strcmp(rep->content[i].cle, "array") != 0)
            continue;

        char buffer[512];
        strncpy(buffer, rep->content[i].valeur, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        int count = 0;

        /* séparation des spectacles */
        char *item = strtok(buffer, "|");

        while (item && count < maxSpectacles) {

            struct spectacle sp = {0};

            /* séparation des champs */
            char *field = strtok(item, ";");

            while (field) {

                char *eq = strchr(field, '=');
                if (eq) {
                    *eq = '\0';
                    char *cle = field;
                    char *val = eq + 1;

                    if (strcmp(cle, "id") == 0) {
                        //sp.id = atoi(val);
                    }
                    else if (strcmp(cle, "intitule") == 0) {
                        strncpy(sp.intitule, val, sizeof(sp.intitule) - 1);
                    }
                    else if (strcmp(cle, "nbPlaces") == 0) {
                        sp.nbPlaces = atoi(val);
                    }
                }

                field = strtok(NULL, ";");
            }

            result[count++] = sp;
            item = strtok(NULL, "|");
        }

        return count;
    }

    return 0;
}