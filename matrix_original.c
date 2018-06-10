#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row1, col1, row2, col2;
int row1_half, col1_half, row2_half, col2_half;
int **matrix1, **matrix2, **matrix3;

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

	/**--------------- Calculate ---------------**/
	start=clock();
	//matrix multiply
	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			for(int k=0; k<col1; k++)	
				matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	}

	end=clock();
	time=(end-start) / CLOCKS_PER_SEC * 1000;
	printf("\nOriginal Multiplication: %.10lf \t sec\n", time);

	/**--------------- result ---------------**/
	//Print out the resulting matrix
/*	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			printf("%d ",matrix3[i][j]);
		}
		printf("\n");
	}
*/
	//write result to file
	fp_out = fopen("original_output2.txt","w+");
	if(!fp_out){
		printf("Open Failed\n");
		exit(0);
	}
	
	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			fprintf(fp_out,"%d ",matrix3[i][j]);
		}
		fprintf(fp_out,"\n");
	}
	fclose(fp_out);

}
