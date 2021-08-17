/*EXECV Abuelo-Padre*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    printf ("Hola desde proceso Abuelo \n");
    int proPadre;
    int com = (proPadre = execv("procesoPadre", argv));
    if ( com == -1)
        perror("Error = -1(Abuelo-Padre)");
    return 0;
}