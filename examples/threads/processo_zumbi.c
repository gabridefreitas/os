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
		printf("Sou o processo filho, e vou morrer...\n");
		exit(43); /* Filho: termina com status qualquer */
		break;
	default:
		printf("Sou o processo pai, e vou entrar em loop...\n");
		while(1) {  /* Pai: nunca termina */
			sleep(100);
		}
	}
	return 0; 						
}
