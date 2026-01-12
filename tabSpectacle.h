#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include"spectacle2.h"

const int maxSpectacles = 100;


//permet de compter les éléments valides dans le tableau
//totoposera problème si la varriable globale est supprimée, trouver une solution ou passer à une ttaille defixe, car n'apporte pas grand chose au projet
int nbElements = 0;


/*
*todo sera déplacé dans un header à part
*le tableau sera remplacé par des fonctions preant prenant argument un pointeur tableau
*/
struct spectacle tabSpectaclesGlobal[100];

/*
*Initialise le tableau global avec des données de test
*todo sera déplacé dans un header à part*/
*le tableau sera remplacé par des fonctions preant en argument un pointeur tableau
*/
void tabSpectacle_initTabGlobal() {
    struct spectacle tabTemp[] = {
        {"En attendant Gotot", 10},
        {"Tant qu'il y aura des pommes", 4},
        {"Le cercle des poètes dix par rues", 7},
        {"Notre spam de Paris", 7},
        {"Pouple fiction", 17},
        {"Les oiseaux se crashent pour mourrir", 29}
    };

    //divise le tableau temporaire par la taille d'un élément et obtient la taille
    nbElements = sizeof(tabTemp) / sizeof(tabTemp[0]);

    for (int i = 0; i < nBelements; i++) 
    {
        tabSpectaclesGlobal[i] = tabTemp[i];
    }
    nbSpec = taille;
}
    
/*
*affiche le tableau global
* todo remplacer le tableau global par un passage d'un pointeur tableau
*/
void tabSpectacle_afficher() {
    printf("Liste des spectacles :\n");
    for (int i = 0; i < nbElements; i++) {
        printf("%d - %s (%d places)\n",
               i,
               tabSpectaclesGlobal[i].intitule,
               tabSpectaclesGlobal[i].nbPlaces);
    }
}

/*
 *ajoute une structure spectacle au tableau global 
*si le maximum n'estpas atteint
* ajoute l'élément et incrimente le compteur
*todo remplacer le tableau global par un passage d'un pointeur tableau
*/
bool tabSpectacle_ajouter(struct spectacle spectacle) 
{
    if (nbElements <100) 
    {
        tabSpectaclesGlobal[nbElements] = spectacle;
        nbElements++;

        return true;
    }
else 
{
    return false;
}
}
    
/
/* ajouteretourne un spectacle par l'id du tableau
* todo remplacer le tableau global par un passage d'un pointeur tableau*/
struct spectacle tab_spectacle_getSpectacle(int idSpectacle) 
{
return tabSpectaclesGlobal[idSpectacle];
}

/*
*  Test si la quantité de places est disponible pour l'e spectacle idvia son id dans le tableau 
*/
bool tabSpectacle_quantiteEstDisponible(int idSpectacle, int quantiteDemandee) 
{
    if (idSpectacle < 0 || idSpectacle >= nbSpec) {
        return false;
    }

    return spectacle_quantiteDisponible(tabSpectaclesGlobal[idSpectacle].nbPlaces;
}

/*
 * Décrémente le nombre de places demandées pour l'id spectacle si disponible, retourne un booléen
 */
bool tabSpectacle_retirerPlaces(int idSpactacle, int quantiteDemandee) 
{
    if (idSpectacle < 0 || idSpectacle >= nbSpec) {
        {
            return false;
        }
        }
    return tabSpectacle[i].retirerPlaces())
            }
