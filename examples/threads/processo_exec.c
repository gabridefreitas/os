#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {   
	pid_t p = fork(); /* Cria um novo processo */
	int status = 0;

	if(p < 0) {  /* Indica ocorrência de erro */
		fprintf(stderr, "Criação do novo processo falhou!\n");
		exit(-1);  /* Terminação de erro */
	} else if(p == 0) {  /* Processo filho */
		printf("Iniciando a execução do processo filho...\n"); 
		printf("Sou o filho de PPID = %d, tenho PID = %d\n", getppid(), getpid());
		printf("PID do filho (no filho): %d\n", p);						
		execlp("/bin/ls", "ls", "-l", NULL);  /* Atribui um novo programa ao filho */
		printf("Filho com parada de execução forçada!\n"); 
		exit(-1);
	} else {  /* Processo pai */
		printf("Pai aguardando o filho terminar...\n"); 
		printf("Sou o pai - PID = %d\n", getpid());
		printf("PID do filho (no pai): %d\n", p);						
		wait(&status);
		printf("Pai terminou! PID: %d, PPID (PID do pai): %d.\nStatus de terminação do filho = %s\n", getpid(), getppid(), (WEXITSTATUS(status) == 0 ? "Sucesso" : "Falha"));
		printf("Filho completou a execução!\n");	
		exit(0);  /* Terminação de sucesso */
	}	
}
