#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ	0
#define WRITE	1

int main ( void ){
  	int papa[2],hijo[2];
  	int  bytesDad,bytesSon,pid;
  	char message[100],send[100];
  	printf ("Ejemplo comunicación entre proceso padre e hijo.\n");
	pipe( papa );
  	pipe( hijo );
	pid = fork();
	if( pid == -1 )
		printf("Error al crear el proceso hijo... \n");
	else if (pid == 0){
    		close( papa[WRITE] );
    		close( hijo[READ] ); 
			bytesDad = read ( papa[READ], message , 100);
    		printf("El hijo recibio: %s , %d bytes\n", message, bytesDad);
    		printf("Escribe el mensaje hacia el padre:\n");
    		scanf("%[^\n]s", send);
    		write( hijo[WRITE], send, strlen(send));
			close( hijo[WRITE] );
   		close( papa[READ] );
  	}
  	else{
    		close( papa[READ] ); 
    		close( hijo[WRITE] );
			printf("Escribe el mensaje hacia el hijo:\n");
    		scanf("%[^\n]s", send);;
    		write( papa[WRITE],send , strlen(send));
 			bytesSon = read(hijo[READ], message, 100);
    		printf("El padre recibio: %s, %d bytes\n",message , bytesSon);
			close( papa[WRITE] );
    		close( hijo[READ] );
  	}
	return 0;
}
