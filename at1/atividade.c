/*
 * Nome: Gabriel de Freitas Adolfo
 * Registro acadêmico: XXXXXX
 * Atividade: Gerenciamento de Processos na Prática
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MATRIX_SIZE 10

static void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int transpose) {
  int row;
  int column;

  printf("Matriz %s! PID = %d:\n", transpose ? "transposta" : "original",
         getpid());

  for (row = 0; row < MATRIX_SIZE; row++) {
    for (column = 0; column < MATRIX_SIZE; column++) {
      transpose ? printf("%4d", matrix[column][row])
                : printf("%4d", matrix[row][column]);
    }
    printf("\n");
  }
  printf("\n");
}

static void init_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
  int row;
  int column;
  int value = 1;

  printf("Inicializando a matriz! PID = %d:\n", getpid());

  for (row = 0; row < MATRIX_SIZE; row++) {
    for (column = 0; column < MATRIX_SIZE; column++) {
      matrix[row][column] = value++;
    }
  }
}

int main(void) {
  int matrix[MATRIX_SIZE][MATRIX_SIZE];
  int status = 0;
  pid_t p;

  printf("Sou o pai - PID = %d\n", getpid());

  init_matrix(matrix);
  p = fork();

  if (p < 0) {
    fprintf(stderr, "Criacao do novo processo falhou!\n");
    exit(-1);
  }

  if (p == 0) {
    const char* cmd =
        "count=$(curl -L -s 'https://ge.globo.com/motor/formula-1/' | "
        "egrep -oi 'Hamilton' | wc -l); "
        "printf 'Ocorrencias encontradas para \'Hamilton\' no GloboEsporte "
        "sobre Fórmula 1 (https://ge.globo.com/motor/formula-1/): %s\\n' "
        "\"$count\"";

    printf("Iniciando a execucao do processo filho...\n");
    printf("Sou o filho de PPID = %d, tenho PID = %d\n", getppid(), getpid());
    printf("PID do filho (no filho): %d\n", p);

    execlp("sh", "sh", "-c", cmd, (char*)NULL);

    printf("Filho com parada de execucao forçada!\n");
    exit(-1);
  }

  if (p > 0) {
    printf("PID do filho (no pai): %d\n\n", p);

    print_matrix(matrix, 0);
    print_matrix(matrix, 1);

    printf("Pai aguardando o filho terminar...\n");
    wait(&status);

    printf("Status de terminacao do filho = %s\n",
           (WEXITSTATUS(status) == 0 ? "Sucesso" : "Falha"));
    printf("Filho completou a execucao!\n");

    printf("Pai terminou! PID: %d, PPID (PID do pai): %d.\n", getpid(),
           getppid());

    exit(0);
  }

  return 0;
}