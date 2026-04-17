#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t pid;		
	int status;
	printf("Pai: Meu PID = %d\n", getpid());	

	switch(fork()) {
	case -1:
		perror("Erro no fork\n"); 
		exit(-1);
		break;
	case 0:
		printf("Filho: meu PID = %d, PPID = %d\n", getpid(), getppid()); /* Filho: PID próprio e PID do pai */
		exit(13);
		break;
	default:
		printf("Pai: meu PID = %d, PPID = %d\n", getpid(), getppid());
		pid = wait(&status);  /* Espera filho terminar.*/
		printf("Pai: filho (PID = %d) terminou, status = %d\n", pid, WEXITSTATUS(status));
	}
	printf("PID %d terminando... \n", getpid());
	return 0; 						
}
