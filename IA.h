#include <stdio.h> 
#include <stdbool.h>
extern int tab_value[8][8];
typedef struct{
    int plt[8][8];
    short int minmax;
    int profondeur;
    int* possible_coups[22];
    int score; 
}noeud;

int choix(int coup[22]);
int min_max();
int choisircoup (int plt[8][8], int joueur, int deep);
int evaluation(int plt[8][8],int joueur);
