#include <stdio.h>
#include <stdbool.h>
#include "function_othelo.h"
int plateau[8][8] = {0};
int main(){
    //Initialisation du tableau, Vide = 0, Noir = 1, Blanc = 2
    plateau[3][3] = 2; plateau[4][4] = 2; plateau[4][3] = 1; plateau[3][4] = 1;
    int joueur = 1;
    int x; int y;
    while ((fini(plateau)==false) && ((Jouable(plateau, 3 - joueur )||(Jouable(plateau, joueur))))) {
        affichage(plateau);
        KelCaz(joueur, &x, &y);
        while (SePaPocible(plateau, x, y, joueur)==0) {
            KelCaz(joueur, &x, &y);
        }
        plateau[x][y] = joueur;
        if (Jouable(plateau, 3 - joueur))
            {joueur = 3 - joueur;} //Changement de joueur pour le prochain tour
    }
    return 0;
}

/*CONversion cases : 
>>  x*8+y = case
<< x = case / 8, y = case % 8

                            for (int k = opp-1; k>0; k--){
								if ()
                                plt[x+a*k*temppossible3][y+b*k*temppossible3] = joueur;

*/
