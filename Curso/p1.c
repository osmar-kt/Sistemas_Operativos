/* gcc p1.c -lpthread -lrt */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void* hProductor(void *idProductor);
void* hConsumidor(void *idConsumidor);

sem_t sA1, sA2, sB1, sB2;
int vA, vB;

int main()
{
    int i, ide[2];
    pthread_t productor, consumidor;
    
    sem_init(&sA1, 5, 0);
    sem_init(&sA2, 5, 1);
    sem_init(&sB1, 5, 0);
    sem_init(&sB2, 5, 1);
    
    for(i=0; i<2; i++)
    {
        ide[i]=i;
        
        pthread_create(&productor, NULL, hProductor, &ide[i]);
        pthread_create(&consumidor, NULL, hConsumidor, &ide[i]);
    }
    
    for(i=0; i<2; i++)
    {
        pthread_join(productor, NULL);
        pthread_join(consumidor, NULL);
    }
    
    sem_destroy(&sA1);
    sem_destroy(&sA2);
    sem_destroy(&sB1);
    sem_destroy(&sB2);
    
    return 0;
}
void* hProductor(void *idProductor)
{
    int productor = *(int *)idProductor, j;
    
    for(j=0; j<20; j++)
    {
        sem_wait(&sA2);
        
        vA = j;
        
        printf("productor: (%d) \n", productor);
        printf("produce: (%d) \n\n", vA);
        
        sem_post(&sA1);
        sem_wait(&sB2);
        
        vB = j+100;
        
        printf("productor: (%d) \n", productor);
        printf("produce: (%d) \n\n", vB);
        
        sem_post(&sB1);
    }
    
    pthread_exit(NULL);
}
void* hConsumidor(void *idConsumidor)
{
    int consumidor = *(int *)idConsumidor, k;
    
    for(k=0; k<20; k++)
    {
        sem_wait(&sA1);
        
        printf("consumidor: (%d) \n", consumidor);
        printf("consume: (%d) \n\n", vA);
        
        sem_post(&sA2);
        sem_wait(&sB1);
        
        printf("consumidor: (%d) \n", consumidor);
        printf("consume: (%d) \n\n", vB);
        
        sem_post(&sB2);
    }
    
    pthread_exit(NULL);
}
