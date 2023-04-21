#ifndef LABIRINTO_H
#define LABIRINTO_H

#include<stdbool.h>
#include<time.h>

#include "arquivo.h"
#include "player.h"

typedef struct configRelatorio{
    int read;
    int notRead;
}relatorio;

bool checkMovimento(matrizinput *m, int x, int y);
bool checkMatrizZerada(auxMatriz *aux);
int qtdVisita(auxMatriz *m, int check);
void movimento(matrizinput *m, auxMatriz *aux, Player *p);

#endif