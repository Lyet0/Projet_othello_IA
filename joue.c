#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "userNetwork.h"
#include "function_othelo.h"
#include "IA.h"
int plateau_de_jeu[8][8] = {0};


#define BLACK 0  
int main(int argc,char *argv[]) 
{
	plateau_de_jeu[3][3] = 2; 
	plateau_de_jeu[4][4] = 2; 
	plateau_de_jeu[4][3] = 1; 
	plateau_de_jeu[3][4] = 1;
	game *g;
	int move; 

	if ((g=allocateGameOthello()) == NULL ) { return(EXIT_FAILURE); }

	if (argc > 4 ) { 
		g->userId=atoi(argv[3]); 
		g->address=argv[2]; 
		g->port=atoi(argv[4]);
	}
	else { fprintf(stderr,"usage : %s <userPasswd> <ip ad> <userId> <Port>\n",argv[0]); exit(-1); }
	

	if (registerGameOthello(g,argv[1]) < 0 ) { exit(-1); }	// test de l'authentification auprès du serveur 

	if (startGameOthello(g) < 0 ) { // cet appel est bloquant en attendant un adversaire 
		fprintf(stderr,"error Starting Game\n"); 
		return (EXIT_FAILURE); 
	}
	// debut de partie
	while (g->state == PLAYING && !feof(stdin)) {
		int x, y={0};
		printf("My color : %s\n", g->myColor==BLACK?"Black":"White");
		if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
					SePaPocible(plateau_de_jeu,g->move/8,g->move%8,g->currentPlayer+1);
					plateau_de_jeu[g->move/8][g->move%8]=g->currentPlayer+1;
				}
			}
		}
	 	else { 		
			int coup=choisircoup(plateau_de_jeu,g->myColor+1,7); 
			if (coup==-1) {
				coup=64; //pass
			}
			printf("%d\n",coup);
			g->move =coup;
			printf("playing move %d ",g->move);
			doMoveOthello(g);
			x=g->move/8;
			y=g->move%8;
			SePaPocible(plateau_de_jeu,x ,y,g->currentPlayer+1);
			printf(" (x=%d,y=%d)\n",x,y);
			plateau_de_jeu[x][y]=g->currentPlayer+1;
			affichage(plateau_de_jeu);
			// envoie du coup à l'adversaire 
	   	}
		g->currentPlayer=!g->currentPlayer; 
	} 
	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	freeGameOthello(g);
	return 0; 
}



	



	
