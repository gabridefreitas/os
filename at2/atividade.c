/*
 * Nome: Gabriel de Freitas Adolfo
 * Registro acadêmico: XXXXXXX
 * Atividade: Cálculo de Números Perfeitos Usando Threads
 *
 * Descrição:
 * Programa em C que utiliza múltiplas threads para encontrar os 5 primeiros
 * números perfeitos usando a Fórmula de Euclides-Euler.
 *
 * Utiliza mutex para sincronização e exclusão mútua ao acessar a variável
 * global que controla qual expoente de Mersenne será testado.
 *
 * Fórmula de Euclides-Euler:
 * Um número perfeito par tem a forma: 2^(p-1) * (2^p - 1)
 * onde (2^p - 1) é um número primo de Mersenne.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define NUM_THREADS 4
#define PERFECT_NUMBERS_NEEDED 5

/* Expoentes de Mersenne conhecidos que geram números primos */
/* Mais expoentes para garantir paralelismo real entre threads */
static const int MERSENNE_EXPONENTS[] = {2,  3,  5,  7,   13,  17,  19,
                                         31, 61, 89, 107, 127, 521, 607};
static const int NUM_EXPONENTS =
    sizeof(MERSENNE_EXPONENTS) / sizeof(MERSENNE_EXPONENTS[0]);

/* Variáveis globais compartilhadas */
static int current_index = 0; /* Índice no array de expoentes */
static int perfect_count = 0; /* Quantidade de números perfeitos encontrados */
static pthread_mutex_t mutex; /* Mutex para sincronização */

/*
 * Calcula 2^exponent
 */
static long power_of_2(int exponent) {
  long result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= 2;
  }
  return result;
}

/*
 * Calcula um número perfeito a partir do expoente de Mersenne
 * Fórmula: 2^(p-1) * (2^p - 1)
 */
static long calculate_perfect_number(int mersenne_exp) {
  long part1 = power_of_2(mersenne_exp - 1);
  long mersenne_prime = power_of_2(mersenne_exp) - 1;
  return part1 * mersenne_prime;
}

/*
 * Função executada por cada thread
 * Cada thread processa um expoente de Mersenne
 */
static void* thread_worker(void* arg) {
  long thread_id = (long)arg;
  int index;
  int mersenne_exp;
  long perfect_number;

  while (1) {
    /* Seção crítica: obter o próximo índice a ser processado */
    pthread_mutex_lock(&mutex);

    /* Se já encontramos o número desejado, sai */
    if (perfect_count >= PERFECT_NUMBERS_NEEDED ||
        current_index >= NUM_EXPONENTS) {
      pthread_mutex_unlock(&mutex);
      break;
    }

    index = current_index;
    current_index++;

    pthread_mutex_unlock(&mutex);

    /* Seção não-crítica: calcular o número perfeito */
    mersenne_exp = MERSENNE_EXPONENTS[index];
    perfect_number = calculate_perfect_number(mersenne_exp);

    /* Seção crítica: atualizar contador e imprimir resultado */
    pthread_mutex_lock(&mutex);

    /* Verifica novamente se já alcançamos o limite antes de incrementar */
    if (perfect_count < PERFECT_NUMBERS_NEEDED) {
      printf("Thread %ld encontrou o número perfeito: %ld\n", thread_id,
             perfect_number);
      perfect_count++;
    }

    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

/*
 * Função para obter tempo em milissegundos
 */
static long get_time_ms(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main(void) {
  pthread_t threads[NUM_THREADS];
  long start_time, end_time, elapsed_time;
  int i;

  printf("=== Busca de Números Perfeitos com Threads ===\n");
  printf("Usando a Fórmula de Euclides-Euler: 2^(p-1) * (2^p - 1)\n\n");
  printf("Número de threads: %d\n", NUM_THREADS);
  printf("Números perfeitos a encontrar: %d\n\n", PERFECT_NUMBERS_NEEDED);

  /* Inicializa o mutex */
  if (pthread_mutex_init(&mutex, NULL) != 0) {
    fprintf(stderr, "Erro ao inicializar mutex!\n");
    exit(EXIT_FAILURE);
  }

  /* Marca o tempo inicial */
  start_time = get_time_ms();

  /* Cria as threads */
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, thread_worker, (void*)(long)i) != 0) {
      fprintf(stderr, "Erro ao criar thread %d!\n", i);
      exit(EXIT_FAILURE);
    }
  }

  /* Aguarda o término de todas as threads */
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      fprintf(stderr, "Erro ao fazer join na thread %d!\n", i);
      exit(EXIT_FAILURE);
    }
  }

  /* Marca o tempo final */
  end_time = get_time_ms();
  elapsed_time = end_time - start_time;

  /* Destroy do mutex */
  pthread_mutex_destroy(&mutex);

  printf("\n=== Resumo da Execução ===\n");
  printf("Tempo total de execução: %ld milissegundos\n", elapsed_time);
  printf("Números perfeitos encontrados: %d\n", perfect_count);

  return EXIT_SUCCESS;
}
