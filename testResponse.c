#include <stdio.h>

#include "cleValeur.h"
#include "response.h"
#include "spectacle.h"

int main(void)
{
    /* =============================
       Test d'une réponse simple
       ============================= */

    struct response resp = response_create(201);

    printf("\nTest d'une reponse simple\n");
    response_afficher(&resp);

    /* =============================
       Test d'une réponse avec contenu
       ============================= */

    /* Initialisation des spectacles */
    spectacle_initTabGlobal();

    char chaine[16];
    snprintf(chaine, sizeof(chaine), "%d", tabSpectaclesGlobal[0].nbPlaces);

    resp = response_create(200);

    /* Création des paires clé / valeur */
    struct cleValeur cv_id =
        cleValeur_create("id", "0");

    struct cleValeur cv_intitule =
        cleValeur_create("intitule", tabSpectaclesGlobal[0].intitule);

    struct cleValeur cv_nbPlaces =
        cleValeur_create("nbPlaces", chaine);

    /* Ajout au contenu de la réponse */
    response_ajouterContenu(&resp, &cv_id);
    response_ajouterContenu(&resp, &cv_intitule);
    response_ajouterContenu(&resp, &cv_nbPlaces);

    printf("\nTest d'une reponse avec contenu\n");
    response_afficher(&resp);

    return 0;
}
