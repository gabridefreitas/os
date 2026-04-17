#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int var_global = 1;  /* Variável no segmento de dados inicializados */

int main(){
	int valor = 100;  /* Variável automática na pilha */
	pid_t pid;
	
    printf("Antes do fork...\n");
	if((pid = fork()) < 0) {
		perror("Erro no fork!\n");  /* Tratamento de erro */
	}
	else if(pid == 0) {  /* Processo filho atualiza variáveis */
		var_global++;
        valor++;
	}
	else  /* Pai dorme por 2 segundos */ 
        sleep(2);
	
	printf("PID = %d, var_global = %d, valor = %d\n", getpid(), var_global, valor);

	exit(0);
}
