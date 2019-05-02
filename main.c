#include <stdio.h>
#include <stdlib.h>
#include "entradaSaida.h"
#include "paradigma.h"

void main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)){
    int tamanhoMatriz = calculaTamanhoMatriz(arq->entrada);
    int **mat = leituraArqEntrada(arq->entrada, tamanhoMatriz);

    if (checkValoresMatriz(mat, tamanhoMatriz)){

      int maior, opcao;
      Ponto inicial, elemento;
      double utime_ant, utime_pos, stime_ant, stime_pos;

      printf("Escolha um paradigma para ver a maior sub-matriz encontrada:\n\n"
      "[1] Força Bruta\n[2] Guloso\n[3] Programação dinâmica\n[0] Todos os paradigmas\n\n>>> ");
      scanf("%d", &opcao);

      switch(opcao){
          case 1:
            maior = forcaBruta(mat, tamanhoMatriz, &inicial);
            imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 0);
            break;
          case 2:
            maior = guloso(mat, maiorDiagonal(mat, tamanhoMatriz, &elemento), elemento, &inicial);
            imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 0);
            break;
          case 3:
            maior = dinamica(mat, tamanhoMatriz, &inicial);
            imprimeMaiorSubMatriz(arq->saida, mat, maior, inicial, tamanhoMatriz, 0);
            break;
          case 0:
            imprimeMaiorSubMatriz(arq->saida, mat, forcaBruta(mat, tamanhoMatriz, &inicial), inicial, tamanhoMatriz, FORCABRUTA);
            imprimeMaiorSubMatriz(arq->saida, mat, guloso(mat, maiorDiagonal(mat, tamanhoMatriz, &elemento), elemento, &inicial), inicial, tamanhoMatriz, GULOSO);
            imprimeMaiorSubMatriz(arq->saida, mat, dinamica(mat, tamanhoMatriz, &inicial), inicial, tamanhoMatriz, DINAMICA);
            break;
          default:
            printf("Não existe esta opção.\n");
      }
    }
    liberaMatriz(mat, tamanhoMatriz);
    liberaArquivos(arq);
  }
}
