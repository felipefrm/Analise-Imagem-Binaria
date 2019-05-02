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
    }
  }
  return arq;
}


int calculaTamanhoMatriz(FILE* arq){

  int tamanhoMatriz = 0;
  char c;

  while((c = fgetc(arq)) != '\n' && !feof(arq)){

    if (c == '1' || c == '0')
      tamanhoMatriz++;

  }
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

    if(!(i % 2)){    // pega só os elementos pares do arquivo (elementos contendo os valores da matriz)
      mat[lin][col] = c - 48; // conversão de char para inteiro
      col++;
    }
  }
  return mat;
}

int checkValoresMatriz(int **mat, int tamanhoMatriz){
  for (int i=0; i<tamanhoMatriz; i++){
    for (int j=0; j<tamanhoMatriz; j++){
      if (mat[i][j] != 1 && mat[i][j] != 0){
        fprintf(stderr, "Matriz inválida!\n");
        return 0;
      }
    }
  }
  return 1;
}

int verificaArqVazio(FILE* arq){
  int tamanho_arq;
  fseek (arq, 0, SEEK_END);               // aponta para o fim do arquivo com fseek()
  if((tamanho_arq = ftell (arq)) == 0){   // retorna o valor da posição do ponteiro com ftell()
    fprintf(stderr, "O arquivo de entrada está vazio!\n");
    return 0;
  }
  rewind(arq);   // retorna o ponteiro para o inicio do arquivo, para os proximos
  return 1;      // procedimentos
}


void imprimeMaiorSubMatriz(FILE* arq, int** mat, int maior, Ponto inicial, int tamanhoMatriz, int paradigma){

  switch (paradigma){     // Imprime a identificação de qual algoritmo é a matriz imprimida
    case 1:
      fprintf(arq, ">>> ALGORITMO DE FORÇA BRUTA <<<\n\n");
      break;
    case 2:
      fprintf(arq, ">>> ALGORITMO GULOSO <<<\n\n");
      break;
    case 3:
      fprintf(arq, ">>> PROGRAMAÇÃO DINAMICA <<<\n\n");
      break;
  }

  fprintf(arq, "  ");
  for (int i=0; i<tamanhoMatriz; i++)
    fprintf(arq, "%c ", i+'a');
  fprintf(arq, "\n");
  for (int i=0; i<tamanhoMatriz; i++){
    fprintf(arq, "%c ", i+'a');
    for (int j=0; j<tamanhoMatriz; j++){
      if ((i >= inicial.x && i < inicial.x + maior) && (j >= inicial.y && j < inicial.y + maior))
        fprintf(arq, "%d ", mat[i][j]);
      else
        fprintf(arq, "  ");
    }
    fprintf(arq, "\n");
  }
  fprintf(arq, "\n\n");
}

void contaTempoProcessador(double *utime, double *stime){
  struct rusage resources;
  getrusage(RUSAGE_SELF, &resources);
  *utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
  *stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
}

void imprimeTempo(double user_time, double system_time, FILE* arq){
  fprintf(arq, "Tempo de execução:\n");
  fprintf(arq, "%fs (tempo de usuário) + %fs (tempo de sistema) = %fs (tempo total)\n\n", user_time, system_time, user_time+system_time);
}

void liberaMatriz(int** mat, int tamanhoMatriz){
  for (int i=0; i<tamanhoMatriz; i++)
    free(mat[i]);
  free(mat);
}

void liberaArquivos(Arquivos *arq){
  fclose(arq->entrada);
  fclose(arq->saida);
  free(arq);
}
