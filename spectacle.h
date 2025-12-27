#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxSpectacles = 100;

int nbSpec = 0;

struct spectacle {
    char intitule[50];
    int nbPlaces;
};

struct spectacle tabSpectacles[100];

void init() {
    struct spectacle tabTemp[] = {
        {"En attendant Gotot", 10},
        {"Tant qu'il y aura des pommes", 4},
        {"Le cercle des poètes dix par rues", 7},
        {"Notre spam de Paris", 7},
        {"L'inspecteur a ri", 9}
    };

    int taille = sizeof(tabTemp) / sizeof(tabTemp[0]);
    for (int i = 0; i < taille; i++) {
        tabSpectacles[i] = tabTemp[i];
    }
    nbSpec = taille;
}

void afficher() {
    printf("Liste des spectacles :\n");
    for (int i = 0; i < nbSpec; i++) {
        printf("%d - %s (%d places)\n",
               i,
               tabSpectacles[i].intitule,
               tabSpectacles[i].nbPlaces);
    }
}

// Test si la quantité de places est disponible pour l'id du spectacle spécifié, retourne un booléen
bool quantiteEstDisponible(int idSpectacle, int quantiteDemandee) {
    if (idSpectacle < 0 || idSpectacle >= nbSpec) {
        return false;
    }
    return quantiteDemandee <= tabSpectacles[idSpectacle].nbPlaces;
}

// Décrémente le nombre de places demandées pour l'id spectacle si disponible, retourne un booléen
bool retirerPlaces(int idSpectacle, int quantiteDemandee) {
    if (quantiteEstDisponible(idSpectacle, quantiteDemandee)) {
        tabSpectacles[idSpectacle].nbPlaces -= quantiteDemandee;
        return true;
    } else {
        return false;
    }
}

// Ajoute des places pour le spectacle pour l'id en argument
void ajouterPlaces(int idSpectacle, int quantiteDemandee) {
    tabSpectacles[idSpectacle].nbPlaces += quantiteDemandee;
}

struct spectacle creerSpectacle(int id, const char *intitule, int nbPlaces) {
    struct spectacle s;
    strncpy(s.intitule, intitule, sizeof(s.intitule) - 1);
    s.intitule[sizeof(s.intitule) - 1] = '\0';
    s.nbPlaces = nbPlaces;
    return s;
}

bool ajouterSpectacle(struct spectacle s) {
    if (nbSpec >= maxSpectacles) {
        return false;
    }
    tabSpectacles[nbSpec++] = s;
    return true;
}

struct spectacle creerSpectacleDepuisChaine(char *chaine) {
    char buffer[256];
    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char intitule[50] = "";
    int nbPlaces = 0;

    char *token = strtok(buffer, ";");
    while (token != NULL) {
        char *egal = strchr(token, '=');
        if (egal != NULL) {
            *egal = '\0';
            char *cle = token;
            char *valeur = egal + 1;

            if (strcmp(cle, "intitule") == 0) {
                strncpy(intitule, valeur, sizeof(intitule) - 1);
                intitule[sizeof(intitule) - 1] = '\0';
            } else if (strcmp(cle, "nbPlaces") == 0) {
                nbPlaces = atoi(valeur);
            }
        }
        token = strtok(NULL, ";");
    }

    return creerSpectacle(0, intitule, nbPlaces);
}

char **splitMessage(const char *chaine, int *nbElements) {
    char **resultat = malloc(maxSpectacles * sizeof(char *));
    char buffer[512];

    strncpy(buffer, chaine, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    int count = 0;
    char *token = strtok(buffer, ",");

    while (token != NULL && count < maxSpectacles) {
        resultat[count] = malloc(strlen(token) + 1);
        strcpy(resultat[count], token);
        count++;
        token = strtok(NULL, ",");
    }

    *nbElements = count;
    return resultat;
}

int creerDesSpectaclesDepuisChaine(char *chaine) {
    int nbElements = 0;
    int nbAjoutes = 0;

    char **messages = splitMessage(chaine, &nbElements);

    for (int i = 0; i < nbElements; i++) {
        if (nbSpec >= maxSpectacles) {
            break;
        }
        struct spectacle s = creerSpectacleDepuisChaine(messages[i]);
        ajouterSpectacle(s);
        nbAjoutes++;
        free(messages[i]);
    }

    free(messages);
    return nbAjoutes;
}
