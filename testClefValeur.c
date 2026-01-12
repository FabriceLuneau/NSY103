#include<stdio.h>
#include"cleValeur.h"
#include"cleValeur.h"
int main(void)
{
    //test de cle valeur
    struct cleValeur cv;

    printf("Test de creation d'une structure cle valeur  avec deux arguments séparés  1\n");
     cv = cleValeur_create("id", "1");
    cleValeur_afficher(&cv);

    printf("Test de creation d'une structure cle valeur  avec une chaine, id=1\n"); 
    cv = cleValeur_createDepuisChaine("id=1");
     cleValeur_afficher(&cv);

    printf("Test de creation d'une structure cle valeur  avec une chaine et un nombbre, id=1\n"); 
    cv = cleValeur_createValeurNombre("id" ,1);
    cleValeur_afficher(&cv);

    return 0;
}
