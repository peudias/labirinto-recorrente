Questionário:

1. O código pode ser baixado do git? =============================================================== OK!

2. O código executa com matrizes cujo tamanho é ímpar e imprime resultados corretamente? =========== OK!

3. O código executa com matrizes cujo tamanho é par e imprime resultados corretamente? ============= OK!

4. O código está bem estruturado e organizado? ===================================================== OK!

5. O código bem como a entrada seguem os padrões de pasta e nomes definidos? ======================= OK!

.

6. A documentação apresenta uma discussão sobre o problema?

7. A documentação apresenta como foi pensado a resolução do problema?

8. A documentação apresenta pequenos exemplos para explicar o funcionamento?

9. A documentação apresenta conclusões sobre o trabalho?

10. A documentação detalha a forma como o código deve ser compilado?

# Algoritmo Labirinto Recorrente

<p>
<div style="display: inline-block;">

![C](https://img.shields.io/badge/-C-05122A?style=flat&logo=Cplusplus)&nbsp;
![Visual Studio Code](https://img.shields.io/badge/-Visual%20Studio%20Code-05122A?style=flat&logo=visual-studio-code&logoColor=007ACC)&nbsp;

</p>

## Apresentando o problema

Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor [x][y] dessa estrutura.

Nesse labirinto há paredes que bloqueiam certos passos `#`, perigos que consomem parte de sua vida `*` e `trajetórias` (valores positivos que devem ser subtraídos em 1 a cada passagem).

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

6 - Quanto as paredes `#`, não há muito o que fazer a não ser desviar e continuar a rota. 

7 - Já os perigos `*`, a cada passada, tende a subtrair 1 de vida de um total de 10. Assim, ao ficar sem pontos de vida o algoritmo deve parar e indicar fim de jogo.

8 - Ao alcançar a primeira ou última coluna da matriz, o player irá se teletransportar aleatoriamente para uma outra matriz, e repete todo o processo novamente. 

## Sobre o Labirinto Recorrente

### Resolução do problema

A seguir, três seções das quais abordo a resolução do problema, desde a [entrada de dados](https://github.com/phpdias/caminho-guloso/blob/main/README.md#entradas-de-dados-necess%C3%A1rias), [saída de dados](https://github.com/phpdias/caminho-guloso/blob/main/README.md#sa%C3%ADdas-obtidas) e uma rápida explicação de cada uma das [funções imeplementadas](https://github.com/phpdias/caminho-guloso/blob/main/README.md#explicando-um-pouco-sobre-o-c%C3%B3digo) no programa.

### Entradas de dados necessárias

No programa existe uma pasta nomeada como `dataset`, que dentro contém um documento chamado `input.data`.

Este documento pode ser gerado através do seguinte repositório git, que foi utilizado como referência: [Generate Data To Maze](https://github.com/mpiress/GenerateDataToMaze) [^1]

Analogamente, também pode ser digitado manualmente pelo usuário, mas não é o intuito que utilize dessa forma.

Para exemplificar, utilizarei o seguinte arquivo `input.data`, gerado por mim através do repositório citado acima.

#### Arquivo input.data

No exemplo a seguir, estão as informações sobre o tamanho da matriz e quantas matrizes serão analisadas neste programa.

Observe que a primeira linha do arquivo é onde se encontram as entradas NxN da matriz e também a quantidade de matrizes que serão utilizadas no jogo.

Nos blocos subsequentes, a cada oito linhas (para este exemplo), separados por uma linha em branco, encontram-se as matrizes.

Nessa imagem é possível visualizar três das seis matrizes que existem distintas entre si no total.

![input.data](https://user-images.githubusercontent.com/84406892/233810364-27f6f968-2683-449c-872a-41874dfc4612.png)
  
### Saídas obtidas

Ao executar o programa, existem 5 possíveis saídas a serem geradas.

Observe que existe um padrão nas impressões. 

Primeiro é impresso uma palavra que indica se o player permaneceu vivo `VICTORY!`, se morreu `WASTED!`, ou se empatou `TIE GAME!`.

Em seguida é mostrado uma breve frase que indica o motivo do encerramento do game, e logo abaixo uma mensagem confirmnando que o jogo foi finalizado.

Por fim, uma frase que indica onde o usuário poderá ver o relatório da rodada.

#### VICTORY! - Player conseguiu ZERAR a matriz.

![victory-normal](https://user-images.githubusercontent.com/84406892/233811289-662cc367-e0c0-4d3f-8ff2-6430d854131d.png)

 > Neste caso o player caminhou o suficiente para conseguir zerar toda a trajetória sem zerar a vida, ou seja, morrer (Que sorte!).  

#### VICTORY! - Sem consumir itens.

![victory-sem-consumir](https://user-images.githubusercontent.com/84406892/233811304-39ebb074-a511-44fa-8329-a016799ee2f5.png)

> Neste caso o player entrou em um loop onde não morre mas também não consome itens, então a regra criada foi que, caso chegue a um determinado número x de caminhada, e ainda estando vivo, vence.

> O cálculo para encontrar este número está disponível na [linha 136](https://github.com/phpdias/labirinto-recorrente/blob/main/src/labirinto.c#L136).

#### VICTORY! - Player não consegue se mover.

![victory-3](https://user-images.githubusercontent.com/84406892/233811310-f0dbc8df-bc58-458f-a986-f27f6c460647.png)

> Neste caso, a matriz possui apenas um local disponível e o player está preso neste local entre paredes, logo não consegue se mover.

#### WASTED! - Player morreu.

![wasted](https://user-images.githubusercontent.com/84406892/233811321-bc02a368-8365-4fef-bf85-5845a9be09f1.png)

> Neste caso o player está com a vida zerada e morreu.

#### TIE GAME!

![tie-game](https://user-images.githubusercontent.com/84406892/233811317-263943b9-9d3a-4d8d-a6ae-51b5d4f45472.png)

> Esta é uma regra especial onde, se o player iniciar em uma parede, automaticamente finaliza o jogo.

> Uma vez que ainda estará com sua vida total mas não conseguiu vencer por outros meios, declarei como empate.

### Explicando um pouco sobre o código

O programa em si possui basicamente 6 funções. Todas que irei citar, estão presentes no [caminhoguloso.c](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c). 

- menu( );
> Função localizada na [linha 3](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L3). 



> Tem como funcionalidade chamar a função que faz imprimir, e assim, imprimir a matriz original. Em seguida executar a função que faz caminhar pela matriz, e por fim, imprimir a matriz final, que sairá de forma visual para o usuário, mostrando o caminho percorrido. 

- lerArquivo( );
> Função localizada na [linha 10](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L10). 

> Tem como funcionalidade abrir o arquivo `input.data`, e não sendo possível realizar essa ação, imprimirá uma mensagem indicando tal erro. Do contrário, tendo êxito em abrir o arquivo, essa função irá ler as informações dentro do arquivo. Também é responsável por lidar com a possibilidade do arquivo `input.data` ter espaços em branco no final da última matriz, fazendo com que isso não interfira no resultado desejado.

- primeiraLinha( );
> Função localizada na [linha 53](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L53). 

> Tem como funcionalidade tokenizar a primeira linha do arquivo `input.data`. É a função responsável por fazer o programa reconhecer que a primeira linha será a correspondente aos valores de N da matriz NxN.

- tokenizar( );
> Função localizada na [linha 64](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L64). 

> Tem como funcionalidade tokenizar. É a função responsável por reconhecer as matrizes e acessar a posição apropriada da matriz.

- ImprimeAleatoria( );
> Função localizada na [linha 78](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L78). 

> Tem como funcionalidade imprimir a matriz e também é responsável pela formatação da mesma para a visualização do usuário.

- Contador( );
> Função localizada na [linha 87](https://github.com/phpdias/caminho-guloso/blob/main/src/caminhoguloso.c#L87). 

> Tem como funcionalidade percorrer a matriz. Essa é a função com mais finalidades para o problema. É onde está a lógica do programa para que a matriz seja percorrida corretamente. Também é lá que é feito a soma dos números transitados pelas matrizes, além de ainda ser responsável por imprimir os valores ordenados em que a matriz movimentou.

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

<a style="color:black" href="mailto:phpdias@outlook.com?subject=[GitHub]%20O%20Caminho%20Guloso">
 <img align="center" src="https://img.shields.io/badge/-phpdias@outlook.com-05122A?style=flat&logo=email" alt="email"/>
</a>

</div>

## Referências

[^1]: [GitHub](<https://github.com/mpiress/GenerateDataToMatrix>)


