#include <stdio.h>
#include"cleValeur.h"
#include "request.h"
#include "response.h"
#include"spectacle.h"

int main(void)
{
    //test de cle valeur
    struct cleValeur cv;

    printf("Test de creation d'une structure cle valeur  avec iddeux arguments séparés  1\n");
     cv = cleValeur_create("id", "1");
    cleValeur_afficher(&cv);

    printf("Test de creation d'une structure cle valeur  avec une chaine, id=1\n"); 
    cv = cleValeur_createDepuisChaine("id=1");
     cleValeur_afficher(&cv);

    // Tests de requetes
    printf("\nTest de creation des structure requete \n");

    struct request req;

    printf("\nTest de creation d'une structure requete sans argument");
    request_createDepuisChaine("getSpectacles",& req);
    request_afficher(&req);

        printf("\nTest de creation d'une structure requete avec un argument, id= 1\n");
    request_createDepuisChaine("getSpectacle?id=1",& req);
    request_afficher(&req);

    printf("\nTest de creation d'une structure requete avec deux argument, id=1 et nbPlaces=2 \n");
    request_createDepuisChaine("reserver?id=1&nbPlaces=2",& req);
    //request_afficher(&req);

    //printf("\nTest printf("\nTest de creation d'une structure requete avec un argument, structure cv id=1\n");

//struct request req;
//struct cleValeur cv;

request_init(&req);

/* Création de la paire clé / valeur */
cv = cleValeur_create("id", "1");

/* Ajout de l'argument à la requête */
request_ajouterArgument(&req, &cv);

/* Affichage pour vérification */
request_afficher(&req);

    return 0;
}
