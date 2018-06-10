#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int row1, col1, row2, col2;
int row1_half, col1_half, row2_half, col2_half;
int **matrix1, **matrix2, **matrix3;
//for Strasens's
int **A11, **A12, **A21, **A22;
int **B11, **B12, **B21, **B22;
int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
int **C11, **C12, **C21, **C22;

void strassen();	//do Strassen's matrix multiply

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


	/**--------Strasen's Matrix Multiply----------**/
	strassen();


}	

/**---------- STRASSEN'S MATRIX ----------**/
void strassen(){

	row1_half = row1 / 2;
	col1_half = col1 / 2;
	row2_half = row2 / 2;
	col2_half = col2 / 2;

	//malloc A
	A11 = malloc(row1_half * sizeof(int *));   //a
	A12 = malloc(row1_half * sizeof(int *));   //b
	A21 = malloc(row1_half * sizeof(int *));   //c
	A22 = malloc(row1_half * sizeof(int *));   //d
	for(int i=0; i<row1_half; i++){
		A11[i] = malloc(col1_half * sizeof(int *));
		A12[i] = malloc(col1_half * sizeof(int *));
		A21[i] = malloc(col1_half * sizeof(int *));
		A22[i] = malloc(col1_half * sizeof(int *));
	}

	//malloc B
	B11 = malloc(row2_half * sizeof(int *));   //e
	B12 = malloc(row2_half * sizeof(int *));   //f
	B21 = malloc(row2_half * sizeof(int *));   //g
	B22 = malloc(row2_half * sizeof(int *));   //h
	for(int i=0; i<row2_half; i++){
		B11[i] = malloc(col2_half * sizeof(int *));
		B12[i] = malloc(col2_half * sizeof(int *));
		B21[i] = malloc(col2_half * sizeof(int *));
		B22[i] = malloc(col2_half * sizeof(int *));
	}
	
	//malloc C
	C11 = malloc(row1_half * sizeof(int *));
	C12 = malloc(row1_half * sizeof(int *));
	C21 = malloc(row1_half * sizeof(int *));
	C22 = malloc(row1_half * sizeof(int *));
	for(int i=0; i<row1_half; i++){
		C11[i] = malloc(col2_half * sizeof(int *));
		C12[i] = malloc(col2_half * sizeof(int *));
		C21[i] = malloc(col2_half * sizeof(int *));
		C22[i] = malloc(col2_half * sizeof(int *));
	}
	
	//initialize A
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col1_half;j++){
			A11[i][j] = matrix1[i][j];
			A12[i][j] = matrix1[i][col1_half+j];
			A21[i][j] = matrix1[row1_half+i][j];
			A22[i][j] = matrix1[row1_half+i][col1_half+j];
		}
	}
	
	//initialize B
	for(int i=0;i<row2_half;i++){
		for(int j=0;j<col2_half;j++){
			B11[i][j] = matrix2[i][j];
			B12[i][j] = matrix2[i][col2_half+j];
			B21[i][j] = matrix2[row2_half+i][j];
			B22[i][j] = matrix2[row2_half+i][col2_half+j];
		}
	}
	
	//initialize C
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col2_half;j++){
			C11[i][j]=0; C12[i][j]=0;
			C21[i][j]=0; C22[i][j]=0;
		}
	}

	//malloc M
	M1 = malloc(row1_half * sizeof(int *));   //p1
	M2 = malloc(row1_half * sizeof(int *));   //p2
	M3 = malloc(row1_half * sizeof(int *));   //p3
	M4 = malloc(row1_half * sizeof(int *));   //p4
	M5 = malloc(row1_half * sizeof(int *));   //p5
	M6 = malloc(row1_half * sizeof(int *));   //p6
	M7 = malloc(row1_half * sizeof(int *));   //p7
	for(int i=0; i<row1_half; i++){
		M1[i] = malloc(col2_half * sizeof(int *));
		M2[i] = malloc(col2_half * sizeof(int *));
		M3[i] = malloc(col2_half * sizeof(int *));
		M4[i] = malloc(col2_half * sizeof(int *));
		M5[i] = malloc(col2_half * sizeof(int *));
		M6[i] = malloc(col2_half * sizeof(int *));
		M7[i] = malloc(col2_half * sizeof(int *));
	}

	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col1_half;j++){
			M1[i][j] = 0; M2[i][j] = 0;
			M3[i][j] = 0; M4[i][j] = 0;
			M5[i][j] = 0; M6[i][j] = 0;
			M7[i][j] = 0;
		}
	}

	//time counter
	float start,end,time;
	start = clock();
	for(int i=0; i<row1_half; i++){
		for(int j=0; j<col2_half; j++){
			//calculate M
			for(int k=0;k<col1_half; k++){
				M1[i][j] += A11[i][k] * (B12[k][j]-B22[k][j]);
				M2[i][j] += (A11[i][k]+A12[i][k]) * B22[k][j];
				M3[i][j] += (A21[i][k]+A22[i][k]) * B11[k][j];
				M4[i][j] += A22[i][k] * (B21[k][j]-B11[k][j]);
				M5[i][j] += (A11[i][k]+A22[i][k]) * (B11[k][j]+B22[k][j]);
				M6[i][j] += (A12[i][k]-A22[i][k]) * (B21[k][j]+B22[k][j]);
				M7[i][j] += (A11[i][k]-A21[i][k]) * (B11[k][j]+B12[k][j]);
			}

			//count C
			C11[i][j] = M5[i][j]+M4[i][j]-M2[i][j]+M6[i][j];
			C12[i][j] = M1[i][j]+M2[i][j];
			C21[i][j] = M3[i][j]+M4[i][j];
			C22[i][j] = M1[i][j]+M5[i][j]-M3[i][j]-M7[i][j];
		}
	}
	end=clock();
	
	time = (end-start) / CLOCKS_PER_SEC * 1000;
	printf("Strassen's Computation:  %.10lf \tsec\n\n",time);
	
/*	printf("C11\n");
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col2_half;j++){
			printf("%d ",C11[i][j]);
		}
		printf("\n");
	}
	printf("C12\n");
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col2_half;j++){
			printf("%d ",C12[i][j]);
		}
		printf("\n");
	}
	printf("C21\n");
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col2_half;j++){
			printf("%d ",C21[i][j]);
		}
		printf("\n");
	}
	printf("C22\n");
	for(int i=0;i<row1_half;i++){
		for(int j=0;j<col2_half;j++){
			printf("%d ",C22[i][j]);
		}
		printf("\n");
	}
*/

}
