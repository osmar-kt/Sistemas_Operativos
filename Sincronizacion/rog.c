#include<stdio.h>
#include<pthread.h>


pthread_mutex_t producido;
pthread_mutex_t restante;


int sectCrit;


void productor(void *param){​​​​​​​
    puts("HILO PRODUCTOR");
    int i;
    for (i = 0; i < 20; ++i){​​​​​​​
        pthread_mutex_lock(&restante);
        sectCrit = i;
        printf("PRODUCTOR %d \n", sectCrit);
        pthread_mutex_unlock(&producido); 
    }​​​​​​​
}​​​​​​​


void consumidor(void *param){​​​​​​​
    puts("HILO CONSUMIDOR");
    int i;
    for(i = 0; i < 20; i++){​​​​​​​
        pthread_mutex_lock(&producido);
        printf("CONSUMIDOR %d \n", sectCrit);
        pthread_mutex_unlock(&restante); 
    }​​​​​​​
}​​​​​​​


int main(int argc, char const *argv[]){​​​​​​​
    
    producido = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    restante = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;


    pthread_t prod, consum;
    pthread_create(&prod, NULL, (void *) &productor, NULL);
    pthread_create(&consum, NULL, (void *) &consumidor, NULL);


    pthread_mutex_lock(&producido);
    
    pthread_join(prod, NULL);
    pthread_join(consum, NULL);
    pthread_mutex_destroy(&producido);
    pthread_mutex_destroy(&restante);
    return 0; 
}​​​​​​​