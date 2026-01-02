#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include "userNetwork.h"
#include "function_othelo.h"
int tab_value[8][8]={
    {60, -20, 20, 5, 5, 20, -20, 60},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {5, -5, 3, 3, 3, 3, -5, 5},
    {20, -5, 15, 3, 3, 15, -5, 20},
    {-20, -40, -5, -5, -5, -5, -40, -20},
    {60, -20, 20, 5, 5, 20, -20, 60}
};
int evaluation(int plt[8][8],int joueur){
    int score = 0;
    for (int i=0; i<64; i++){
        if (plt[i/8][i%8]==joueur){
            score = score + tab_value[i/8][i%8];
        }
        else if (plt[i/8][i%8]==3 - joueur){
            score = score - tab_value[i/8][i%8];
        }
    }

}
int choix(int coup[22]){//à randomiser
    int max = coup[0];
    int index = 0;
    for (int i=1; i<22; i++){
        if (coup[i]>max){
            max = coup[i];
            index = i;
        }
    }
    return index;
}

int min_max(int deep,int plt[8][8],int type,int joueur ){//à optimiser
    if ((deep == 0)||(fini(plt)==true)||!(Jouable(plt, joueur))) {
        return evaluation(plt,joueur);
    }
    int bestscore;
    int coup[22]={-1};
    int nb_coup = couppossible(plt, joueur, coup);
    if (type==1){//MAX
        bestscore =10000; 
        for (int i=0; i<nb_coup;i++){
            int refplt[8][8]={0};
            for (int x=0; x<8; x++){
                for (int y=0; y<8; y++){
                    refplt[x][y]=plt[x][y];
                }
            }
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, joueur);
            refplt[x][y]=joueur;
            int score = min_max(deep-1, refplt, 0, 3 - joueur);
            if (score>bestscore){
                bestscore = score;
            }
        }

    }
    if (type==0){//MIN
        bestscore=10000; 
        for (int i=0; i<nb_coup;i++){
            int refplt[8][8]={0};
            for (int x=0; x<8; x++){
                for (int y=0; y<8; y++){
                    refplt[x][y]=plt[x][y];
                }
            }
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, joueur);
            refplt[x][y]=joueur;
            int score = min_max(deep-1, refplt, 1, 3 - joueur);
            if (score<bestscore){
                bestscore = score;
            }
        }
    }
    return bestscore;
}
int choisircoup (int plt[8][8], int joueur,int deep){
    int coup[22]={-1};
    int nb_coup = couppossible(plt, joueur, coup); 
    int bscore[22]={-10000};
        for (int i=0; i<nb_coup;i++){
            int refplt[8][8];
            for (int x=0; x<8; x++){
                for (int y=0; y<8; y++){
                    refplt[x][y]=plt[x][y];
                }
            }
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, joueur);
            refplt[x][y]=joueur;
            int score = min_max(deep-1, refplt, 1, 3 - joueur);
            bscore[i]=score;
        }
    return coup[choix(bscore)];
}

int alpha_beta(int plt[8][8],int play,int n,int joueur,int alpha,int beta){//à faire

}









/*
int evaluation(int plt[8][8],int play,int n,int joueur){
    if (n==0){return (tab_value[play/8][play%8]);}
    int k = 0; 
    int coup[22]={-1};
    int refplt[8][8]={0};
    for (int x=0; x<8; x++){
        for (int y=0; y<8; y++){
            refplt[x][y]=plt[x][y];
        }
        }
    for (int i; i<64; i++){
        {if (SePaPocible(plt, i/8, i%8, joueur)==1){
            coup[k]=evaluation(plt, i, n-1, 3 - joueur)-evaluation(plt, i, n-1, 3 - joueur);
            plt[i/8][i%8]=0;
            k++;
            for (int x=0; x<8; x++){
                for (int y=0; y<8; y++){
                    refplt[x][y]=plt[x][y];
                }
            }
            }
        }
    }
    return choix(coup)+tab_value[play/8][play%8];
}   
*/