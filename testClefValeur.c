#include <stdio.h>
#include "cleValeur.h"
#include "listeCleValeur.h"

int main(void)
{
    // Test de cleValeur
    printf("Test de creation d'une structure cleValeur avec deux arguments séparés\n");
    struct cleValeur cv1 = cleValeur_create("id", "1");
    cleValeur_afficher(&cv1);

    printf("Test de creation d'une structure cleValeur avec une chaine id=1\n"); 
    struct cleValeur cv2 = cleValeur_createDepuisChaine("id=2");
    cleValeur_afficher(&cv2);

    printf("Test de creation d'une structure cleValeur avec une chaine et un nombre\n"); 
    struct cleValeur cv3 = cleValeur_createValeurNombre("id", 3);
    cleValeur_afficher(&cv3);

    // Test de ListeCleValeur
    ListeCleValeur lcv = listeCleValeur_create();
    listeCleValeur_add(&lcv, cv1);
    listeCleValeur_add(&lcv, cv2);
    listeCleValeur_add(&lcv, cv3);

    // Affichage des éléments de la liste
    printf("\nAffichage des éléments de la liste :\n");
    listeCleValeur_afficher(&lcv);
    //for (size_t i = 0; i < cl.taille; i++)
    //{
        //cleValeur_afficher(&cl.items[i]);
    //}

    // Libération de la mémoire de la liste
    listeCleValeur_free(&lcv);

    return 0;
}
