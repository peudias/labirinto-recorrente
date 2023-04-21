#include "include/labirinto.h"

int main(){
    Player p;

    p.status = VIVO;
    p.vida = MAX_VIDA;
    p.banco_vida = p.inimigo = p.sacola = p.qtdVisita = p.qtdNaoVisita = 0;

    matrizinput m;
    m.numMatriz = 0;

    auxMatriz aux;
    lerArquivo(&m, &aux);
    p.qtdMaxMatriz = m.qtdMatriz;
    p.qtdTotal = p.qtdMaxMatriz;

    m.numMatriz = aux.numMatriz = 1;
    movimento(&m, &aux, &p);
    printf("\n");

    for(int i = 0; i < p.qtdTotal; i++){
        LidoNaoLido(i + 1, &p.qtdNaoVisita, &p.qtdVisita);
    }

    createRelatorio(&p);
}