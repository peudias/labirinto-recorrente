#ifndef ARQUIVO_H 
#define ARQUIVO_H

#include "const.h"
#include "player.h"

#include<stdlib.h>
#include<string.h>

typedef struct configMatriz{
    int **matriz;

    int numMatriz;

    int Nlinha;
    int Ncoluna;
    int qtdMatriz;
}matrizinput;

typedef struct configMatrizAux{
    int **matriz;

    int numMatriz;

    int Nlinha;
    int Ncoluna;
    int qtdMatriz;
}auxMatriz;

void lerArquivo(matrizinput *m, auxMatriz *aux);
void primeiraLinha(char *str, int *Nlinha, int *Ncoluna, int *qtdMatriz);
void tokenizar(char *str, int **matriz, int contadorLinha);
void init_matrizAux(matrizinput *m, auxMatriz *aux);

void checkpoint(matrizinput *m);
void checkpoint_binaria(auxMatriz *aux);
void createRelatorio(Player *p);

void logs(matrizinput *m, int x, int y);
void LidoNaoLido(int N, int *naoVisita, int *visita);

void lerCheckpoint(matrizinput *m);
void lerBinario(auxMatriz *aux);
#endif