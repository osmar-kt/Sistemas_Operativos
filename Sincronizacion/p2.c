/* gcc p2.c -lpthread -lrt */

#include <pthread.h>
#include <stdio.h>


void* hProductor(void *idProductor);
void* hConsumidor(void *idConsumidor);

pthread_mutex_t sA1, sA2, sB1, sB2;

int vA, vB;

int main ()
{
    int i, ids[2];

    pthread_t productor, consumidor;
    
    sA1 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    sB1 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    sA2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    sB2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    
    for(i=0; i<2; i++)
    {
        ids[i]=i;
        
        pthread_create(&productor, NULL, hProductor, &ids[i]);
        pthread_create(&consumidor, NULL, hConsumidor, &ids[i]);
    }
    
    for(i=0; i<2; i++)
    {
        pthread_join(productor, NULL);
        pthread_join(consumidor, NULL);
    }
    
    pthread_mutex_destroy(&sA1);
    pthread_mutex_destroy(&sB1);
    pthread_mutex_destroy(&sA2);
    pthread_mutex_destroy(&sB2);
    
    return 0;
}

void* hProductor(void *idProductor)
{
    int productor = *(int *)idProductor, j;
    
    for(j=0; j<20; j++)
    {
        pthread_mutex_lock(&sA2);
        
        vA = j;
        
        printf("Productor: (%d) \n", productor);
        printf("Produce: (%d) \n\n", vA);
        
        pthread_mutex_unlock(&sA1);
        pthread_mutex_lock(&sB2);
        
        vB = j+100;
        
        printf("Productor: (%d) \n", productor);
        printf("Produce: (%d) \n\n", vB);
        
        pthread_mutex_unlock(&sB1);
    }
    
    pthread_exit(NULL);
}
void* hConsumidor(void *idConsumidor)
{
    int consumidor = *(int *)idConsumidor, k;
    
    for(k=0; k<20; k++)
    {
        pthread_mutex_lock(&sA1);
        
        printf("Consumidor: (%d) \n", consumidor);
        printf("Consume: (%d) \n\n", vA);
        
        pthread_mutex_unlock(&sA2);
        pthread_mutex_lock(&sB1);
        
        printf("Consumidor: (%d) \n", consumidor);
        printf("Consume: (%d) \n\n", vB);
        
        pthread_mutex_unlock(&sB2);
    }
    
    pthread_exit(NULL);
}
