#include <stdio.h> 
#include <stdbool.h>
extern int tab_value[8][8];


int choix(int coup[64], int taille);
int min_max(int deep,int plt[8][8],int type,int current_player, int root_player, int balpha) ;
int choisircoup (int plt[8][8], int joueur,int deep);
int evaluation(int plt[8][8],int joueur);
