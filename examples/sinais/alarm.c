#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig) {
	alarm_fired = 1;
}

int main() {
	int pid;
	printf("\nAlarm application starting...\n");
	if((pid = fork()) == 0) {
		printf("PID = %d\n", pid);
		sleep(5);
		kill(getppid(), SIGALRM); /* getppid() retorna o ID do processo pai */
		exit(0);
	}

	printf("PID = %d", pid);
	printf("\nwaiting for alarm to go off\n");
	(void) signal(SIGALRM, ding);

	pause(); /* Suspende a execução até que um sinal ocorra (se o sinal 
                já tiver ocorrido, o processo vai esperar para sempre */
	if(alarm_fired)
		printf("\nDing!\n");

	printf("Done\n");
	exit(0);
}
