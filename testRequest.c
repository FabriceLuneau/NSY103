#include <stdio.h>
#include "cleValeur.h"
#include "request.h"
#include "spectacle.h"

int main(void)
{
    // Test de cleValeur
    struct cleValeur cv;

    printf("Test de création d'une structure cleValeur avec deux arguments séparés\n");
    cv = cleValeur_create("id", "1");
    cleValeur_afficher(&cv);

    printf("\nTest de création d'une structure cleValeur à partir d'une chaîne 'id=1'\n"); 
    cv = cleValeur_createDepuisChaine("id=1");
    cleValeur_afficher(&cv);

    // Tests de requêtes
    printf("\nTest de création d'une structure request\n");

    struct request req;

    // Initialisation de la requête
    req = request_create("get");

    printf("\nTest de création d'une requête sans argument\n");
    request_createDepuisChaine(&req, "getSpectacles");
    request_afficher(&req);

    printf("\nTest de création d'une requête avec un argument id=1\n");
    req = request_create("get");
    request_createDepuisChaine(&req, "getSpectacle?id=1");
    request_afficher(&req);

    printf("\nTest de création d'une requête avec deux arguments id=1 et nbPlaces=2\n");
    req = request_create("get");
    request_createDepuisChaine(&req, "reserver?id=1&nbPlaces=2");
    request_afficher(&req);

    // Test avec ajout manuel d'un argument
    printf("\nTest d'ajout manuel d'un argument à la requête\n");
    req = request_create("get");

    /* Création de la paire clé/valeur */
    cv = cleValeur_create("id", "1");

    /* Ajout de l'argument à la requête */
    request_ajouterArgument(&req, &cv);

    /* Affichage pour vérification */
    request_afficher(&req);

    return 0;
}
