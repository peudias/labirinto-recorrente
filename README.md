# Algoritmo Labirinto Recorrente

<p>
<div style="display: inline-block;">

![C](https://img.shields.io/badge/-C-05122A?style=flat&logo=Cplusplus)&nbsp;
![Visual Studio Code](https://img.shields.io/badge/-Visual%20Studio%20Code-05122A?style=flat&logo=visual-studio-code&logoColor=007ACC)&nbsp;

</p>

## Apresentando o problema

Um garoto se encontra perdido em um labirinto, o qual é compreendido como uma matriz cujas posições de sua localização é dada por um valor x,y dessa estrutura.

Trata-se de um jogo inteiramente automático e aleatório. O garoto precisa percorrê-lo, encontrando obstáculos como paredes intransponíveis `#` ou `-1`, itens que podem lhe conceder vidas, bem como perigos que podem tirá-las `*` ou `-9`. O objetivo do jogo é concluir todo o trajeto, escolhendo movimentos ao acaso, de forma a chegar ao final sem perder todas as vidas. Em caso de fracasso, o personagem perde todas as vidas e, consequentemente, o jogo é perdido.

## Regras

1 - Criar um sistema que leia K matrizes quadradas no tamanho NxN.

2 - O programa deve enumerá-las, de forma a deixá-las organizadas para processamento.  

3 - A partir da primeira matriz, tem como regras:

  > (a) avançar para a próxima coluna; 

  > (b) retroceder para coluna anterior; 

  > (c) saltar para a linha de baixo; 
  
  > (d) saltar para a linha de cima;

  > (e) ir em diagonal para baixo.
  
  > (e) ir em diagonal para cima.

  ![exemplomatriz](https://user-images.githubusercontent.com/84406892/233808930-39043b46-b0b7-48ce-abd8-4691a551779b.png)
  
  > Obs:. Setas verdes indicam que o player <strong>PODE</strong> seguir aquele caminho. 
  
5 - Para caminhar, deve optar de forma aleatória a próxima casa.

6 - Quanto às paredes `#`, não há muito o que fazer a não ser desviar e continuar a rota. 

7 - Já os perigos `*`, a cada passada, tende a subtrair 1 de vida de um total de 10.

8 - Ao alcançar a primeira ou última linha da matriz, o player irá se teletransportar aleatoriamente para uma outra matriz, e repete todo o processo novamente. 

9 - Ao ficar sem pontos de vida, o algoritmo deve parar e indicar o fim de jogo.

10 - Ao decorrer do jogo, a cada passo correto sob uma estrada, o player consome um item, subtraindo esse do valor que compõe a posição x,y. 

11 - A cada subtração bem sucedida, essa vai para um banco de vida que quando cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.

12 - Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados.

13 - O player inicia a jornada com zero itens e com vida máxima (10).

## Regras Especiais

14 - Caso o player chegue a um determinado número x de caminhada sem consumir itens, e ainda esteja vivo, vence.

15 - Se o player iniciar o jogo em uma parede, automaticamente finaliza o jogo e gera empate.

16 - Caso as matrizes possuam apenas um local disponível e o player esteja preso neste local entre paredes (spawnou nessa posição), estando impossibilitado de se mover, o player vence.

## Sobre o Labirinto Recorrente

### Resolução do problema

A seguir, três seções das quais abordo a resolução do problema, desde a [entrada de dados](https://github.com/phpdias/labirinto-recorrente/blob/main/README.md#entradas-de-dados-necess%C3%A1rias), [saída de dados](https://github.com/phpdias/labirinto-recorrente/blob/main/README.md#sa%C3%ADdas-obtidas) e uma rápida explicação de cada uma das [funções imeplementadas](https://github.com/phpdias/labirinto-recorrente/blob/main/README.md#explicando-um-pouco-sobre-o-c%C3%B3digo) no programa.

### Entradas de dados necessárias

No programa existe uma pasta nomeada como `dataset`, que dentro contém um documento chamado `input.data`.

Este documento pode ser gerado através do seguinte repositório git, que foi utilizado como referência: [Generate Data To Maze](https://github.com/mpiress/GenerateDataToMaze) [^1]

Analogamente, também pode ser digitado manualmente pelo usuário, mas não é o intuito que utilize dessa forma.

Para exemplificar, utilizarei o seguinte arquivo `input.data`, gerado por mim através do repositório citado acima.

### Arquivo input.data

No exemplo a seguir, estão as informações sobre o tamanho da matriz e quantas matrizes serão analisadas neste programa.

Observe que a primeira linha do arquivo é onde se encontram as entradas NxN da matriz e também a quantidade de matrizes que serão utilizadas no jogo.

Nos blocos subsequentes, a cada oito linhas (para este exemplo), separados por uma linha em branco, encontram-se as matrizes.

Nessa imagem é possível visualizar três das seis matrizes que existem distintas entre si no total.

![input.data](https://user-images.githubusercontent.com/84406892/233810364-27f6f968-2683-449c-872a-41874dfc4612.png)
  
### Saídas obtidas

Ao executar o programa, existem 5 possíveis saídas a serem geradas.

Observe que existe um padrão nas impressões. 

Primeiro é impresso uma palavra que indica se o player permaneceu vivo `VICTORY!`, se morreu `WASTED!`, ou se empatou `TIE GAME!`.

Em seguida é mostrado uma breve frase que indica o motivo do encerramento do game, e logo abaixo uma mensagem confirmando que o jogo foi finalizado.

Por fim, uma frase que indica onde o usuário poderá ver o relatório da rodada.

#### VICTORY! - Player conseguiu ZERAR a matriz.

![victory-normal](https://user-images.githubusercontent.com/84406892/233811289-662cc367-e0c0-4d3f-8ff2-6430d854131d.png)

 > Neste caso o player caminhou o suficiente para conseguir zerar toda a trajetória sem zerar a vida, ou seja, sem morrer (Que sorte!).  

#### VICTORY! - Sem consumir itens.

![victory-sem-consumir](https://user-images.githubusercontent.com/84406892/233811304-39ebb074-a511-44fa-8329-a016799ee2f5.png)

> Neste caso o player entrou em um loop em que não morre, mas também não consome itens, então uma regra especial foi criada que, caso chegue a um determinado número x de caminhada, e ainda esteja vivo, vence.

> O cálculo para encontrar este número está disponível na [linha 136](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L136).

#### VICTORY! - Player não consegue se mover.

![victory-3](https://user-images.githubusercontent.com/84406892/233811310-f0dbc8df-bc58-458f-a986-f27f6c460647.png)

> Neste caso, a matriz possui apenas um local disponível e o player está preso neste local entre paredes, logo não consegue se mover, mas também não está com a vida zerada.

#### WASTED! - Player morreu.

![wasted](https://user-images.githubusercontent.com/84406892/233811321-bc02a368-8365-4fef-bf85-5845a9be09f1.png)

> Neste caso o player está com a vida zerada e morreu.

#### TIE GAME!

![tie-game](https://user-images.githubusercontent.com/84406892/233811317-263943b9-9d3a-4d8d-a6ae-51b5d4f45472.png)

> Esta é uma regra especial em que, se o player iniciar em uma parede, automaticamente finaliza o jogo.

> Uma vez que ainda estará com sua vida total mas não conseguiu vencer por outros meios, é declarado como empate.

### Arquivo output.data

Este arquivo é onde a função logs() faz seu trabalho. 

É um arquivo onde mostra exatamente por onde o player passou (indicado por `>X<`), além de também mostrar o mapa do jogo, incluindo onde estão os inimigos (`-9`) e as paredes (`-1`).

Utilizando como exemplo o `input.data` acima, onde possui seis Matrizes 8x8, obteve-se o seguinte resultado:

![output](https://user-images.githubusercontent.com/84406892/233817051-cc35f960-f7f0-46d7-bb69-ab763d469944.png)

Note na parte direita da imagem que o arquivo pode ser bem extenso dependendo do volume de dados a serem processados e caminho percorrido pelo jogador.

### Arquivo relatorio.data

Este arquivo é onde a função createRelatorio() faz seu trabalho.

É um arquivo que mostra informações mais detalhadas sobre a jornada do player durante a execução do programa.

Alguns exemplos são: quantidade de `casas visitadas` e `não visitadas`, soma total dos `itens consumidos`, quantidade de `perigos enfrentados`, quantidade de `vida e status` do player.

![relatorio.data](https://user-images.githubusercontent.com/84406892/233817243-84adac74-f240-4862-a97e-fd1d469e8c79.png)

### Explicando um pouco sobre o código

#### O algoritmo por completo possui 16 funções. 

### Funções presentes na [util.c](https://github.com/phpdias/labirinto-recorrente/blob/main/src/util.c). 

1. void printCor(int cor);

> Função localizada na [linha 3](https://github.com/phpdias/labirinto-recorrente/blob/main/src/util.c#L3).

> Esta é uma função que foi utilizada para o processo de criação do algoritmo. Serve apenas para pintar as paredes de azul e os inimigos de vermelho. 

> Não é uma função que aparece para o usuário final. Foi utilizada apenas no processo de desenvolvimento.

### Funções presentes na [labirinto.c](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c). 

1. bool checkMovimento(matrizinput *m, int x, int y);

> Função localizada na [linha 3](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L3).

> Esta é uma função para o processo checagem de movimento. Verifica se as casas ao redor do player são ou não parede. 

2. bool checkMatrizZerada(auxMatriz *aux);

> Função localizada na [linha 91](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L91). 

> Esta é uma função para o processo de checar se a matriz está zerada, ou seja, se os valores disponíveis para trajetória estão em zero.

3. int qtdVisita(auxMatriz *m, int check);

> Função localizada na [linha 99](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L99). 

> Esta é uma função para o processo de checar a quantidade de casas visitadas.

4. void movimento(matrizinput *m, auxMatriz *aux, Player *p);

> Função localizada na [linha 109](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L109). 

> Esta é a função para o processo de movimento do player.

> Aqui também está presente as mensagens de vitória, derrota e empate.

### Funções presentes na [arquivo.c](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c). 

1. void lerCheckpoint(matrizinput *m);

> Função localizada na [linha 3](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L3). 

> Por sempre estar alternando entre matrizes, manter todas elas em RAM pode ser custoso, logo se fez necessário utilizar arquivos para manter o último checkpoint de modificação da matriz.

> Sempre que utiliza-se do teletransporte, é feito o salvamento da matriz atual para pegar ela novamente quando precisar.

2. void lerBinario(auxMatriz *aux);

> Função localizada na [linha 40](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L40). 

> Mesma lógica do lerCheckpoint(); 

> Difere apenas que é a matriz que guarda se passou ou não pelo caminho.

3. void lerArquivo(matrizinput *m, auxMatriz *aux);

> Função localizada na [linha 77](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L77). 

> Tem como funcionalidade abrir o arquivo `input.data`, e não sendo possível realizar essa ação, imprimirá uma mensagem indicando tal erro. Do contrário, tendo êxito em abrir o arquivo, essa função irá ler as informações dentro do arquivo. Também é responsável por lidar com a possibilidade do arquivo `input.data` ter espaços em branco no final da última matriz, fazendo com que isso não interfira no resultado desejado.

4. void primeiraLinha(char *str, int *Nlinha, int *Ncoluna, int *qtdMatriz);

> Função localizada na [linha 123](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L123). 

> Tem como funcionalidade tokenizar a primeira linha do arquivo `input.data`. É a função responsável por fazer o programa reconhecer que a primeira linha será a correspondente aos valores de N da matriz NxN e também a quantidade de matrizes.

5. void tokenizar(char *str, int **matriz, int contadorLinha);

> Função localizada na [linha 145](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L145). 

> Tem como funcionalidade tokenizar. É a função responsável por reconhecer as matrizes e acessar a posição apropriada da matriz.

6. void init_matrizAux(matrizinput *m, auxMatriz *aux);

> Função localizada na [linha 165](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L165). 

> Faz alocação dinâmica para trabalhar com a matriz.

> Inicializa os valores.

7. void checkpoint(matrizinput *m);

> Função localizada na [linha 188](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L188). 

> Faz salvamento da matriz buscar a mesma quando precisar.

> Essa função cria a matriz que é lida no lerCheckpoint();

8. void checkpoint_binaria(auxMatriz *aux);

> Função localizada na [linha 210](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L210).

> Mesma lógica da função checkpoint();

> Diferença que trabalha no arquivo com a matriz binária, que utiliza apenas `0` e `1`.

9. void logs(matrizinput *m, int x, int y);

> Função localizada na [linha 232](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L232).

> Esta é uma função para a criação do log pós rodada do jogo. 

> Responsável por mostrar informações como: Onde o player está, qual matriz está, qual posição está, para onde o player se moveu.


10. void LidoNaoLido(int N, int *naoVisita, int *visita);

> Função localizada na [linha 266](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L266).

> Função para verificar na matriz binária quais posições são 0 ou 1.


11. void createRelatorio(Player *p);

> Função localizada na [linha 310](https://github.com/phpdias/labirinto-recorrente/blob/main/src/arquivo.c#L310).

> Esta é uma função para a criação do relatório pós rodada do jogo. 

> Responsável por mostrar informações como: Quantidade de cadas diferentes visitadas e não visitadas, soma total dos itens consumidos, quantos perigos foram enfrentados, quantidade de vida do player e seu status.

### Arquivos .h

No geral contêm declarações de funções, variáveis, constantes e outras definições que são compartilhadas entre diferentes arquivos do código, mas abaixo, detalhes de um arquivo em específico.

### Arquivo [const.h](https://github.com/phpdias/labirinto-recorrente/blob/main/src/include/const.h). 

> Nesse arquivo possui os `#define` de:

> PAREDE, representado por `-1`.

> PERIGOS, representado por `-9`.

> Algumas outras definições, como por exemplo `visitado` e `não visitado`, para auxiliar na contagem, e também algumas definições de `cores`, para melhorar a impressão do resultado no console.

## Conclusão

Sobre o game em si, é notório que é muito difícil que o player permaneça vivo, sobretudo em matrizes quadráticas cada vez maiores e em maior quantidade.

Contudo com regras especiais criadas, existem meios que facilitam a vitória do player em sua jornada.

Sobre o custo computacional, é difícil dar um resultado com precisão, visto que o custo pode variar imensamente devido ao volume de dados. Quanto maior for a quantidade de matrizes e também a quantidade de linhas x coluna, maior será o custo.

Por outro lado, no código foram utilizados meios para tentar minimizar o custo, como por exmeplo nas funções `lerCheckpoint` e `lerBinario`, que, como já foi explicado na seção sobre os códigos, por sempre estar alternando entre matrizes, manter todas elas em RAM pode acabar sendo bastante custoso, e dessa forma se fez necessário utilizar arquivos individuais para minimizar o impacto.

Vale ainda destacar que o percurso "escolhido" (que é de forma aleatória) pelo player pode afetar o custo computacional, uma vez que, caso o jogador ande por todas as casas até zerar a matriz, terá um custo maior do que caso consiga finalizar sem precisar percorrer todas as posições.



## Compilação e Execução

Este algoritmo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
|  `make r`              | Realiza o `make clean`, `make` e `make run` juntos                                                |

## Contatos

<div style="display: inline-block;">

<a href="https://t.me/phpdias" target="_blank">
  <img align="center" src="https://img.shields.io/badge/-phpdias-05122A?style=flat&logo=telegram" alt="telegram"/>
</a>
  
<a href="https://linkedin.com/in/phpd" target="_blank">
  <img align="center" src="https://img.shields.io/badge/-phpd-05122A?style=flat&logo=linkedin" alt="linkedin"/>
</a>

<a style="color:black" href="mailto:phpdias@outlook.com?subject=[GitHub]%20O%20Labirinto%20Recorrente">
 <img align="center" src="https://img.shields.io/badge/-phpdias@outlook.com-05122A?style=flat&logo=email" alt="email"/>
</a>

</div>

## Referências

[^1]: [GitHub](<https://github.com/mpiress/GenerateDataToMaze>)


