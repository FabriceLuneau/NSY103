#include <stdbool.h>
#include<stdio.h>
#include"spectacle.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include"request.h";
#include"response";


/*
Version question 1 avec tubes anonymes
*/
int main(int argc, char** argv) 
{
	//initialisation des données, le tableau est dans le header spectacle
	//les, deux processus auront leur copie et se synchroniseront ensuite
	init();

	//déclaration des tubes on se place du cote serveur pourles noms
int outcoming[2];
pipe(outcoming);

	   if(outcoming == -1)
   {
         perror("pipe creation failled");
         return errno;
   } 
	
	int incoming[2];
	pipe(incoming);

	if(incoming == -1)
   {
         perror("pipe creation failled");
         return errno;
   }
		
	//creation du processus enfant
	pid_t res = fork();

	   if(res == -1)
   {
         perror("fork failled");
         return errno;
   }
	
	//division en processus clieent et enfan 
	if(res == 0) 
	{
		printf("Lancement du processusc client %i \n", getpid());

		//fermeture des descripteurs inutiles
		        close(incoming[0]);
        close(outcoming[1]);

		
	//valeur impossible de choix  pour le démarage
	int specSelect = 9999;
	
	//Valeur d'action 99 impossible pour rester dans la boucle while
			int choix = 99;
			
				//Tant que l'utilisateur ne choisit pas 0 on reste dans la boucle
				while(choix != 0) {
        struct request req; 
					
			printf("Menu \n\n");
			
						//Il faut choisir un spectacle pour avoir accès aux opérations, il est affiché en rappel, 9999 correspond à l'absence de choix
			if(specSelect != 9999) 
			{
				printf("Spectacle selectionne: %i %s %i \n", specSelect, tabSpectacles[specSelect].intitule, tabSpectacles[specSelect].nbPlaces);
				}  
				else 
				{
							printf("Pas de spectacles selectionne \n");
				}
							
										//operations toujours disponibles
										printf("1 selectionner un spectacle \n");
										printf("2 Afficher les spectacles \n");
										
										//operations disponibles seulement avec un spectacle selectionne
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

						 req.idSpectacle) = specSelect; 
req.nbPlaces = nbPlaces;

        bool resultat; 

        write(incoming[1], &req, sizeof(req));
        read(outcoming[0], &resultat, sizeof(resultat)); 
						 
        if (resultat) {  
						 {
	printf("places retirees \n");
					 }
					 else 
					 {
						 printf("Places insufisantepour la demande s\n");
					 }
					 }
					 break;
					 case 0:
close(incoming[0]);
	close(outcoming[1])
	
					 return 0;
					 break;
					 default:
					 printf("Operation non supportee\n");
					 break;
				}

	}
	}
	else
	{
		//partie serveur
		
//fermeture des descripteurs intutiles
		close(incoming[1]);
        close(outcoming[0]);

		while(1) 
		{
			        struct request req;
			
        read(incoming[0], &req, sizeof(req));

			        bool ok = retirerPlaces(req.idSpectacle, req.nbPlaces);

			        write(outcoming[1], &ok, sizeof(ok)); 
		}

//section inataignable le client quite dans sa partie 
		//et le serveurdoit être coupe avec ctrl + c, les ressources seront libéré par le system  
	}
			
	return 0;
	}
 