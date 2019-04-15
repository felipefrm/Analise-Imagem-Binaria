#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"
#include "entradaSaida.h"

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial){
  int maior = 0, clock = 0, sub_matriz;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if ((sub_matriz = submatrizValida(i, j, mat, &clock, maior, tamanhoMatriz)) > maior) {
        maior = sub_matriz;
        inicial->x = i;
        inicial->y = j;
      }
    }
  }
  return maior;
}

int submatrizValida(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz){
  int range = maior + 1;
  int i_range, j_range;
                                          // pega a maior submatriz possivel a partir do ponto [i][j]
  while (1) {
    i_range = range + i;
    j_range = range + j;

    if (i_range > tamanhoMatriz || j_range > tamanhoMatriz)
      return maior;

    if (!checkSubMatrizForcaBruta(mat, i, j, range)){
      return maior;
    }
    // for (int lin = i; lin < i_range; lin++){
    //
    //   for (int col = j; col < j_range; col++){
    //     (*clock)++;
    //     // printf("contador: %d\n", *clock);
    //     if (mat[lin][col] == 0){
    //       return maior;
    //     }
    //   }
    // }

    maior = range;
    range++;
  }

  return maior;
}


int guloso(int **mat, int tamanhoMatriz, Ponto* inicial){

  for (int maior = tamanhoMatriz; maior > 0; maior--){
    int ContadorAnda = tamanhoMatriz - maior + 1;
    for (int i = 0; i < ContadorAnda; i++){
      for (int j = 0; j < ContadorAnda; j++){
        if (checkSubMatrizGuloso(mat, i, j, maior)){
          inicial->x = i;
          inicial->y = j;
          return maior;
        }
      }
    }
  }
}
