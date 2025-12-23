#include <stdbool.h>
#include<stdio.h>
#include"spectacle.h"


int main(int argc, char** argv) 
{
	int specSelect = 9999;
	
    init();
	
	//Valeur 99 impossible pour rester dans la boucle while
			int choix = 99;
			
				//Tant que l'utilisateur ne choisit pas 0 on reste dans la boucle
				while(choix != 0) {
			printf("Menu \n\n");
			
						//Il faut choisir un spectacle pour avoir accès aux opérations, il est affiché en rappel, 9999 correspond à l'absence de de choix
			if(specSelect != 9999) 
			{
				printf("Spectacleselectionne: %i %s %i \n", specSelect, tabSpectacles[specSelect].intitule, tabSpectacles[specSelect].nbPlaces);
				}  
				else 
				{
							printf("Pas de spectacles selectionné \n");
				}
							
										//opérations toujours disponibles
										printf("1 selectionner un spectacle \n");
										printf("2 Afficher les spectacles \n");
										
										//opérations disponibles seulement avec un spectacle selectionné
										if(specSelect != 9999) 
										{
				printf("3 Retirer des places \n");
				printf("4 Ajouter des  places \n");
				printf("\n 0 Quitter \n\n");
				}
				
				printf("Entrez votre choix \n");
				scanf("%d", &choix);
				
				printf("Votre choix %i \n", choix);
				
				//traitments des choix
				switch(choix) 
				{
					case 1:
					int idSpectacle;
					
					printf("Entrez l'id du spectacle \n");
				scanf("%d", &idSpectacle);
					specSelect = idSpectacle;
					
					 					 break;
					 case 2:
					 afficher();
					 
					 break;
					 case 3:
					 if(specSelect != 9999) 
					 {
						 int nbPlaces;
						 
						 printf("Entrez le nombbre de places \n");
				scanf("%d", &nbPlaces);
				
						 retirerPlaces(specSelect, nbPlaces);
					 }
					 else 
					 {
						 printf("Operation non ssupportee\n");
					 }
					 
					 break;
					 case 4:
					 	 if(specSelect != 9999) 
						 {
						 int nbPlaces;
						 
						 printf("Entrez le nombbre de places \n");
				scanf("%d", &nbPlaces);
				
						 ajouterPlaces(specSelect, nbPlaces);
					 } 
					 else
					 {
				 printf("Operation non ssupportee\n");
				}
					 break;
					 case 0:
					 return 0;
					 break;
					 default:
					 break;
				}
	}
			
	return 0;
	}
 