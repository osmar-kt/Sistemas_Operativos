#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void fillMatrix(int *matrix[],int nrows,int ncolumns);
void printMatrix(int *matrix[],int nrows,int ncolumns);
void allocateMemory(int *matrix[],int ncolumns ,int nrows);
void product(int *matrixA[],int *matrixB[],int ncolumns,int start,int end);

int main( int argc , char *argv[] ){
	if( argc < 4 || atoi(argv[1]) < atoi(argv[3]) ){
		printf("Uso: %s NumFilas NumColumnas NumProcesos \n",argv[0]);
		printf("Aviso:\nEl numero de filas debe ser mayor al numero de procesos \n");
		exit(0);
	}
	srand(time(NULL));
	int rows, columns, process, range, extra, pid, i, j, start, end;
	rows = atoi( argv[1] );
	columns = atoi( argv[2] );
	process  = atoi( argv[3] );
	range  = rows / process ;
	extra = rows % process ;
	end = range;
	start = 0;
	int *matrixA[rows] , *matrixB[columns];
	allocateMemory( matrixA , rows , columns );
	allocateMemory( matrixB , columns , rows );
	fillMatrix( matrixA , rows , columns );
	fillMatrix( matrixB , columns , rows );
	printf("Matriz A:\n");
	printMatrix( matrixA , rows , columns );
	printf("Matriz B:\n");	
	printMatrix( matrixB , columns , rows );
	printf("\nResultado:\n");
	for( i=0 ; i < process ; i++ ){
		pid = fork();
		if( pid == -1 )
			printf("Error al crear el proceso %d",i);
		else if( pid == 0 ){
			if( i == (process -1) )
				product(matrixA , matrixB , rows , start , end+extra);
			else
				product(matrixA , matrixB , rows , start , end);
			exit(0);
		}
		start += range;
		end += range;
	}
	wait(NULL);
	return 0;
}

void fillMatrix( int *matrix[] , int nrows , int ncolumns ){
	int i,j,num;
	for( i=0 ; i < nrows ; i++  )
		for( j=0 ; j < ncolumns ; j++ ){
			num = rand()%10;
			matrix[i][j]=num;
		}
}

void printMatrix( int *matrix[] , int nrows , int ncolumns ){
	int i,j,num;
	for( i=0 ; i < nrows ; i++ ){
		for( j=0 ; j < ncolumns ; j++ )
			printf("%*d ",4,matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void allocateMemory( int *matrix[] , int nrows , int ncolumns ){
	int i;
	for( i = 0 ; i < nrows ; i++)
		matrix[i] = (int *) malloc( sizeof(int) * ncolumns );
}

void product( int *matrixA[], int *matrixB[] , int ncolumns , int start , int end ){
	int i, j, k, p, n, val, row[ncolumns];
	for( i = start ; i < end ; i++ ){
		for( n = 0 , p = 0 ; n < ncolumns ; n++ , p++){
			val = 0;
			for( j = 0 ; j < ncolumns ; j++ )
				val += matrixA[i][j] * matrixB[j][n]; 
			row[p] = val;
		}
		printf("Fila %*d: ", 3,i);
		for( k = 0 ; k < ncolumns ; k++)
			printf("%*d " , 5,row[k]);
		printf("\n");	
	}
}