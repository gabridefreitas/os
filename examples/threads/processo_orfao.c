#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t pid;

	printf("Antes do fork\n");
	pid = fork();  /* Cria processo filho */
	printf("Depois do fork\n");

	switch(pid) {
	case -1:
		perror("Erro no fork\n"); 
		exit(-1);
		break;
	case 0:
		printf("Sou o processo filho. Meu PID é: %i \n", getpid());
		while(1) {  /* Filho: nunca termina */
			sleep(100);
		}
		printf("Sou o filho, não vou exibir este texto porque estou em loop!");
		break;
	default:
		printf("Sou o processo pai. Vou finalizar com erro 42\n");
		exit(42);  /* Pai: finaliza com status qualquer */
	}
	return 0; /* Nunca será executado */
}
