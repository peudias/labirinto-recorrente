#include "include/labirinto.h"

bool checkMovimento(matrizinput *m, int x, int y){
    if(x < 0 || x == m->Nlinha) return false;
    if(y < 0 || y == m->Ncoluna) return false;

    if(x == 0){ //primeira linha
        if(y == 0){ //primeira coluna
            if(
                m->matriz[x + 0][y + 1] != PAREDE ||
                m->matriz[x + 1][y + 1] != PAREDE ||
                m->matriz[x + 1][y + 0] != PAREDE){
                return true;
            }
        } else if(y == m->Ncoluna - 1){ //ultima coluna
            if(
                m->matriz[x + 0][y - 1] != PAREDE ||
                m->matriz[x + 1][y - 1] != PAREDE ||
                m->matriz[x + 1][y + 0] != PAREDE){
                return true;
            }
        } else{ //entre primeira e ultima coluna
            if(
                m->matriz[x + 0][y + 1] != PAREDE ||
                m->matriz[x + 0][y - 1] != PAREDE ||
                m->matriz[x + 1][y + 0] != PAREDE ||
                m->matriz[x + 1][y + 1] != PAREDE ||
                m->matriz[x + 1][y - 1] != PAREDE){
                return true;
            }
        }
    } else if(x == m->Nlinha - 1){ //ultima linha
        if(y == 0){ //primeira coluna
            if(
                m->matriz[x + 0][y + 1] != PAREDE ||
                m->matriz[x - 1][y + 1] != PAREDE ||
                m->matriz[x - 1][y + 0] != PAREDE){
                return true;
            }
        } else if(y == m->Ncoluna - 1){ //ultima coluna
            if(
                m->matriz[x + 0][y - 1] != PAREDE ||
                m->matriz[x - 1][y - 1] != PAREDE ||
                m->matriz[x - 1][y + 0] != PAREDE){
                return true;
            }
        } else{ //entre primeira e ultima coluna
            if(
                m->matriz[x + 0][y + 1] != PAREDE ||
                m->matriz[x + 0][y - 1] != PAREDE ||
                m->matriz[x - 1][y + 0] != PAREDE ||
                m->matriz[x - 1][y + 1] != PAREDE ||
                m->matriz[x - 1][y - 1] != PAREDE){
                return true;
            }
        }
    } else if(y == 0){ //primeira coluna
        if(
            m->matriz[x + 0][y + 1] != PAREDE ||
            m->matriz[x - 1][y + 0] != PAREDE ||
            m->matriz[x + 1][y + 0] != PAREDE ||
            m->matriz[x + 1][y + 1] != PAREDE ||
            m->matriz[x - 1][y + 1] != PAREDE){
            return true;
        }
    } else if(y == m->Ncoluna - 1){ //ultima coluna
        if(
            m->matriz[x + 0][y - 1] != PAREDE ||
            m->matriz[x - 1][y + 0] != PAREDE ||
            m->matriz[x + 1][y + 0] != PAREDE ||
            m->matriz[x - 1][y - 1] != PAREDE ||
            m->matriz[x + 1][y - 1] != PAREDE){
            return true;
        }
    } else{
        if(
            m->matriz[x + 0][y + 1] != PAREDE ||
            m->matriz[x + 0][y - 1] != PAREDE ||
            m->matriz[x + 1][y + 0] != PAREDE ||
            m->matriz[x - 1][y + 0] != PAREDE ||
            m->matriz[x - 1][y + 1] != PAREDE ||
            m->matriz[x - 1][y - 1] != PAREDE ||
            m->matriz[x + 1][y + 1] != PAREDE ||
            m->matriz[x + 1][y - 1] != PAREDE){
            return true;
        }
    }
    return false;
}

bool checkMatrizZerada(auxMatriz *aux){
    for(int i = 0; i < aux->Nlinha; i++){
        for(int j = 0; j < aux->Ncoluna; j++)
            if(aux->matriz[i][j] == N_VISITADO) return true;
    }
    return false;
}

int qtdVisita(auxMatriz *m, int check){
    int contador = 0;

    for(int i = 0; i < m->Nlinha; i++){
        for(int j = 0; j < m->Ncoluna; j++)
            if(m->matriz[i][j] == check) contador++;
    }
    return contador;
}

