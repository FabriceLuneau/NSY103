#include <stdbool.h>
#include<stdio.h>
#include"spectacle.h"


int main(int argc, char** argv) 
{
	printf("Création et ajout d'un spectacle); \n");

	//int id;
//char intitule[50];
//int nbPlaces;

	//printf("Entrer l'id du spectacle \n");
	//scanf("%i", id);
	
	//printf("Entrer l'intitule du   spectacle \n");
	//scanf("%s", intitule);
	
	//printf("Entrer le nombre de place du spectacle \n");

	struct spectacle spec = spectacle_creer("Le chat beaute", 2);
	spectacle_ajouterSpectacle(spec);
spectacle_afficherTout();

printf("\n initialisation du jeu de test");
		
	spectacle_initTabGlobal();


	return 0;
	}
 