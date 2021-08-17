/* FORK. Abuelo-Padre-Hijo*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pro1,pro2;
	int status1,status2;
	if((pro1 = fork()) == 0){
		printf("Primer Hijo: %d\n",getpid());
	}
	else if(pro1 == -1){
		perror("ERROR\n");
	}
	else{
		if((pro2 = fork()) == 0){
			printf("Segundo Hijo: %d\n",getpid());
		}
		else if(pro2 == -1){
			perror("ERROR\n");
		}
		else{
			waitpid(pro1,&status1,0);
			waitpid(pro2,&status2,0);
			printf("Proceso Padre: %d\n",getpid());
		}
	}
return 0;
}