void movimento(matrizinput *m, auxMatriz *aux, Player *p){
    if(p->status == MORTO) return;

    srand(time(NULL));
    int x = rand() % m->Nlinha;
    int y = rand() % m->Ncoluna;
    int i, j;
    int xBackup, yBackup;
    int movimentoVazio = 0;
    if(m->matriz[x][y] == PAREDE){
        printf(CINZA "\nTIE GAME!" RESET);
        printf(VERDE "\nPlayer VIVO!" RESET);
        printf(VERMELHO "\nPlayer iniciou na parede.\nJogo finalizado!" RESET);
        printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
        return;
    }

    // printf("[%d] ", m->numMatriz);

    if(checkMovimento(m, x, y)){
        do{
            i = (rand() % 3) - 1; // -1 0 1
            j = (rand() % 3) - 1; // -1 0 1
            xBackup = x;
            yBackup = y;

            movimentoVazio++;
            if(movimentoVazio > (m->Ncoluna * m->Nlinha * m->Nlinha * p->qtdTotal)){
                //printf("foi minha culpa\n");
                printf(VERDE_BACKGROUND "\nVICTORY!" RESET);
                printf(VERDE "\nPlayer VIVO!" RESET);
                printf(VERMELHO "\nPlayer ficou andando sem consumir itens por %d vezes.\nJogo finalizado!" RESET, (m->Ncoluna * m->Nlinha * m->Nlinha * p->qtdTotal));
                printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
                return;
            }
            if(checkMovimento(m, (x + i), (y + j))){
                if(m->matriz[x][y] != PAREDE){
                    if(m->matriz[x][y] == INIMIGO){
                        p->vida--;
                        p->inimigo++;
                        p->banco_vida = 0;

                        if(p->vida == 0){
                            p->status = MORTO;
                            printf(VERMELHO_BACKGROUND "\nWASTED!" RESET);
                            printf(VERMELHO "\nPlayer morreu! \nJogo finalizado." RESET);
                            printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
                            checkpoint(m);
                            aux->numMatriz = m->numMatriz;
                            checkpoint_binaria(aux);

                            return;
                        }
                    } else{
                        if(m->matriz[x][y] > 0){
                            m->matriz[x][y]--;
                            movimentoVazio = 0;
                            p->banco_vida++;
                            p->sacola++;

                            if(p->banco_vida == MAX_BANCO){
                                if(p->vida < 10){
                                    p->vida++;
                                }
                                p->banco_vida = 0;
                            }
                        }
                        if(aux->matriz[x][y] == N_VISITADO){
                            // p->qtdVisita++;
                            aux->matriz[x][y] = VISITADO;
                        }
                    }
                    x += i;
                    y += j;
                    if(m->matriz[x][y] == PAREDE){
                        //printf("eh parede\n");
                        x = xBackup;
                        y = yBackup;
                    }
                } else{
                    x = xBackup;
                    y = yBackup;
                }
                logs(m, x, y);
                // printf("x = %d y = %d\n", x, y);
            } else{ //testar portal
                if(m->matriz[x][y] != PAREDE && m->matriz[x][y] != INIMIGO){
                    if(m->matriz[x][y] > 0){
                        m->matriz[x][y]--;
                        p->banco_vida++;
                        p->sacola++;

                        if(p->banco_vida == MAX_BANCO){
                            if(p->vida < 10){
                                p->vida++;
                            }
                            p->banco_vida = 0;
                        }
                    }
                    if(aux->matriz[x][y] == N_VISITADO) aux->matriz[x][y] = VISITADO;
                }
                checkpoint(m);
                aux->numMatriz = m->numMatriz;
                checkpoint_binaria(aux);

                m->numMatriz = aux->numMatriz = (1 + rand() % p->qtdMaxMatriz);
                lerCheckpoint(m);
                lerBinario(aux);

                // movimento(m, aux, p);

                x = rand() % m->Nlinha;
                y = rand() % m->Ncoluna;

                if(!checkMovimento(m, x, y)){
                    printf(VERDE_BACKGROUND "\nVICTORY!" RESET);
                    printf(VERDE "\nPlayer VIVO!" RESET);
                    printf(VERMELHO "\nNão foi possível se mover.\nJogo finalizado." RESET);
                    printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
                    return;
                }
            }
        } while (checkMatrizZerada(aux) && p->status == VIVO);
        printf(VERDE_BACKGROUND "\nVICTORY!" RESET);
        printf(VERDE "\nPlayer VIVO!" RESET);
        printf(VERDE "\nPlayer conseguiu zerar toda a trajetória.\nJogo finalizado." RESET);
        printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
    } else {
        printf(VERDE_BACKGROUND "\nVICTORY!" RESET);
        printf(VERDE "\nPlayer VIVO!" RESET);
        printf(VERMELHO "\nNão foi possível se mover.\nJogo finalizado." RESET);
        printf("\nAcesse " AZUL "dataset/relatorio.data" RESET " para visualizar informações detalhadas sobre o percurso.\n");
        return;
    }
    checkpoint(m);
    aux->numMatriz = m->numMatriz;
    checkpoint_binaria(aux);
}
