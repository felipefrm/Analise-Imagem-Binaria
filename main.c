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

    if(checkValoresMatriz(mat, tamanhoMatriz)){

      int maior = 0, clock = 0, sub_matriz;
      Ponto inicial;
      Ponto ponto;

      double utime_ant, utime_pos, stime_ant, stime_pos;
      fprintf(arq->saida, " ----------- FORÇA BRUTA ----------\n\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = forcaBruta(mat, tamanhoMatriz, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
      imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

      fprintf(arq->saida, " ----------- FORÇA BRUTA 2 ----------\n\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = forcaBruta2(mat, tamanhoMatriz, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
      imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

      fprintf(arq->saida, " ----------- DIMAMICO ----------\n\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = dinamica(mat, tamanhoMatriz, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
      imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

      fprintf(arq->saida, " ----------- GULOSO ----------\n\n");
      contaTempoProcessador(&utime_ant, &stime_ant);
      maior = guloso(mat, melhor(mat, tamanhoMatriz, &ponto), ponto, &inicial);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos - utime_ant, stime_pos - stime_ant, arq->saida);
      imprimeArqSaida(arq->saida, mat, maior, inicial, tamanhoMatriz);

      liberaPonteiros(arq, mat, tamanhoMatriz);
    }
  }
}
