#include "include/arquivo.h"

void lerCheckpoint(matrizinput *m){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/checkpoint/checkpoint_%d.data", m->numMatriz);

    FILE *file = fopen(str, "r");

    char *result, linha[100];
    int contador = 0;
    int controle = 1;

    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
    } else{
        while(!feof(file)){
            result = fgets(linha, sizeof(linha), file);

            size_t tamanho = strlen(linha);
            if(linha[tamanho - 1] == '\n') linha[tamanho - 1] = 0;

            if(result){
                if(controle == 1){
                    controle = 0;
                    primeiraLinha(linha, &m->Nlinha, &m->Ncoluna, &m->qtdMatriz);
                    m->matriz = (int **)malloc(sizeof(int *) * m->Nlinha);
                    for(int i = 0; i < m->Nlinha; i++){
                        m->matriz[i] = (int *)malloc(sizeof(int) * m->Nlinha);
                    }
                } else if(strlen(linha) > 1){
                    tokenizar(linha, m->matriz, contador);
                    contador++;
                }
            }
        }
    }
    fclose(file);
}

void lerBinario(auxMatriz *aux){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/binaria/binaria_%d.data", aux->numMatriz);

    FILE *file = fopen(str, "r");

    char *result, linha[100];
    int contador = 0;
    int controle = 1;

    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
    } else{
        while(!feof(file)){
            result = fgets(linha, sizeof(linha), file);

            size_t tamanho = strlen(linha);
            if(linha[tamanho - 1] == '\n') linha[tamanho - 1] = 0;

            if(result){
                if(controle == 1){
                    controle = 0;
                    primeiraLinha(linha, &aux->Nlinha, &aux->Ncoluna, &aux->qtdMatriz);
                    aux->matriz = (int **)malloc(sizeof(int *) * aux->Nlinha);
                    for(int i = 0; i < aux->Nlinha; i++){
                        aux->matriz[i] = (int *)malloc(sizeof(int) * aux->Nlinha);
                    }
                } else if(strlen(linha) > 1){
                    tokenizar(linha, aux->matriz, contador);
                    contador++;
                }
            }
        }
    }
    fclose(file);
}

void lerArquivo(matrizinput *m, auxMatriz *aux){
    FILE *file = fopen("dataset/input.data", "r");

    FILE *filelog = fopen("dataset/output.data", "w");
    fclose(filelog);

    char *result, linha[100];
    int contador = 0;
    int controle = 1;

    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
    } else{
        while(!feof(file)){
            result = fgets(linha, sizeof(linha), file);

            size_t tamanho = strlen(linha);
            if(linha[tamanho - 1] == '\n') linha[tamanho - 1] = 0;

            if(result){
                if(controle == 1){
                    controle = 0;
                    primeiraLinha(linha, &m->Nlinha, &m->Ncoluna, &m->qtdMatriz);
                    m->matriz = (int **)malloc(sizeof(int *) * m->Nlinha);
                    for(int i = 0; i < m->Nlinha; i++){
                        m->matriz[i] = (int *)malloc(sizeof(int) * m->Nlinha);
                    }
                } else if(strlen(linha) > 1){
                    tokenizar(linha, m->matriz, contador);
                    contador++;

                    if(contador == m->Nlinha){
                        m->numMatriz++;
                        checkpoint(m);
                        init_matrizAux(m, aux);
                        checkpoint_binaria(aux);
                    }
                } else{
                    contador = 0;
                }
            }
        }
    }
    fclose(file);
}

void primeiraLinha(char *str, int *Nlinha, int *Ncoluna, int *qtdMatriz){
    const char sep[] = " ";
    char *tokens;
    int contador = 3;

    tokens = strtok(str, sep);

    while(tokens != NULL){
        if(contador == 3){
            *Nlinha = atoi(tokens);
        } else if(contador == 2){
            *Ncoluna = atoi(tokens);
        } else if(contador == 1){
            *qtdMatriz = atoi(tokens);
        } else{
            return;
        }
        contador--;
        tokens = strtok(NULL, sep);
    }
}

void tokenizar(char *str, int **matriz, int contadorLinha){
    int contadorColuna = 0;
    const char sep[] = " ";
    char *tokens;

    tokens = strtok(str, sep);

    while(tokens != NULL){
        if(strcmp(tokens, "#") == 0){
            matriz[contadorLinha][contadorColuna] = PAREDE;
        } else if(strcmp(tokens, "*") == 0){
            matriz[contadorLinha][contadorColuna] = INIMIGO;
        } else{
            matriz[contadorLinha][contadorColuna] = atoi(tokens);
        }
        contadorColuna++;
        tokens = strtok(NULL, sep);
    }
}

void init_matrizAux(matrizinput *m, auxMatriz *aux){
    aux->numMatriz = m->numMatriz;
    aux->Nlinha = m->Nlinha;
    aux->Ncoluna = m->Ncoluna;

    aux->matriz = (int **)malloc(sizeof(int *) * aux->Nlinha);
    for(int i = 0; i < aux->Nlinha; i++){
        aux->matriz[i] = (int *)malloc(sizeof(int) * aux->Nlinha);
    }

    for(int i = 0; i < m->Nlinha; i++){
        for(int j = 0; j < m->Ncoluna; j++){
            if(m->matriz[i][j] == PAREDE){
                aux->matriz[i][j] = PAREDE;
            } else if(m->matriz[i][j] == INIMIGO){
                aux->matriz[i][j] = INIMIGO;
            } else{
                aux->matriz[i][j] = N_VISITADO;
            }
        }
    }
}

