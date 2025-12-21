#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <errno.h>
#include <stdbool.h>

#define N 8 
#define BLACK 0 
#define WHITE 1 
#define EMPTY 2 


#ifdef CONVENTIONOK 
typedef int8_t monType ;
#else 
typedef int32_t monType;
#define MYBLACK 2 
#define MYWHITE 1 
#define MYEMPTY 0 
#endif 

bool Valide(int x, int y){
    //Vérifie si la case en question appartient au tableau
    int V=false;
    if (((x>-1)&&(x<8))&&((y>-1)&&(y<8))) {
        V = true;
    }
    return V;
}

// Assume we have a function that modifies our board 
int faireCoupOthello(monType plt[N][N],int8_t coup,int8_t joueur) {
    //Vérifie si le coup est possible, le joue si oui
	int x = coup / 8 ; int y = coup % 8;
    int tempcarreepossible = 0;
    int tempossible = 0;
	int temppossible3=1;
    //Impossibilité à cause de la case pleine
    int possible = 1;
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
	plt[x][y]=joueur;
    if (tempossible == 0) {possible = 0;}
    printf("Possibilité : %d \n", possible);
    return possible;

}

void afficheTableau(monType tableau[N][N]) 
{
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
#ifdef CONVENTIONOK
			printf("%c ",(tableau[i][j]==EMPTY)?'.':(tableau[i][j]==BLACK)?'B':'W'); 
#else 
			printf("%c ",(tableau[i][j]==MYEMPTY)?'.':(tableau[i][j]==MYBLACK)?'B':'W'); 
#endif
		} 
		printf("\n"); 
	}
	printf("\n\n\n"); 

}

int dansTableau(int i, int j) 
{
	return ((i>=0) && (i<N) && (j>=0) && (j<N)); 
}


int lireCoup(int8_t *coup,int8_t *couleur, FILE *savedGames) 
{
	int res=0; 
	res=fread(coup,sizeof(int8_t),1,savedGames); 
	if (res) res=fread(couleur,sizeof(int8_t),1,savedGames); 
#ifndef CONVENTIONOK 
	*couleur=(*couleur==BLACK)?MYBLACK:MYWHITE; 
#endif 
	return res; 
}

int lireTableau(monType tableau[N][N], FILE *savedGames) 
{
	int res; 
#ifdef CONVENTIONOK 
	res=fread(tableau,sizeof(int8_t),64,savedGames); 
#else 
	int8_t temp[N][N]; 
	res=fread(temp,sizeof(int8_t),64,savedGames); 
	for (int i=0;i<N*N;i++) {
		tableau[i/8][i%8]=((temp[i/8][i%8]==BLACK)?MYBLACK:(temp[i/8][i%8]==WHITE)?MYWHITE:MYEMPTY); 
	}
#endif 
	return res; 
}
int compareTableau(monType tableau[N][N],monType reference[N][N]) 
{
	int erreur=0; 
	for (int i=0;i<64;i++) { 
		erreur+=(tableau[i/8][i%8]!=reference[i/8][i%8]); 
	}
	return erreur; 
}


int main(int argc, char *argv[])
{
	// tableau before and after (ie. expected after) 
	monType monTableau[N][N]; // 1 Black, 0 white , 2 empty 
	monType after[N][N]; 
	int8_t  c,p; // coup de 0 à 63 pour un coup valide, 64 pour PASS. 
		     // p player (1 Black, 0 white) 
	int errors=0,nberrors=0; 
	int nbtest=0; 
	FILE *fi; 

	if (argc<2) { printf("%s <file>\n",argv[0]); exit (1); } 
	if ((fi=fopen(argv[1],"r"))!=NULL) {
		while (lireTableau(monTableau,fi)) {
			nbtest++; 
			printf("#test %d tableau initial\n",nbtest); 
			afficheTableau(monTableau); 
			lireCoup(&c,&p,fi); 
			lireTableau(after,fi); 
			faireCoupOthello(monTableau,c,p);
			printf("coup de %d en %d %d\n",p,c/8,c%8); 
			printf("tableau de ref\n"); 
			afficheTableau(after); 
			printf("tableau calculé\n"); 
			afficheTableau(monTableau); 
			if ((errors=compareTableau(monTableau,after))) { 
				printf("%d error(s) in test %d\n",errors,nbtest);
		       		nberrors+=errors;
			}
		}
	fclose(fi); 
	} else {
		perror("cannot open file"); 
	}
	printf("J'ai détecté %d Erreur(s)\n",nberrors); 
}
