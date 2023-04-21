#ifndef UTIL_H
#define UTIL_H

#define PAREDE -1
#define INIMIGO -9

#define VISITADO 1
#define N_VISITADO 0

#define VERMELHO "\x1b[31m"
#define VERDE "\x1b[32m"
#define VERMELHO_BACKGROUND "\x1b[41m"
#define VERDE_BACKGROUND "\x1b[42m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

#include<stdio.h>

void printCor(int cor);

#endif