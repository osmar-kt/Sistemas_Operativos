/*EXECV Padre-Nieto*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    printf ("Hola desde proceso padre \n");
    int proNieto;
    int com = proNieto = execv("procesoNieto", argv);
    if ( com == -1)
        perror("Error = -1");
    return 0;
}