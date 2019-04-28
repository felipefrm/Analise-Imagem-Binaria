#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "entradaSaida.h"
#include "paradigma.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)){
    int tamanhoMatriz = calculaTamanhoMatriz(arq->entrada);
    int **mat = leituraArqEntrada(arq->entrada, tamanhoMatriz);

    if (checkValoresMatriz(mat, tamanhoMatriz)){

      int maior = 0;
      Ponto inicial, elemento;
      double utime_ant, utime_pos, stime_ant, stime_pos;

      imprimeMatrizCompleta(arq->saida, mat, tamanhoMatriz);

      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = forcaBruta(mat, tamanhoMatriz, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 1);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = guloso(mat, maiorDiagonal(mat, tamanhoMatriz, &elemento), elemento, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 2);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);

      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = dinamica(mat, tamanhoMatriz, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 3);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);

    }
    liberaMatriz(mat, tamanhoMatriz);
  }
  liberaArquivos(arq);
}
