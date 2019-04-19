#include "entradaSaida.h"
#ifndef PARADIGMA
#define PARADIGMA

int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial);
int submatrizPossivel(int i, int j, int **mat, int *clock, int maior, int tamanhoMatriz);
int forcaBruta2(int **mat, int tamanhoMatriz, Ponto* inicial);
int dinamica(int **matriz,int tamanhoMatriz,Ponto* inicial);
int guloso(int **mat, int tamanhoDiagonal, Ponto ponto, Ponto* inicial);
int maiorDiagonal(int i, int j, int **mat, int tamanhoMatriz);
int melhor(int **mat, int tamanhoMatriz, Ponto* ponto);
// int maiorDiagonal(int i, int j, int **mat, int tamanhoMatriz, int *referencia);
int melhorSolucaoLocal(int **mat, int tamanhoMatriz, Ponto *inicial);
int checkSubMatrizForcaBruta(int **mat, int lin, int col, int range);
int checkSubMatrizGuloso(int **mat, int x, int y, int maior);
int guloso(int **mat, int tamanhoDiagonal, Ponto ponto, Ponto* inicial);

#endif
