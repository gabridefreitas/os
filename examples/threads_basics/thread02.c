#include <pthread.h>
#include <stdio.h>

char buffer;
int flag = 0;

void *produtor() { /* Código do produtor */
	char item;
	while(1) {
		item = 'A';
		printf("Produzi A\n");
		buffer = item;
		flag = 1;
	}
    pthread_exit(0); /* Status de saída */
}

void *consumidor() { /* Código do consumidor */
	char item;
	while(1) {
		if (flag == 1) {
			item = buffer;
			printf(">>>>>>>>> Consumi o item %c\n", item);
			flag = 0;
		}
	}
    pthread_exit(0); /* Status de saida */
}

int main() {
    pthread_t t1, t2; /* Declara as threads */

   /* Cria threads: id, atributo assocido na inicialização, função, parâmetro */
   (void) pthread_create(&t1, NULL, produtor, NULL);
   (void) pthread_create(&t2, NULL, consumidor, NULL);
   
   /* Espera fim das threads: id, status de saída */
   (void) pthread_join(t1, NULL);
   (void) pthread_join(t2, NULL);

    return 0;
}
