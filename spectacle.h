#include <stdbool.h>
#include<stdio.h>

int nbSpec;
int specSelect = 9999;


struct spectacle {
    char intitule[50];
    int nbPlaces;
};

struct spectacle tabSpectacles[10];

void init() 
{
    struct spectacle tabTemp[] = {
        {"En attendant Gotot", 10},
        {"Tant qu'il y aura des pommes", 4},
        {"Le cercle des poètes dix par rues", 7},
		{"Notre spam de Paris", 7},
        {"L'inspecteur a ri", 9},
        	};
			
			//copie du tableau local ves le tableau global
			for(int i=0;i < sizeof(tabTemp) / sizeof(tabTemp[0]); i++) {
tabSpectacles[i] = tabTemp[i];
			}
			
//calcule du nombre d'entrées
nbSpec = sizeof(tabTemp) / sizeof(tabTemp[0]); 
}

void afficher() 
{
    printf("Liste des spectacles :\n");
	
    for (int i = 0; i < nbSpec;i++) {
        printf("%d - %s (%d places)\n", i, tabSpectacles[i].intitule, tabSpectacles[i].nbPlaces);
    }
}

bool quantiteEstDisponible(int idSpectacle, int quantiteDemandee) 
{
    int quantiteDisponible = tabSpectacles[idSpectacle].nbPlaces;
    return quantiteDemandee <= quantiteDisponible;
}

bool retirerPlaces(int idSpectacle, int quantiteDemandee) 
{
    if (quantiteEstDisponible(idSpectacle, quantiteDemandee)) {
        tabSpectacles[idSpectacle].nbPlaces -= quantiteDemandee;
        return true;
    } else {
        return false;
    }
}

void ajouterPlaces(int idSpectacle, int quantiteDemandee) 
{
    
        tabSpectacles[idSpectacle].nbPlaces += quantiteDemandee;
        }
		