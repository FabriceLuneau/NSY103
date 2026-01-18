#include <stdio.h>
#include "response.h"
#include "cleValeur.h"
#include "spectacle.h"

int main(void)
{
    struct response resp;
    struct cleValeur cv;

    /* =====================================================
       1. Réponse OK : réservation réussie
       ===================================================== */
    printf("\n=== Test 1 : Réservation OK ===\n");

    resp = response_create("200");
    cv = cleValeur_create("message", "reservation_ok");
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    /* =====================================================
       2. Réponse ERREUR : pas assez de places
       ===================================================== */
    printf("\n=== Test 2 : Erreur - pas assez de places ===\n");

    resp = response_create("409"); /* conflit */

    cv = cleValeur_create("message", "pas_assez_de_places");
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    /* =====================================================
       3. Réponse ERREUR : opération inconnue
       ===================================================== */
    printf("\n=== Test 3 : Erreur - operation inconnue ===\n");

    resp = response_create("400"); /* requête invalide */

    cv = cleValeur_create("message", "operation_inconnue");
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    /* =====================================================
       4. Réponse ERREUR : spectacle non trouvé
       ===================================================== */
    printf("\n=== Test 4 : Erreur - spectacle non trouve ===\n");

    resp = response_create("404"); /* non trouvé */

    cv = cleValeur_create("message", "spectacle_non_trouve");
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    /* =====================================================
       5. Réponse OK : un seul spectacle
       ===================================================== */
    printf("\n=== Test 5 : Réponse avec un spectacle ===\n");

    resp = response_create("200");

    /*
     * array = item:id=1;intitule=Opera;nbPlaces=20
     */
    cv = cleValeur_create(
        "array",
        "item:id=1;intitule=Opera;nbPlaces=20"
    );
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    /* =====================================================
       6. Réponse OK : plusieurs spectacles
       ===================================================== */
    printf("\n=== Test 6 : Réponse avec plusieurs spectacles ===\n");

    resp = response_create("200");

    /*
     * array = item:id=1;intitule=Opera;nbPlaces=20,
     *         item:id=2;intitule=Concert;nbPlaces=100,
     *         item:id=3;intitule=Theatre;nbPlaces=50
     */
    cv = cleValeur_create(
        "array",
        "item:id=1;intitule=Opera;nbPlaces=20,"
        "item:id=2;intitule=Concert;nbPlaces=100,"
        "item:id=3;intitule=Theatre;nbPlaces=50"
    );
    response_ajouterContenu(&resp, &cv);

    response_afficher(&resp);

    return 0;
}
