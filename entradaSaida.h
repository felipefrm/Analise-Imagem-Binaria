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
int checkValoresMatriz(int **mat, int tamanhoMatriz);
void imprimeArqSaida(FILE* arq, int** mat, int maior, Ponto inicial, int tamanhoMatriz);
void contaTempoProcessador(double *utime, double *stime);
void imprimeTempo(double user_time, double system_time, FILE* arq);
void liberaPonteiros(Arquivos *arq, int** mat, int tamanhoMatriz);
int checkSubMatrizForcaBruta(int **mat, int lin, int col, int range);
int checkSubMatrizGuloso(int **mat, int y, int x, int maior);

#endif
