/*Chat Sin Nombre*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ	0
#define WRITE	1

int main ( void ){
  	
	int dsDad[2],dsSon[2];
  	int  bytes,pid;
  	char message[100],send[100],*end="fin" ;
	pipe( dsDad );
  	pipe( dsSon );
	pid = fork();
	
	if( pid == -1 )
		printf("\tError\n");
	else if (pid == 0){
    	close( dsDad[WRITE] );
    	close( dsSon[READ] );
		
		while( 1 ){
			
			memset( message , 0 , 100 );
			memset( send , 0 , 100);
			bytes = read ( dsDad[READ], message , 100);
			
			if( strncmp( end , message, 3 ) == 0 )
				break;
 			printf("Mensaje recibio por: %s \n", message);
   
    		printf("Msj para el padre: ");
    		scanf(" %[^\n]s", send);
    		write( dsSon[WRITE], send, strlen(send));
			
			if( strncmp( end , send, 3 ) == 0 )
				break;
		}
		
		printf("\tFin del Chat\n");
    	
		close( dsSon[WRITE] );
   		close( dsDad[READ] );
  	}
  	else{
    	
		close( dsDad[READ] );  
    	close( dsSon[WRITE] ); 
		
		while( 1 ){
			
			memset( message , 0 , 100 );
			memset( send , 0 , 100);
    		
			printf("Msj para el hijo: ");
    		scanf(" %[^\n]s", send);
    		write( dsDad[WRITE],send , strlen(send));
			
			if( strncmp( end , send , 3 ) == 0 )
				break;

    		bytes = read(dsSon[READ], message, 100);
			
			if( strncmp( end , message , 3 ) == 0 )
				break;
    			printf("Mensaje recibio por el padre: %s \n",message);
		}
		
		printf("\tFin del Chat\n");
    	
		close( dsDad[WRITE] );
    	close( dsSon[READ] );
  	}	
	return 0;
}
