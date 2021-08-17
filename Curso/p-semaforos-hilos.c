#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
char valA[4], valB[4];
int endRead;
sem_t secA1[4], secA2[4], secB1[4], secB2[4], semEndRead;
void* hiloProductores (void *produce)
{
    char idPro = *(char *)produce;
    int x=0, x2, valorSem, cantWrite = 0;
    for(x2=0; x2<100; x2++)
    {
        do
        {
            x=0;
            while(x<4 && (valorSem = sem_trywait(&secA2[x])) != 0)
                x++;
            if(x<4 && valorSem == 0)
            {
                valA[x]=idPro;
                printf("SE PRODUJO :%c EN LA FILA %d DE LA PRIMERA SECCION CRITICA \n", valA[x], x);
                cantWrite++;
                sem_post(&secA1[x]);
                x=100;
            }
            else
                x=0;
            while(x<4 && (valorSem = sem_trywait(&secB2[x])) != 0)
                x++;
            if(x<4 && valorSem == 0)
            {
                valB[x]=idPro;
                printf("SE PRODUJO :%c EN LA FILA %d DE LA SEGUNDA SECCION CRITICA \n", valB[x], x);
                cantWrite++;
                sem_post(&secB1[x]);
                x = 100;
            }
        }while(x != 100);
    }
    while(sem_trywait(&semEndRead) != 0)
        x=x;
    endRead+=x2+1;
    sem_post(&semEndRead);
    printf("\n \n SE ESCRIBIERON %d DATOS DEL PRODUCTOR %c \n \n", cantWrite, idPro);
    pthread_exit(NULL);
}
void* hiloConsumidores(void *consume)
{
    int idCo = *(int *)consume, y, valorSem2, cantRead = 0, leer;
    do
    {
        do
        {
            y=0;
            while(y < 4 && (valorSem2 = sem_trywait(&secA1[y])) != 0 && leer<500)
                y++;
            if(y < 4 && valorSem2 == 0)
            {
                printf("SE CONSUMIO :%c DE LA FILA %d DE LA PRIMERA SECCION CRITICA \n", valA[y], y);
                sem_post(&secA2[y]);
                cantRead++;
                y = 100;
            }
            else
                y=0;
            while(y < 4 && (valorSem2 = sem_trywait(&secB1[y])) != 0 && leer<500)
                y++;
            if(y < 4 && valorSem2 == 0)
            {
                printf("SE CONSUMIO :%c DE LA FILA %d DE LA SEGUNDA SECCION CRITICA \n", valB[y], y);
                sem_post(&secB2[y]);
                cantRead++;
                y=100;  
            }
        }while(y != 100);
        while(sem_trywait(&semEndRead) != 0)
            y=y;
        leer = endRead;
        sem_post(&semEndRead);
    }while(leer<500);
    printf("\n \n SE LOGRO LEER %d DATOS DEL CONSUMIDOR %d \n \n", cantRead, idCo);
    pthread_exit(NULL);
}
int main ()
{
    int i, f, k, vC[3];
    char vP[5];
    pthread_t consumidor[3], productor[5];
    endRead = 0;
    sem_init(&semEndRead, 5, 1);
    for(i=0; i<4; i++)
    {
        sem_init(&secA1[i], 5, 0);
        sem_init(&secA2[i], 5, 1);
        sem_init(&secB1[i], 5, 0);
        sem_init(&secB2[i], 5, 1);
    }
    for(f=0; f<5; f++)
    {
        vP[f] = 'A'+f;
        pthread_create(&productor[f], NULL, hiloProductores, &vP[f]);
    }
    for(k=0; k<3; k++)
    {
        vC[k] = k;
        pthread_create(&consumidor[k], NULL, hiloConsumidores, &vC[k]);
    }
    for(k=0; k<3; k++)
        pthread_join(consumidor[k], NULL);
    for(f=0; f<5; f++)
        pthread_join(productor[f], NULL);
    for(i=0; i<4; i++)
    {
        sem_destroy(&secA1[i]);
        sem_destroy(&secA2[i]);
        sem_destroy(&secB1[i]);
        sem_destroy(&secB2[i]);
    }
    sem_destroy(&semEndRead);    
    return 0;
}