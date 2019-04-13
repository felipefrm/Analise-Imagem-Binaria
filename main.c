#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "entradaSaida.h"
#include "paradigma.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag){
    int tamanhoMatriz = calculaTamanhoMatriz(arq->entrada);
    int **mat = leituraArqEntrada(arq->entrada, tamanhoMatriz);

    fclose(arq->entrada);

    int maior = 0, clock = 0, sub_matriz;
    Ponto inicial;

    for (int i=0; i<tamanhoMatriz; i++){
      for (int j=0; j<tamanhoMatriz; j++){
        if ((sub_matriz = forcaBruta(i, j, mat, &clock, maior, tamanhoMatriz)) > maior) {
          maior = sub_matriz;
          inicial.x = i;
          inicial.y = j;
        }
      }
    }

    imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);
    liberaPonteiros(arq, mat, tamanhoMatriz);
  }
}
