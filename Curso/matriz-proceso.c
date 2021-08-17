#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int pideDat(int*, int*, int*, int*, int*);
int divideTareas(int, int, int, int, int**, int**, int**);
int** creaMat(int, int);
int llenaMat(int **, int, int);
int imprimeMat(int, int, int**);
int main()
{
    int r, c, r2, c2, cantProcesos, **a, **b, **res;
    pideDat(&r, &c, &r2, &c2, &cantProcesos);
    a=creaMat(r, c);
    if(a == NULL)
        exit(1);
    b=creaMat(r2, c2);
    if(b == NULL)
        exit(1);
    res=creaMat(r, c2);
    if(res == NULL)
        exit(1);
    llenaMat(a, r, c);
    llenaMat(b, r2, c2);
    divideTareas(r, c, c2, cantProcesos, a, b, res);
    printf("\n");
    imprimeMat(r, c2, res);
    printf("\n");
    free(a);
    free(b);
    free(res);
    return 0;
}
int pideDat(int *re, int *co, int *re2, int *co2, int *cant)
{
    do
    {
        puts("SI INGRESAS DIMENSIONES NO VALIDAS PARA MULTIPLICAION DE MATRICES SE VOLVERAN A PEDIR \n El NUMERO DE PROCESOS DEBE DE SER IGUAL O MENOR A EL NUMERO DE RENGLONES DE LA MATRIZ A");
        puts("Numero de renglones matriz A");
        scanf("%d",re);
        puts("Numero de columnas matriz A");
        scanf("%d",co);
        puts("Numero de renglones matriz B");
        scanf("%d",re2);
        puts("Numero de columnas matriz B");
        scanf("%d",co2);
        puts("Numero de procesos que deseas");
        scanf("%d",cant);
    }while(!(*co == *re2) && *cant<=*re);
    return 0;
}
int divideTareas(int ren, int col, int col2, int proces, int **matA, int **matB, int **matC)
{
    if(matA == NULL)
        exit(1);
    if(matB == NULL)
        exit(1);
    if(matC == NULL)
        exit(1);
    int cantProcesXFila = ren/proces;
    int residuoProcesXFila = ren%proces;
    int ini=0, fin, i=0, espPro, f, k;
    pid_t espera;
    int indice[proces*2];
    while (ini<ren)
        if(residuoProcesXFila > 0)
        {
            fin = ini+cantProcesXFila;
            indice[i]=ini;
            indice[i+1]=fin;
            ini += cantProcesXFila+1;
            residuoProcesXFila--;
            i+=2;
        }
        else
        {
            fin = ini+(cantProcesXFila-1);
            indice[i]=ini;
            indice[i+1]=fin;
            ini += cantProcesXFila;
            i+=2;
        }
    for(i=0; i<(proces*2); i+=2)
        switch(fork())
        {
            case -1:
                perror("NO SE LOGRO CREAR EL PROCESO");
                exit(1);
            break;
            case 0:
                fin = indice[i+1];
                for(ini = indice[i]; ini<=fin; ini++)
                    for(f=0; f<col2; f++)
                    {
                        matC[ini][f]=0;
                        for(k=0; k<col; k++)
                            matC[ini][f]+= matA[ini][k] * matB[k][f];
                    }
            break;
            default:
                waitpid(espera, &espPro, 0);
            break;
        }
    return 0;
}
int** creaMat(int ren, int col)
{
    int cent, cent2;
    int **temp = (int **) malloc(sizeof(int*)*ren);
    for(cent=0; cent<ren; cent++)
        temp[cent] = (int *)malloc(sizeof(int)*col);
    return temp;
}
int llenaMat(int **mat, int renglon, int columna)
{
    if(mat == NULL)
        exit(1);
    int p, q;
    for(p=0; p<renglon; p++)
        for(q=0; q<columna; q++)
            {
                printf("que valor quieres para la posicion [%d][%d] \n",p, q);
                scanf("%d",&mat[p][q]);
            }
    return 0;
}
int imprimeMat(int renglon, int columna, int **matriz)
{
    if(matriz == NULL)
        exit(1);
    int x,z;
    system("clear");
    for(x=0; x<renglon; x++)
    {
        printf("\n");
        for(z=0; z<columna; z++)
            printf(" %d|", matriz[x][z]);
    }
    return 0;
}