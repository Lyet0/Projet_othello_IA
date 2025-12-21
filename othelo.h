#include <stdio.h> 
#include <stdbool.h>
extern int plateau[8][8];
void affichage(int plt[8][8]);

int KelCaz(int joueur, int*x, int*y );

bool Valide(int x, int y);

int SePaPocible(int (*plt)[8], int x, int y, int joueur);

int FeeLePa(int plt[8][8], int x, int y, int joueur) ;

bool Jouable(int plt[8][8], int joueur);

bool fini (int (*plt)[8]);