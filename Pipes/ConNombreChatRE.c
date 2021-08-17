/* Mini chat entre procesos utilizando PIPES con nombre 
 *  Receptor - Emisor
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    FILE *mipipe;
    char buffer[128],buffer2[128];
    char *fin = "fin";

    printf ("\t*************  C H A T *************\n");

    while( 1 ) {
        memset( buffer , 0 , 128 );
  		memset( buffer2 , 0 , 128 );
        mipipe=fopen("pipetest", "r");
        if (fgets(buffer, 128, mipipe))
            printf ("Recibido: %s\n", buffer);
        fclose(mipipe);
        if( strncmp( buffer , fin , 3 ) == 0 )
            break;
        mipipe=fopen("pipetest", "w");
        printf("Ingresa un mensaje: ");
        scanf(" %[^\n]s", buffer2);
        fputs(buffer2, mipipe);
        fclose(mipipe);
        printf("\n");
        if( strncmp( buffer2 , fin , 3 ) == 0 )
            break;
    }
    printf("\tChat finalizado... \n");
    return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  FILE *mipipe; 
  char buffer[128];
  int i=0;

  if (mkfifo("pipetest", S_IWUSR |  /* El usuario puede escribir */
                 S_IRUSR |  /* El usuario puede leer */
                 S_IRGRP |  /* El grupo puede leer */
                     S_IROTH    /* Otros pueden leer */
         )!=0)
    printf ("Hubo un problema al crear la pipe\n");

  mipipe=fopen("pipetest", "w"); /* Lo abrimos como un fichero normal y corriente */

  /* Con esta línea leemos hasta que se cierre la tubería por el otro */

  while (i<10)
    {
      sprintf(buffer, "CADENA ENVIADA Número: %i\n", i+1);
      fputs(buffer, mipipe);
      i++;
    }

  fclose(mipipe); 
    }
