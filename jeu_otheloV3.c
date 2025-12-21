#include <stdio.h>
#include <stdbool.h>
int plateau[8][8] = {0};


void affichage(int plt[8][8]){
    //Affichage du tableau
    printf("  y = 0 1 2 3 4 5 6 7\n");
    for(int a=0; a<8; a++){
        printf("\nx=%d :",a);
        for(int b=0; b<8; b++){
            printf(" %d",plt[a][b]);
        }
    }
    printf("\n \n");
}

int KelCaz(int joueur, int*x, int*y ){
    //Demande au joueur l'emplacement où il veut jouer ex : 4 3 = milieu haut-gauche
    printf("Joueur %d: veuillez indique une case format (x y) avec x colonne et y ligne, de 0 à 7 et sans les parenthèses.\n", joueur);
    scanf("%d %d", x, y);
    return 1;
}

bool Valide(int x, int y){
    //Vérifie si la case en question appartient au tableau
    int V=false;
    if (((x>-1)&&(x<8))&&((y>-1)&&(y<8))) {
        V = true;
    }
    return V;
}

int SePaPocible(int (*plt)[8], int x, int y, int joueur){
    //Vérifie si le coup est possible, le joue si oui

    int tempcarreepossible = 0;
    int tempossible = 0;
    //Impossibilité à cause de la case pleine
    int possible = 1;
    if (plt[x][y]!=0) {possible = 0;}
    //Possibilité si ligne adverse suivie par pion allié.
    else {
        //Choisir l'une des directons par rapport à la case
        for(int a=-1; a<2; a++){
            for(int b=-1; b<2; b++){ 
                if (Valide(x+a, y+b) && (((a!=0))||(b!=0))) {
                    int opp = 1;
                    //Vérifier dans cette direction la première case, répéter si elle est adverse
                    while (((plt[x+a*opp][y+b*opp] != 0) && Valide(x+a*opp, y+b*opp))&&(tempcarreepossible == 0)) {
                        tempcarreepossible = 0;
                        //Si on atteint une alliée après avoir passé des adverses, 
                        if ((plt[x+a*opp][y+b*opp] == joueur)&& (opp>=1)){
                            tempcarreepossible = 1;
                            tempossible = 1;
                            //Changer ces adverses en alliés
                            for (int k = opp-1; k>0; k--){
                                plt[x+a*k][y+b*k] = joueur;
                            }
                        }
                        opp++;                  
                    }
                }
            }
        }
    }
    if (tempossible == 0) {possible = 0;}
    printf("Possibilité : %d \n", possible);
    return possible;
}
int FeeLePa(int plt[8][8], int x, int y, int joueur) {
    //Vérifie si le coup est possible sans le jouer
    int tempcarreepossible = 0;
    int tempossible = 0;
    //Impossibilité à cause de la case pleine
    int possible = 1;
    if (plt[x][y]!=0) {possible = 0;}
    //Possibilité si ligne adverse suivie par pion allié.
    else {
        //Choisir l'une des directons par rapport à la case
        for(int a=-1; a<2; a++){
            for(int b=-1; b<2; b++){ 
                if (Valide(x+a, y+b) && (((a!=0))||(b!=0))) {
                    int opp = 1;
                    //Vérifier dans cette direction la première case, répéter si elle est adverse
                    while (((plt[x+a*opp][y+b*opp] != 0) && Valide(x+a*opp, y+b*opp))&&(tempcarreepossible == 0)) {
                        tempcarreepossible = 0;
                        //Si on atteint une alliée après avoir passé des adverses, indiquer la possibilité
                        if ((plt[x+a*opp][y+b*opp] == joueur)&& (opp>=1)){
                            tempcarreepossible = 1;
                            tempossible = 1;
                        }
                        opp++;                  
                    }
                }
            }
        }
    }
    if (tempossible == 0) {possible = 0;}
    return possible;
}

bool Jouable(int plt[8][8], int joueur){
    //Vérifie tous les coups, pour savoir si ce joueur peut jouer
    int c = 0;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++){
            c = c + FeeLePa(plt, i, j, joueur);
        }
    }
    if (c==0) {return false;}
    else {return true;}
}

bool fini (int (*plt)[8]){
    //Vérifie si le tableau est plein [Potentiellement redondant]
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (plt[i][j]==0)
                {return false;}
        }
    }
    return true; 
}

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
