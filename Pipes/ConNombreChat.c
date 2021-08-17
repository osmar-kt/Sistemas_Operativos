/* Con Nombre*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
    
	FILE *mipipe;
    char buffer[128],buffer2[128];
    int i=0;
	char *fin = "fin";

	if( mkfifo("pipetest", S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH) != 0 )
		perror("Error ");
		
	while( 1 ) {
		memset( buffer , 0 , 128 );
  		memset( buffer2 , 0 , 128 );
		mipipe=fopen("pipetest","w");
  		printf("Ingresa un mensaje: ");
  		scanf(" %[^\n]s", buffer);
  		fputs(buffer, mipipe);
		fclose(mipipe);
  		if( strncmp( buffer , fin , 3 ) == 0 )
    		break;
		mipipe=fopen("pipetest","r");
  		if (fgets(buffer2, 128, mipipe))
    		printf ("Recibido: %s\n\n", buffer2);
		fclose(mipipe);
  		if( strncmp( buffer2 , fin , 3 ) == 0 )
    		break;
	}
	printf("\tFin del Chat\n");
	
	return 0;
}
