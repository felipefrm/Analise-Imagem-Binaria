#ifndef MATRIZ
#define MATRIZ

struct ponto {
  int x;
  int y;
}; typedef struct ponto Ponto;

struct arquivos {
  FILE* entrada;
  FILE* saida;
  int flag;   // flag para poder retornar 0 em caso de erro
}; typedef struct arquivos Arquivos;


Arquivos* argumentosEntrada(int argc, char* argv[]);
int calculaTamanhoMatriz(FILE* arq);
int** alocaMatriz(int tamanhoMatriz);
int** leituraArqEntrada(FILE* arq, int tamanhoMatriz);
int checkValoresMatriz(int **mat, int tamanhoMatriz);
int verificaArqVazio(FILE* arq);
void imprimeMatrizCompleta(FILE* arq, int** mat, int tamanhoMatriz);
void imprimeMaiorSubMatriz(FILE* arq, int** mat, int maior, Ponto inicial, int tamanhoMatriz, int paradigma);
void contaTempoProcessador(double *utime, double *stime);
void imprimeTempo(double user_time, double system_time, FILE* arq);
void liberaMatriz(int** mat, int tamanhoMatriz);
void liberaArquivos(Arquivos *arq);


#endif
