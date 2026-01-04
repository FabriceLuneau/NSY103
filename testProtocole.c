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
     cv = creerCleValeur("id", "1");
    afficherCleValeur(&cv);

    printf("Test de creation d'une structure cle valeur  avec une chaine, id=1\n"); 
    cv = creerCleValeurDepuisChaine("id=1");
     afficherCleValeur(&cv);

    // Tests de requetes
    printf("\nTest de creation des structure requete \n");

    struct request req;

    printf("\nTest de creation d'une structure requete sans argument");
    creerRequestDepuisChaine("getSpectacles",& req);
    afficherRequest(&req);

        printf("\nTest de creation d'une structure requete avec un argument, id= 1\n");
    creerRequestDepuisChaine("getSpectacle?id=1",& req);
    afficherRequest(&req);

    printf("\nTest de creation d'une structure requete avec deux argument, id=1 et nbPlaces=2 \n");
    creerRequestDepuisChaine("reserver?id=1&nbPlaces=2",& req);
    afficherRequest(&req);

    //Test response =====
struct response resp;

printf("\nTeste dune reponse simple\n");
     response_init(&resp, 201);
response_afficher(&resp);
    
//test d'une response avec un contenu

 initTabSpectacles();

 printf("\nTeste dune reponse avec un spectacle\n");
   response_init(&resp, 200);
 response_ajouterCleValeur(&resp, creerCleValeur("id", "0"));
        response_ajouterCleValeur(&resp, creerCleValeur("intitule", tabSpectacles[0].intitule));
        //response_ajouterCleValeur(&resp, creerCleValeur("nbPlaces", tabSpectacles[0].nbPlaces));

   response_afficher(&resp);
    



    //printf("\n--- Test response ---\n");
    //afficherResponse(&resp);
    //teste de reponse avec un spectacle

    return 0;
}
