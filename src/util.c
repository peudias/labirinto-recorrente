#include "include/const.h"

void printCor(int cor){
    printf("[ ");

    switch(cor){
    case 1:
        printf(AZUL "#" RESET);
        break;
    case 2:
        printf(VERMELHO "*" RESET);
        break;
    default:
        break;
    }

    printf(" ]");
}