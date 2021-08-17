/*
Problema del productor-consumidor entre procesos
Implementando semáforos (POSIX) con nombre
Compilar: gcc semaforo1.c -lpthread -lrt */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define TAM_MEM 1
int *Memoria;

int CrearLigamemoria( void );
int DestruyeMemoriaCompartida( int id_Memoria , int *buffer );
sem_t * CrearSemaforo(  char *name , int val );

int main(){
    int pid,id,j;
    char *name1 = "consumidor";
    char *name2 = "productor";
    sem_t *semaforoConsumidor , *semaforoProductor;

    semaforoConsumidor = CrearSemaforo( name1 , 0 );
    semaforoProductor = CrearSemaforo( name2 , 1 );

    pid = fork();
    if( pid == -1 )
        printf("Error al crear el hijo\n");
    else if( pid == 0 ){
        id = CrearLigamemoria();
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( semaforoProductor );
            *Memoria = j;
            printf("Produjo: %d\n",j);
            sem_post( semaforoConsumidor );
        }
        sem_unlink( name1 );
        sem_unlink( name2 );
        exit(0);
    }
    else{
        id = CrearLigamemoria();
        for( j = 0 ; j < 10 ; j++ ){
            sem_wait( semaforoConsumidor );
            printf("consumio: %d\n",*Memoria);
            sem_post( semaforoProductor );
        }
        sem_unlink( name1 );
        sem_unlink( name2 );
        DestruyeMemoriaCompartida( id , Memoria );
    }
    wait(NULL);
    sem_close( semaforoProductor );
    sem_destroy( semaforoProductor );
    sem_close( semaforoConsumidor );
    sem_destroy( semaforoConsumidor );
    return 0;
}

int CrearLigamemoria( void ){
    int key2,shmid;
    key2 = ftok("/bin/ls",3);

    //Verifica si existe la zona de memoria
    if( ( shmid = shmget( key2 , sizeof( int ) * TAM_MEM , IPC_CREAT|IPC_EXCL|0666) ) == -1 ){
        // Si existe obtiene la memoria 
        if( ( shmid = shmget( key2 , sizeof( int ) * TAM_MEM , 0 ) ) == -1 ){
            perror("shmget \n");
            exit(1);
        }
        else
            printf("Se ligo a la memoria con id: %d\n",shmid);
    }
    else
        printf("Creo la memoria con id: %d\n",shmid);
    //Se liga a la zona de memoria compartida
    if( ( Memoria = (int*)shmat( shmid , (int*) 0 , 0 ) ) == (void*)-1 ){
        perror("shmat \n");
        exit(1);
    }

    return shmid; //Descriptor de la memoria
}

int DestruyeMemoriaCompartida( int id_Memoria , int *buffer ){
    if( id_Memoria != 0 || id_Memoria != -1 ){ //Valida si ya se destruyo
        shmdt( buffer );                       //Quita la liga hacia la memoria
        shmctl( id_Memoria , IPC_RMID , (struct shmid_ds *) NULL ); //Destruye la zona de memoria
        printf("Se destruyo la memoria\n");
    } 
    else{
        shmdt( buffer );
        printf("Se desligo la memoria\n");
    }
    
}

sem_t * CrearSemaforo( char *name , int val){
    sem_t *mut;
    if( ( mut = sem_open( name , O_CREAT | O_EXCL , 0666 , val ) ) == SEM_FAILED ){
        if( ( mut = sem_open( name , 0 ) ) == SEM_FAILED )
            printf("Error al abrir el semaforo\n");
        else
            printf("Ligado al semaforo correctamente %p\n", mut);
    }
    else{
        printf("Semaforo: %s creado: %p\n", name, mut);
        sem_init( mut , 1 , val );
    }

    return mut;
}