#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* Cria uma thread extra, mostra compartilhamento de variáveis e captura valor 
 * de retorno da thread extra.
 */

void *thread_function(void *arg);
char message[] = "Hello World"; /* Variável global */

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread...\n");
    res = pthread_join(a_thread, &thread_result); /* Recebeu o retorno de 
                                                     thread_function */
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joind, it returned: %s\n", (char *)thread_result);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) { /* Vai receber um argumento -> message
                                      ver linha 19 */
    printf("thread_function is running. Argument was: %s\n", (char *)arg);
    sleep(3);
    strcpy(message, "Bye!"); /* Copia a string para message */
    pthread_exit("Thank you for the CPU time");
}
