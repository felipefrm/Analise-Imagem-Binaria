#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"

int forcaBruta(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz){
  // (*clock)++;
  // printf("contador: %d\n", *clock);
  int range = maior, flag = 0;
  int i_range, j_range;

  while (1) {

    i_range = range + i;
    j_range = range + j;

    if (i_range > tamanhoMatriz || j_range > tamanhoMatriz)
      return maior;

    for (int lin = i; lin < i_range; lin++){
      for (int col = j; col < j_range; col++){
        if (mat[lin][col] == 0){
          return maior;
        }
      }
    }

    maior = range;
    range++;
  }

  return maior;
}
