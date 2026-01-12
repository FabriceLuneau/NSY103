#include <stdio.h>
#include "cleValeur.h"
#include "response.h"
#include "spectacle.h"

int main(void)
{
    /* =============================
       Test d'une réponse simple
       ============================= */

    struct response *resp = response_create(201);

    printf("\nTest d'une reponse simple\n");
    response_afficher(resp);

    /* =============================
       Test d'une réponse avec contenu
       ============================= */

    // Initialisation des spectacles (si nécessaire)
    spectacle_initTabGlobal();

    char chaine[16];
    snprintf(chaine, sizeof(chaine), "%d", tabSpectaclesGlobal[0].nbPlaces);

    resp = response_create(200);

    response_ajouterCleValeur(
        resp,
        cleValeur_create("id", "0")
    );

    response_ajouterCleValeur(
        resp,
        cleValeur_create("intitule", tabSpectaclesGlobal[0].intitule)
    );

    response_ajouterCleValeur(
        resp,
        cleValeur_create("nbPlaces", chaine)
    );

    printf
