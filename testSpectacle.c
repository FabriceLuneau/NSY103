#include <stdbool.h>
#include<stdio.h>
#include"spectacle.h"


int main(int argc, char** argv) 
{
	//int id;
//char intitule[50];
//int nbPlaces;

	//printf("Entrer l'id du spectacle \n");
	//scanf("%i", id);
	
	//printf("Entrer l'intitule du   spectacle \n");
	//scanf("%s", intitule);
	
	//printf("Entrer le nombre de place du spectacle \n");
	
	init();
	
	//afficher();
	
	
    //char chaine[] = "intitule=Hamlet;nbPlaces=50";
	
    //struct spectacle s = creerSpectacleDepuisChaine(chaine);
    //ajouterSpectacle(s);
	    
        char chaine[] =
        "intitule=Hamlet;nbPlaces=50,"
        "intitule=Macbeth;nbPlaces=30,"
        "intitule=Othello;nbPlaces=40";

    	        		int nb = creerDesSpectaclesDepuisChaine(chaine);
		
		printf("nb : %i \n", nb);
		
	
	
	
	
	afficher();
	

	return 0;
	}
 