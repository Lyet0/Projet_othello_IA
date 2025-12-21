#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "userNetwork.h"
#include "othelo.h"
int plateau_de_jeu[8][8] = {0};


#define BLACK 0  
void update_tab(int plt[8][8],int bouge,int couleur)
	{
	plt[bouge/8][bouge%8]=couleur;
	}
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
	 	if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
					 update_tab(plateau_de_jeu,g->move,g->currentPlayer);
				}
			}
		}
	 	else { 		
			g->move=65; // si scanf correct cette valeur est modifiée, sinon cela terminera la partie. 
			// recuperation du coup sur stdin 
			printf("Enter your move:\n");
			g->move = 44; 
			printf("playing move %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8);
			doMoveOthello(g);
			update_tab(plateau_de_jeu,g->move,g->currentPlayer);
	// envoie du coup à l'adversaire 
	   	}
		g->currentPlayer=!g->currentPlayer; 
	} 
	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	freeGameOthello(g);
	return 0; 
}



	



	
