#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/* Função que será chamada */
void ouch(int sig) {
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL); /* SIG_DFL: Replace the current signal 
                                       handler with the default handler */
}

int main() {
	(void) signal(SIGINT, ouch); /* SIGINT gerado pelo terminal (Ctrl-C) */
	while(1) {
		printf("Hello World!\n");
		sleep(1);
	}
}
