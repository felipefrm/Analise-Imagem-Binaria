#include <stdio.h>
#include <stdlib.h>
#include "paradigma.h"
#include "entradaSaida.h"

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial){
  int maior = 0, clock = 0, sub_matriz;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if ((sub_matriz = submatrizPossivel(i, j, mat, &clock, maior, tamanhoMatriz)) > maior) {
        maior = sub_matriz;
        inicial->x = i;
        inicial->y = j;
      }
    }
  }
  return maior;
}

int submatrizPossivel(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz){
  int range = maior + 1;
  int i_range, j_range;
                                          // pega a maior submatriz possivel a partir do ponto [i][j]
  while (1) {
    i_range = range + i;
    j_range = range + j;

    if (i_range > tamanhoMatriz || j_range > tamanhoMatriz){
      return maior;
    }

    if (!checkSubMatrizForcaBruta(mat, i, j, range)){
      return maior;
    }

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

  for (int maior = tamanhoDiagonal; maior >= 0; maior--){
    int ContadorAnda = tamanhoDiagonal - maior + 1;
    for (int i = ponto.x; i < ponto.x + ContadorAnda; i++){
      for (int j = ponto.y; j < ponto.y + ContadorAnda; j++){
        if (checkSubMatrizGuloso(mat, i, j, maior)){
          inicial->x = i;
          inicial->y = j;
          return maior;
        }
      }
    }
  }
}

int maiorDiagonal(int i, int j, int **mat, int tamanhoMatriz){
  int maior_dprincipal= 0, maior_dsecundaria = 0;
  // printf("?");
  while (i < tamanhoMatriz && j < tamanhoMatriz){
    // printf("%d", mat[i][j]);
    if (mat[i][j] == 1)
      maior_dprincipal++;
    else
      break;          // diagonal principal
    i++;
    j++;

  }
  // i=0;
  // while (i < tamanhoMatriz && j >= 0){
  //   if (mat[i][j] == 1)
  //     maior_dsecundaria++;
  //   else
  //     break;          // diagonal secundaria
  //   i++;
  //   j--;
  //
  // }
  // if (maior_dprincipal >= maior_dsecundaria){
  //
    return maior_dprincipal;
  // }
  // else{
  //   return maior_dsecundaria;
  // }
}

int melhor(int **mat, int tamanhoMatriz, Ponto* ponto){
  int maior = 0, diagonal;
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if ((diagonal = maiorDiagonal(i, j, mat, tamanhoMatriz)) > maior){
        maior = diagonal;
        ponto->x = i;
        ponto->y = j;
      }
    }
  }
  printf("maior: %d\n", maior);
  printf("ponto: %dx%d\n", ponto->x, ponto->y);
  return maior;
}





int checkSubMatrizForcaBruta(int **mat, int i, int j, int range){
  for (int lin = i; lin < i + range; lin++){
    for (int col = j; col < j + range; col++){
      if (mat[lin][col] == 0){
        return 0;
      }
    }
  }
  return 1;
}

int checkSubMatrizGuloso(int **mat, int x, int y, int maior){
  for (int i = 0; i < maior; i++) {
    for (int j = 0; j < maior; j++){
        if (!mat[i+x][j+y])
          return 0;
    }
  }
  return 1;
}
