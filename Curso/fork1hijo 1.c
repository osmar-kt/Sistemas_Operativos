/* FORK. Padre-Hijo*/
#include<stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int pid;
	pid = fork();
	if(pid){
		printf("Proceso padre: %d\n",getpid());
	}
		else if(pid == -1){
		perror("Error pid = -1");
		}
	else{
		printf("Proceso hijo: %d\n",getpid());
	}
	return 0;
}