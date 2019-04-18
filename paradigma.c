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


int forcaBruta2(int **mat, int tamanhoMatriz, Ponto* inicial){

  for (int maior = tamanhoMatriz; maior >= 0; maior--){
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


int minimo(int x, int y){
  if(x < y)
    return x;
  else
  return y;
}


int dinamica(int **matriz, int tamanhoMatriz, Ponto* inicial){
  int i,j,maior = 0;
  int matAux[tamanhoMatriz+1][tamanhoMatriz+1];
  for(i=0;i<tamanhoMatriz+1;i++){
    matAux[0][i] = 0;
    matAux[i][0] = 0;
  }

  for(i=1;i<tamanhoMatriz+1;i++){
    for(j=1;j<tamanhoMatriz+1;j++){
      if(!matriz[i-1][j-1])
          matAux[i][j] = 0;
      else{
        matAux[i][j] = 1 + minimo(matAux[i-1][j], minimo(matAux[i][j-1],matAux[i-1][j-1]));
        if(matAux[i][j] > maior){
          maior = matAux[i][j];
          inicial->x = i-maior;
          inicial->y = j-maior;
        }
      }
    }
  }
  return maior;
}

int guloso(int **mat, int tamanhoDiagonal, Ponto ponto, Ponto* inicial){
  int maior = 0, clock = 0, sub_matriz;
  for (int i=ponto.x; i < ponto.x + tamanhoDiagonal; i++){
    for (int j=ponto.y; j < ponto.y + tamanhoDiagonal; j++){
      // printf("%d ", mat[i][j]);
      if ((sub_matriz = submatrizValida(i, j, mat, &clock, maior, tamanhoDiagonal)) > maior) {
        maior = sub_matriz;
        // printf("maior: %d\n", maior);
        inicial->x = i;
        inicial->y = j;
        }
    }
    // printf("\n");
  }
  // printf("\n%d\n", submatrizValida(1, 1, mat, &clock, maior, tamanhoDiagonal));
  return maior;
}

int maiorDiagonal(int i, int j, int **mat, int tamanhoMatriz){
  int maior = 0;
  // printf("?");
  while (i < tamanhoMatriz && j < tamanhoMatriz){
    // printf("%d", mat[i][j]);
    if (mat[i][j] == 1)
      maior++;
    else
      break;
    i++;
    j++;

  }
  return maior;
}

int melhor(int **mat, int tamanhoMatriz, Ponto* ponto){
  int maior = 0, diagonal;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      // printf("i: %d e j: %d\n", i, j);
      if ((diagonal = maiorDiagonal(i, j, mat, tamanhoMatriz)) > maior){
        // printf("d\n", maior);
        maior = diagonal;
        ponto->x = i;
        ponto->y = j;
      }
    }
  }
  // printf("maior: %d\n", maior);
  // printf("ponto: %dx%d\n", ponto->x, ponto->y);
  return maior;
}



// int maiorDiagonal(int i, int j, int **mat, int tamanhoMatriz,int *referencia){
//   int maior = 0,continuidade = 1;
//   while (i < tamanhoMatriz && j < tamanhoMatriz){
//
//     if (mat[i][j] == 1){
//       maior ++;
//     i++;
//     j++;
//       if(continuidade)
//         if(*referencia < i){
//           *referencia = i;
//         }
//       else
//         continuidade = 1;
//   }else{
//     continuidade = 0;
//   }
//   return maior;
// }
//
// int melhorSolucaoLocal(int **mat, int tamanhoMatriz, Ponto *inicial){
//   int maiorx=0, maiory=0, ref, diagonal;
//   for (int i = 0, j = tamanhoMatriz-1; j <= 0; j--){
//     if (maiorx < (diagonal = maiorDiagonal(i, j, mat,&ref)){
//       maiorx = diagonal;
//     }
//     if (maiory < (diagonal = maiorDiagonal(j, i, mat,&ref)){
//       maiory = diagonal;
//     }
//   }
//   if (maiorx >= maiory){
//     // inicial->x = 0;
//     // inicial->y = j+ref;
//     return maiorx;
//   }
//   else {
//     // inicial->x = j+ref;
//     // inicial->y = 0;
//     return maiory;
//   }
// }


//
// int melhorSolucaoLocal(int **mat, int tamanhoMatriz, Ponto *inicial){
//   int maiorx=0, diagonalx, maiory=0, diagionaly;
//   for (int i = 0, j = tamanhoMatriz-1; j <= 0; j--){
//     if (maiorx < (diagonal = maiorDiagonal(i, j, mat)){
//       maiorx = diagonal;
//       diagonalx = j;
//     }
//     if (maiory < (diagonal = maiorDiagonal(j, i, mat)){
//       maiory = diagonal;
//       diagonaly = j;
//     }
//   }
//   if (maiorx >= maiory){
//     inicial->x = 0;
//     inicial->y = j;
//     return maiorx;
//   }
//   else {
//     inicial->x = j;
//     inicial->y = 0;
//     return maiory;
//   }
// }
