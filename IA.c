#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
#include "userNetwork.h"
#include "function_othelo.h"
#include <time.h>
int Sbonus = 0;
int tab_value[8][8]={
    {100, -20, 30, 10, 10, 30, -20, 100},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {30, -2, 5, 2, 2, 5, -2, 30},
    {10, -2, 2, 4, 4, 2, -2, 10},
    {10, -2, 2, 4, 4, 2, -2, 10},
    {30, -2, 5, 2, 2, 5, -2, 30},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {100, -20, 30, 10, 10, 30, -20, 100}
};
time_t letemps;
int final_evaluation(int plt[8][8],int joueur){
    int score = 0;
    for (int i=0; i<64; i++){
        if (plt[i/8][i%8]==joueur){
            score = score + 1;
        }
        else if (plt[i/8][i%8]==3 - joueur){
            score = score - 1;
        }
    }
    return score;
}
int evaluation(int plt[8][8],int joueur){
    int score = 0;
    int casalier=0; 
    int casenimi=0; 
    for (int i=0; i<64; i++){
        if (plt[i/8][i%8]==joueur){
            if ( ((i==1) )||(i==8)){
                if (plt[0][0]==(joueur)){
                    score = score -tab_value[i/8][i%8];
                }
                else{ score = score + tab_value[i/8][i%8];}
            }
            else if ( ((i==6) )||(i==15)){
                if (plt[0][7]==(joueur)){
                    score = score -tab_value[i/8][i%8];
                }
                else{ score = score + tab_value[i/8][i%8];}
            }
            else if ( ((i==48) )||(i==57)){
                if (plt[7][0]==(joueur)){
                    score = score -tab_value[i/8][i%8];
                }
                else{ score = score + tab_value[i/8][i%8];}
            }
            else if ( ((i==54) )||(i==62)){
                if (plt[7][7]==(joueur)){
                    score = score -tab_value[i/8][i%8];
                }
                else{ score = score + tab_value[i/8][i%8];}
            }
            else{
            score = score + tab_value[i/8][i%8];}
        }
        else if (plt[i/8][i%8]==(3 - joueur)){
            score = score - tab_value[i/8][i%8];
        }
    }
    return score;
}
int choix(int coup[64], int taille){//à randomiser
    int index = 0;
    for (int i=0; i<taille; i++){
        if (coup[i]>coup[index]){
            index = i;
        }
    }
    if (rand()%2==0){
        for (int j=0; j<64; j++){
            if ((coup[index]*0.85<coup[j])&&(coup[j]<coup[index])){
                index = j;
            }
        }
    }
    return index;
}

int min_max(int deep,int plt[8][8],int type,int current_player, int root_player,int alpha,int beta ){//à optimiser
    if (!Jouable(plt, current_player)){
        if (!Jouable(plt, 3 - current_player)){
            return final_evaluation(plt,root_player);
        }
        else {
        return min_max(deep-1, plt, 1-type,  3-current_player, root_player,alpha,beta) ;}
    }
    if ((deep == 0)||(fini(plt)==true)) {
        return evaluation(plt,root_player);
    }
    int bestscore;
    int coup[64];
    memset(coup, -1000, 64);
    int nb_coup = couppossible(plt, current_player, coup);
    if (type==1){//MAX
        bestscore =-100000; 
        for (int i=0; i<nb_coup;i++){
            if(time(NULL)-letemps>14){
                bestscore=evaluation(plt,root_player);
                break;
            }
            int refplt[8][8]={0};
            memcpy(refplt, plt, sizeof(int) * 64);
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, current_player);
            int score = min_max(deep - 1, refplt, 0, 3 - current_player, root_player, alpha, beta);            
            if (score>bestscore){
                bestscore = score;
            }
            if (bestscore > alpha){
                bestscore = alpha;
            }
            if (beta <=alpha){
                return bestscore;
            }
            
        }

    }
    if (type==0){//MIN
        bestscore=100000; 
        for (int i=0; i<nb_coup;i++){
            if(time(NULL)-letemps>14){
                bestscore=evaluation(plt,root_player);
                break;
            }
            int refplt[8][8]={0};
            memcpy(refplt, plt, sizeof(int) * 64);
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, current_player);
            int score = min_max(deep - 1, refplt, 0, 3 - current_player, root_player, alpha, beta);            
            if (score<alpha){
                return score;
            }
            if (score<bestscore){
                bestscore = score;
            }
            if (bestscore < alpha){
                 beta = bestscore;
            }
            if (beta <=alpha){
                return bestscore;
            }
            
        }
    }
    return bestscore;
}
int choisircoup (int plt[8][8], int joueur,int deep){
    int coup[64];
    time(&letemps);
    memset(coup, -1, 64);
    int nb_coup = couppossible(plt, joueur, coup); 
    if (nb_coup==0){
        return -1;
    }
    int bscore[64];
    memset(bscore, -1000000, 64);
        for (int i=0; i<nb_coup;i++){
            int refplt[8][8];
            memcpy(refplt, plt, sizeof(int) * 64);
            //Appliquer le coup
            int x = coup[i]/8;
            int y = coup[i]%8;
            SePaPocible(refplt, x, y, joueur);
            refplt[x][y]=joueur;
            int score = min_max(deep - 1, refplt, 0, 3 - joueur, joueur,-10000,10000);
            bscore[i]=score;
        }
    return coup[choix(bscore,nb_coup)];
}