#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define NUM_THREADS 10 

int row1, col1, row2, col2;
int **matrix1, **matrix2, **matrix3;


void *runner(void *param);    /*the thread*/

int main()
{
	float start, end, time;
	FILE *fp,*fp_out;

	fp = fopen("test2","r");
	if(!fp){
		printf("Open Failed\n");
		exit(0);
	}
	
	
	/**--------------- matrix 1 ---------------**/
	//get size of matrix1
	fscanf(fp,"%d", &row1);
	fscanf(fp,"%d", &col1);	

	//malloc matrix1
	matrix1 = malloc(row1 * sizeof(int *));
	for(int i=0; i<row1; i++){
		matrix1[i] = malloc(col1 * sizeof(int *));
	}

	//initialize matrix
	for(int i=0; i<row1; i++)
		for(int j=0; j<col1; j++)
			fscanf(fp,"%d",&matrix1[i][j]);
			
	//print matrix1
/*	printf("matrix1\n");
	for(int i=0;i<row1;i++){
		for(int j=0;j<col1;j++)
			printf("%d ",matrix1[i][j]);
		printf("\n");
	}
	printf("\n");
*/
	/**--------------- matrix 2 ---------------**/
	//get size of matrix2
	fscanf(fp,"%d", &row2);
	fscanf(fp,"%d", &col2);	

	//malloc matrix2
	matrix2 = malloc(row2 * sizeof(int *));
	for(int i=0; i<row2; i++){
		matrix2[i] = malloc(col2 * sizeof(int *));
	}

	//initialize matrix2
	for(int i=0; i<row2; i++)
		for(int j=0; j<col2; j++)
			fscanf(fp,"%d",&matrix2[i][j]);

	//print matrix2
/*	printf("matrix2\n");
	for(int i=0; i<row2; i++){
		for(int j=0; j<col2; j++)
			printf("%d ",matrix2[i][j]);
		printf("\n");
	}
	printf("\n");
*/	
	/**--------------- matrix 3 ---------------**/
	//malloc matrix3
	matrix3 = malloc(row1 * sizeof(int *));
	for(int i=0; i<row1; i++){
		matrix3[i] = malloc(col2 * sizeof(int *));
	}
	
	//initialize matrix3
	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			matrix3[i][j] = 0;
		}
	}
	
	/**--------------- pthread ---------------**/
	int i;
	double sum =0;
	struct timeval tstart, tend;
	double exectime;
	pthread_t * threads;
	
	if(row1 % NUM_THREADS != 0){
		fprintf( stderr, "size %d must be a multiple of num of threads %d\n", row1, NUM_THREADS );
    	return -1;
	}
	
	threads = (pthread_t *) malloc( NUM_THREADS * sizeof(pthread_t) );
	
//	gettimeofday( &tstart, NULL );
	start = clock();
  	for ( i = 0; i < NUM_THREADS; ++i ) {
    	int *tid;
    	tid = (int *) malloc( sizeof(int) );
    	*tid = i;
    	pthread_create( &threads[i], NULL, runner, (void *)tid );
  	}
	
	for ( i = 0; i < NUM_THREADS; ++i ) {
    	pthread_join( threads[i], NULL );
  	}
//  	gettimeofday( &tend, NULL );
	end = clock();	
	
//	exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
//  	exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

//  	printf( "Number of MPI ranks: 0\tNumber of threads: %d\tExecution time:%.3lf sec\n", NUM_THREADS, exectime/1000.0);
	time = (end-start) / CLOCKS_PER_SEC * 1000;
	printf("Execution time : %.10lf \t sec\n", time);
	
	
	/**--------------- result ---------------**/
	//Print out the resulting matrix
/*	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			printf("%d ",matrix3[i][j]);
		}
		printf("\n");
	}
*/	
	//Write result to file
	fp_out = fopen("test2_result_pthread.txt","w+");
	if(!fp_out){
		printf("Open Failed\n");
		exit(0);
	}
	
	for(int i=0; i<row1;i++){
		for(int j=0; j<col2; j++){
			fprintf(fp_out,"%d ",matrix3[i][j]);
		}
		fprintf(fp_out,"\n");
	}
	fclose(fp_out);

}


void *runner(void *arg)
{
  	int i, j, k, tid, portion_size, row_start, row_end;
  	double sum;
  
  	tid = *(int *)(arg); // get the thread ID assigned sequentially.
  	portion_size = row1 / NUM_THREADS;
  	row_start = tid * portion_size;
  	row_end = (tid+1) * portion_size;

  	for (i = row_start; i < row_end; ++i) { // hold row index of 'matrix1'
    		for (j = 0; j < row1; ++j) { // hold column index of 'matrix2'
      			sum = 0; // hold value of a cell
      	/* one pass to sum the multiplications of corresponding cells in the row vector and column vector. */
      			for (k = 0; k < row1; ++k) { 
				sum += matrix1[ i ][ k ] * matrix2[ k ][ j ];
      			}
      			matrix3[ i ][ j ] = sum;
    		}
  	}
}

