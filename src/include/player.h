#ifndef PLAYER_H
#define PLAYER_H

#define MAX_VIDA 10
#define MAX_BANCO 4

#define VIVO 1
#define MORTO 0

#include<stdbool.h>

typedef struct Player{
    int vida;
    int qtdVisita;      //letra A
    int sacola;         //letra B
    int qtdNaoVisita;   //letra C
    int inimigo;        //letra D
    int qtdTotal;       //qtd total de matrizes
    int banco_vida;
    int qtdMaxMatriz;
    bool status;
}Player;

#endif