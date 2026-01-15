#include <stdio.h>
#include <stdbool.h>
void affichage(int plt[8][8])
    {
    //Affichage du tableau
    printf("  y =0  1  2  3  4  5  6  7");
    for(int a=0; a<8; a++){
        printf("\nx=%d ",a);
        for(int b=0; b<8; b++){
            if (plt[a][b]==0){
                printf("\033[42m   \033[0m");
            }
            if (plt[a][b]==2){
                printf("\033[47m   \033[0m");
            }
            if (plt[a][b]==1){
                printf("\033[40m   \033[0m");
            }
        }
    }
    printf("\n \n");
}
    /*
    {
        for (int i=0; i<8; i++){
            for (int j=0; j<8; j++){
                printf("%d ", plt[i][j]);
            }
            printf("\n");
        }
    }*/

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

int SePaPocible(int (*plt)[8], int x, int y, int joueur){//à optimiser
    int tempcarreepossible = 0;
    int tempossible = 0;
	int temppossible3=1;
    //Impossibilité à cause de la case pleine
    int possible = 1;
    if (Valide(x, y)==false){
        return 0;
    }
    if (plt[x][y]!=0) {possible = 0;}
    //Possibilité si ligne adverse suivie par pion allié.
    else {
        //Choisir l'une des directons par rapport à la case
        for(int a=-1; a<2; a++){
            for(int b=-1; b<2; b++){ 
                if ((Valide(x+a, y+b)) && ((a!=0)||(b!=0))) {
                    int opp = 1;
					tempcarreepossible = 0;	//Fonctionne connard ou je te /clear
                    //Vérifier dans cette direction la première case, répéter si elle est adverse
                    while (((plt[x+a*opp][y+b*opp] != 0) && Valide(x+a*opp, y+b*opp))&&(tempcarreepossible == 0)) {
                        //Si on atteint une alliée après avoir passé des adverses, 
                        if ((plt[x+a*opp][y+b*opp] == joueur)&& (opp>=1)){
                            tempcarreepossible = 1;
                            tempossible = 1;
                            //Changer ces adverses en alliés
							temppossible3=1;
                            for (int k = opp-1; k>0; k--){
								if (plt[x+a*k][y+b*k]==joueur){
									temppossible3=0;
								}
                                plt[x+a*k*temppossible3][y+b*k*temppossible3] = joueur;
                            }
                        }
                        opp++;                  
                    }
                }
            }
        }
    }
	if (tempossible==1){plt[x][y]=joueur;}
    if (tempossible == 0) {possible = 0;}
    return possible;

}
/*int FeeLePa(int plt[8][8], int x, int y, int joueur) {
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
}*/
int FeeLePa(int plt[8][8], int x, int y, int joueur) {//à optimiser
    // 1. SÉCURITÉ : On vérifie d'abord si la case existe (Gère le cas PASS 8 0)
    if (!Valide(x, y)) {
        return 0;
    }

    // 2. La case doit être vide
    if (plt[x][y] != 0) {
        return 0; 
    }

    int adversaire = 3 - joueur; // Si joueur 1 -> adv 2, si joueur 2 -> adv 1

    // 3. On teste les 8 directions
    for(int a = -1; a <= 1; a++){
        for(int b = -1; b <= 1; b++){ 
            if (a == 0 && b == 0) continue; // Pas de direction nulle

            int k = 1;
            // On avance TANT QU'ON voit des pions ADVERSES
            while (Valide(x + a*k, y + b*k) && plt[x + a*k][y + b*k] == adversaire) {
                k++;
            }

            // Si on a avancé d'au moins une case (k > 1) 
            // ET qu'on tombe sur un pion à NOUS juste après
            if (k > 1 && Valide(x + a*k, y + b*k) && plt[x + a*k][y + b*k] == joueur) {
                return 1; // Le coup est valide, pas besoin de chercher plus loin
            }
        }
    }

    return 0; // Aucune direction valide trouvée
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
int couppossible (int plt[8][8], int joueur, int coup[64]){//à optimiser
    //Remplit le tableau coup avec les coups possibles
    int k = 0;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++){
            if (FeeLePa(plt, i, j, joueur)==1){
                coup[k]=i*8+j;
                k++;
            }
        }
    }
    return k;
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
