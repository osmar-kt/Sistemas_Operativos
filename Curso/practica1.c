#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int hijosIzq(int, int);
int hijosDer(int, int);
int hijosDer(int niv, int p)
{
    if(p >= niv)
        return 0;
    p+=1;
    int nodoHijo=fork(), nodoHijo2, nodoHijo3, ban;
    pid_t detiene;
    switch(nodoHijo)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            return hijosDer(niv, p);
            printf("NODO DER ID :%d, MI PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(detiene,&ban,0);
        break;
    }
    nodoHijo2=fork();
    switch(nodoHijo2)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            return hijosDer(niv, p);
            printf("NODO DER ID :%d, MI PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(detiene,&ban,0);
        break;
    }
    nodoHijo3=fork();
    switch(nodoHijo3)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            return hijosDer(niv, p);
            printf("NODO DER ID :%d, MI PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(detiene,&ban,0);
        break;
    }
}
int hijosIzq(int nivel, int pos)
{
    if(pos >= nivel)
        return 0;
    pos+=1;
    int subNodo=fork(), subNodo2, bander;
    pid_t espHijo;
    switch(subNodo)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            return hijosIzq(nivel, pos);
            printf("NODO IZQ ID :%d, PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(espHijo,&bander,0);
        break;
    }
    subNodo2=fork();
    switch(subNodo2)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            return hijosIzq(nivel, pos);
            printf("NODO IZQ ID :%d, PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(espHijo,&bander,0);
        break;
    }
}
int main ()
{
    int niveles;
    puts("CUANTOS NIVELES DESEAS");
    scanf("%d",&niveles);
    int hijoIzq=fork(), hijoDer, bandera;
    pid_t espera;
    switch(hijoIzq)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            hijosIzq(niveles, 1);
            printf("NODO IZQ ID :%d, PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(espera,&bandera,0);
        break;
    }
    hijoDer=fork();
    switch(hijoDer)
    {
        case -1:
            perror("YA NO ES POSIBLE CREAR EL PROCESO");
        break;
        case 0:
            hijosDer(niveles, 1);
            printf("NODO DER ID :%d, MI PAPA ID :%d \n", getpid(), getppid());
            exit(1);
        break;
        default:
            waitpid(espera,&bandera,0);
        break;
    }   
    return 0;
}