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
int choix(int coup[22]){
    int max = coup[0];
    int index = 0;
    for (int i=1; i<22; i++){
        if (coup[i]>max){
            max = coup[i];
            index = i;
        }
    }
    return coup[index];
}
int min_max(){

}
int min_max_adv(){

}
int evaluation(int plt[8][8],int play,int n,int joueur){
    if (n==0){return (tab_value[play/8][play%8]);}
    int k = 0; 
    int coup[22]={0};
    for (int i; i<64; i++){
        {if (FeeLePa(plt, i/8, i%8, joueur)==1){
            plt[i/8][i%8]=joueur;
            coup[k]=evaluation(plt, i, n-1, 3 - joueur)-evaluation(plt, i, n-1, 3 - joueur);
            plt[i/8][i%8]=0;
            k++;
            }
        }
    }
    return choix(coup)+tab_value[play/8][play%8];
}   
int main()
{
    return 0;
}