/* FORK. Abuelo-Padre-Hijo*/
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	pid_t pro1,pro2;
	int status1,status2;
		if((pro1 = fork()) == 0){
			if((pro2 = fork()) == 0){
				printf("Proceso Hijo: %d\n",getpid());
			}
			else if(pro2 == -1){
				perror("ERROR\n");
			}
			else{
				wait(&status2);
				printf("Proceso Padre: %d\n",getpid());
			}
		}
		else if(pro1 == -1){
			perror("ERROR\n");
		}
		else{wait(&status1);
			printf("Proceso Abuelo: %d\n",getpid());
		}
	return 0;
}