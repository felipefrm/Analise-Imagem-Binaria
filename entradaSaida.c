#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/resource.h>
#include "entradaSaida.h"

Arquivos* argumentosEntrada(int argc, char* argv[]){

  Arquivos* arq = malloc(sizeof(Arquivos));   // armazena os ponteiros dos arquivos
  int opcao;
  arq->flag = 1;                                  // passados por linha de comando em uma struct
  if (argc < 5){
    fprintf(stderr, "Use: ./tp2 -i [ARQUIVO DE ENTRADA DE DADOS] -o [ARQUIVO DE SAIDA]\n");
    arq->flag = 0;
    return arq;
  }
  while((opcao = getopt(argc, argv, "i:o:"))!= -1) { // recebe-se os argumentos por meio
                                                     // da funcao getopt()
    switch(opcao) {
      case 'i':
        if(!(arq->entrada = fopen(optarg, "r"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
      case 'o':
        if(!(arq->saida = fopen(optarg, "w"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
    }
  }
  return arq;
}


int calculaTamanhoMatriz(FILE* arq){

  int tamanhoMatriz = 0;

  while(!feof(arq))
    if (fgetc(arq) == '\n')
      tamanhoMatriz++;

  rewind(arq);

  return tamanhoMatriz;
}

int** alocaMatriz(int tamanhoMatriz){

  int **matriz = (int**)malloc(tamanhoMatriz*sizeof(int*));
  for (int i=0; i<tamanhoMatriz; i++)
    matriz[i] = (int*)malloc(tamanhoMatriz*sizeof(int));

  return matriz;
}

int** leituraArqEntrada(FILE* arq, int tamanhoMatriz){

  int **mat = alocaMatriz(tamanhoMatriz);
  char c;
  int lin = 0, col = 0;

  for (int i = 0; i < 2*tamanhoMatriz*tamanhoMatriz; i++){
    c = fgetc(arq);
    if(col >= tamanhoMatriz){
      col = 0;
      lin++;
    }

    if(!(i % 2)){
      mat[lin][col] = c - 48; // conversão de char para inteiro
      col++;
    }
  }

  return mat;
}

void imprimeArqSaida(FILE* arq, int** mat, int maior, Ponto inicial, int tamanhoMatriz){

  fprintf(arq, "Maior: %d\n", maior);
  fprintf(arq, "Posição: [%d][%d]\n\n", inicial.x, inicial.y);

  fprintf(arq, "Matriz original (%dx%d): \n\n", tamanhoMatriz, tamanhoMatriz);
  fprintf(arq, "  ");
  for (int i=0; i<tamanhoMatriz; i++)
    fprintf(arq, "%c ", i+65);
  fprintf(arq, "\n");
  for (int i=0; i<tamanhoMatriz; i++){
    fprintf(arq, "%c ", i+65);
    for (int j=0; j<tamanhoMatriz; j++)
      fprintf(arq, "%d ", mat[i][j]);
    fprintf(arq, "\n");
  }

  fprintf(arq, "\n\nMaior sub-matriz encontrada (%dx%d): \n\n", maior, maior);

  fprintf(arq, "  ");
  for (int i=0; i<tamanhoMatriz; i++)
    fprintf(arq, "%c ", i+65);
  fprintf(arq, "\n");
  for (int i=0; i<tamanhoMatriz; i++){
    fprintf(arq, "%c ", i+65);
    for (int j=0; j<tamanhoMatriz; j++){
      if ((i >= inicial.x && i < inicial.x + maior) && (j >= inicial.y && j < inicial.y + maior))
        fprintf(arq, "%d ", mat[i][j]);
      else
        fprintf(arq, "  ");
    }
    fprintf(arq, "\n");
  }
}

void contaTempoProcessador(double *utime, double *stime){
  struct rusage resources;
  getrusage(RUSAGE_SELF, &resources);
  *utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
  *stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
}

void imprimeTempo(double user_time, double system_time, FILE* arq){
  fprintf(arq, "Tempo de execução:\n\n");
  fprintf(arq, "%fs (tempo de usuário) + %fs (tempo de sistema) = %fs (tempo total)\n\n", user_time, system_time, user_time+system_time);
}

void liberaPonteiros(Arquivos *arq, int** mat, int tamanhoMatriz){

  for (int i=0; i<tamanhoMatriz; i++)
    free(mat[i]);

  free(mat);
  fclose(arq->saida);
  // fclose(arq->entrada);
  free(arq);
}

int checkSubMatrizForcaBruta(int **mat, int i, int j, int range){
  for (int lin = i; lin < i + range; lin++){
    for (int col = j; col < j + range; col++){
      // (*clock)++;
      // printf("contador: %d\n", *clock);
      if (mat[lin][col] == 0){
        return 0;
      }
    }
  }
  return 1;
}

int checkSubMatrizGuloso(int **mat, int y, int x, int maior){
  int yB,xB;
  for (yB = 0; yB < maior; yB++) {
    for (xB = 0; xB < maior; xB++){
        if (!mat[yB+y][xB+x])
          return 0;
    }
  }
  return 1;
}