void checkpoint(matrizinput *m){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/checkpoint/checkpoint_%d.data", m->numMatriz);

    FILE *file = fopen(str, "w");

    if(file == NULL){
        printf(VERMELHO "Não foi possível abrir o arquivo\n" RESET);
    } else{
        fprintf(file, "%d %d %d\n", m->Nlinha, m->Ncoluna, 1);

        for(int i = 0; i < m->Nlinha; i++){
            for(int j = 0; j < m->Ncoluna; j++){
                fprintf(file, "%2d ", m->matriz[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    free(str);
}

void checkpoint_binaria(auxMatriz *aux){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/binaria/binaria_%d.data", aux->numMatriz);

    FILE *file = fopen(str, "w");

    if(file == NULL){
        printf(VERMELHO "Não foi possível abrir o arquivo\n" RESET);
    } else{
        fprintf(file, "%d %d %d\n", aux->Nlinha, aux->Ncoluna, 1);

        for(int i = 0; i < aux->Nlinha; i++){
            for(int j = 0; j < aux->Ncoluna; j++){
                fprintf(file, "%2d ", aux->matriz[i][j]);
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
    free(str);
}

void logs(matrizinput *m, int x, int y){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/output.data");

    FILE *file = fopen(str, "a");

    if(file == NULL){
        printf(VERMELHO "Não foi possível abrir o arquivo\n" RESET);
    } else{
        fprintf(file, "==========================\n");
        fprintf(file, "Matriz atual: %d\n", m->numMatriz);
        fprintf(file, "M[%d][%d]\n", m->Nlinha, m->Ncoluna);
        fprintf(file, "Posição: [x = %d]; [y = %d]\n\n", x, y);

        for(int i = 0; i < m->Nlinha; i++){
            for(int j = 0; j < m->Ncoluna; j++){
                if(i == x && j == y){
                    fprintf(file, " >X< ");
                } else if(m->matriz[i][j] == PAREDE){
                    fprintf(file, "[%2d ]", m->matriz[i][j]);
                } else if(m->matriz[i][j] == INIMIGO){
                    fprintf(file, "[%2d ]", m->matriz[i][j]);
                } else{
                    fprintf(file, "[%2d ]", m->matriz[i][j]);
                }
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }
    fclose(file);
    free(str);
}

void LidoNaoLido(int N, int *naoVisita, int *visita){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/binaria/binaria_%d.data", N);
    //printf("str: %s\n", str);

    FILE *file = fopen(str, "r");

    char *result, linha[100];
    int controle = 1;

    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
    } else{
        while(!feof(file)){
            result = fgets(linha, sizeof(linha), file);

            size_t tamanho = strlen(linha);
            if(linha[tamanho - 1] == '\n') linha[tamanho - 1] = 0;

            if(result){
                if(controle == 1){
                    controle = 0;
                } else if(strlen(linha) > 1){
                    const char sep[] = " ";
                    char *tokens;

                    tokens = strtok(linha, sep);

                    while(tokens != NULL){
                        int val = atoi(tokens);
                        if(val == 0){
                            (*naoVisita)++;
                        } else if(val == 1){
                            (*visita)++;
                        }
                        tokens = strtok(NULL, sep);
                    }
                }
            }
        }
    }
    fclose(file);
}

void createRelatorio(Player *p){
    char *str = (char *)malloc(100);
    sprintf(str, "dataset/relatorio.data");

    FILE *file = fopen(str, "w");

    if(file == NULL){
        printf(VERMELHO "Não foi possível abrir o arquivo\n" RESET);
    } else{
        fprintf(file, "|====================> INFORMAÇÕES SOBRE O PERCURSO <======================|\n");
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "|Player's info:                                                            |\n");
        fprintf(file, "|Jogo foi finalizado e abaixo estão as informações detalhadas da jornada.  |\n");
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Quantidade de casas diferentes visitadas:      [%5d    ]            |\n", p->qtdVisita);   //(a) quantas casas foram percorridas ao todo; 
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Soma total dos itens consumidos pelo player:   [%5d    ]            |\n", p->sacola);      //(b) qual a soma de itens consumidos pelo caminho;
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Quantidade de casas diferentes não visitadas:  [%5d    ]            |\n", p->qtdNaoVisita);//(c) quantas casas da matriz ficaram sem serem exploradas;
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Quantidade de perigos enfrentados pelo player: [%5d    ]            |\n", p->inimigo);     //(d) quantos perigos foram enfrentados ao decorrer do percurso.
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Quantidade total de matrizes:                  [%5d    ]            |\n", p->qtdTotal);
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Quantidade de vida do player:                  [%5d    ]            |\n", p->vida);
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "| => Player Status:                                 [  %5s  ]            |\n", ((p->status == 1) ? "VIVO" : "MORTO"));
        fprintf(file, "|                                                                          |\n");
        fprintf(file, "|==========================================================================|");
    }
    fclose(file);
    free(str);
}