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
    request_afficher(&req);

    //Test response =====
struct response resp;

printf("\nTeste dune reponse simple\n");
     response_init(&resp, 201);
response_afficher(&resp);
    
//test d'une response avec un contenu

 spectacle_initTabGlobal();

 printf("\nTeste dune reponse avec un spectacle\n");

char chaine[4];
 snprintf(chaine, sizeof(chaine), "%d", tabSpectacles[0].nbPlaces);

   response_init(&resp, 200);
 response_ajouterCleValeur(&resp, cleValeur_create("id", "0"));
        response_ajouterCleValeur(&resp, cleValeur_create("intitule", tabSpectacles[0].intitule));
        response_ajouterCleValeur(&resp, cleValeur_create("nbPlaces", chaine));
        //response_ajouterCleValeur(&resp, creerCleValeur("nbPlaces", tabSpectacles[0].nbPlaces));

   response_afficher(&resp);
    



    
    

    return 0;
}
