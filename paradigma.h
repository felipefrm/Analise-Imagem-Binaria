#include "entradaSaida.h"
#ifndef PARADIGMA
#define PARADIGMA

#define FORCABRUTA 1
#define GULOSO 2
#define DINAMICA 3

// Algoritmo Força Bruta
int forcaBruta(int **mat, int tamanhoMatriz, Ponto* inicial);
int submatrizPossivel(int i, int j, int **mat, int maior, int tamanhoMatriz);
int checkSubMatrizForcaBruta(int **mat, int lin, int col, int range);
// Programação Dinamica
int dinamica(int **matriz,int tamanhoMatriz,Ponto* inicial);
int minimo(int x, int y);
// Algoritmo Guloso
int guloso(int **mat, int tamanhoDiagonal, Ponto elemento, Ponto* inicial);
int tamanhoDiagonal(int i, int j, int **mat, int tamanhoMatriz);
int maiorDiagonal(int **mat, int tamanhoMatriz, Ponto* elemento);
int checkSubMatrizGuloso(int **mat, int x, int y, int maior);

#endif
