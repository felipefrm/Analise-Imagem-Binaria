#ifndef MATRIZ
#define MATRIZ

struct ponto {
  int x;
  int y;
}; typedef struct ponto Ponto;

struct arquivos {
  FILE* entrada;
  FILE* saida;
  int flag;   // flag para poder retornar 0 ou 1
}; typedef struct arquivos Arquivos;


Arquivos* argumentosEntrada(int argc, char* argv[]);
int calculaTamanhoMatriz(FILE* arq);
int** alocaMatriz(int tamanhoMatriz);
int** leituraArqEntrada(FILE* arq, int tamanhoMatriz);
void imprimeArqSaida(FILE* arq, int** mat, int maior, Ponto inicial, int tamanhoMatriz);
void liberaPonteiros(Arquivos *arq, int** mat, int tamanhoMatriz);

#endif
