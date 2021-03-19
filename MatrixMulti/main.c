#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>


// This struct collects matrix fields under one roof.
typedef struct Matrix
{
	int *row;
	int *col;
	int *matrix;
}Matrix;

//Function declarations. Functions defined and explained below the main.
void matrixOperation(int operationNumber, Matrix _matrix); 
void matrixMulti (Matrix _firstMatrix, Matrix _secondMatrix, Matrix _newMatrix);
int checkedValues(int option);

int main() {
	int firstMatrixRow, firstMatrixCol, secondMatrixRow, secondMatrixCol;
	bool notValid = true;
	
	//srand() sets the seed which is used by rand to generate “random” numbers.
	//If we don't use srand function, we will have the same random numbers at each run.
	srand(time(0));
	
	// Take inputs from user, if dimensions are valid continue. Otherwise ask again.
	while (notValid){
		//Dimensions from user.
		printf ("Write the ROW and COLUMN of FIRST MATRIX respectively :\n");
		firstMatrixRow = checkedValues(1);
		firstMatrixCol = checkedValues(1);
		printf ("-----------------\n");
		printf ("Write the ROW and COLUMN of SECOND MATRIX respectively :\n");
		secondMatrixRow = checkedValues(1);
		secondMatrixCol = checkedValues(1);
		
		//Check if multiplication valid or not.
		if (firstMatrixCol == secondMatrixRow) {
			
			//Creation of array(matrix) fields.
			int firstMatrix[firstMatrixRow][firstMatrixCol];
			int secondMatrix[secondMatrixRow][secondMatrixCol];
			int newMatrix[firstMatrixRow][secondMatrixCol];
			
			//Data fields stored. Because of working with pointers, we store their addresses.
			//It stores the starting address of matrixes, we do pointer arithmetic to access all elements.
			Matrix dataFirstMatrix = {&firstMatrixRow, &firstMatrixCol, &firstMatrix[0][0]};
			Matrix dataSecondMatrix ={&secondMatrixRow, &secondMatrixCol, &secondMatrix[0][0]};
			Matrix dataNewMatrix ={&firstMatrixRow, &secondMatrixCol, &newMatrix[0][0]};
				
			notValid = false;
			printf ("--------------------------------------\n");
			printf ("The Matrix is Valid. Continue..\n");
			
			//Menu
			printf("[1] Manuel Entrance\n");
			printf("[2] Random Entrance\n");
			int matrixMenu = checkedValues(2);
			
			if (matrixMenu == 1) {
				//Write and print arrays(matrixes).
				printf("FIRST MATRIX : \n");
				matrixOperation(1, dataFirstMatrix);
				matrixOperation(2, dataFirstMatrix);
				printf("Second MATRIX : \n");
				matrixOperation(1, dataSecondMatrix);
				matrixOperation(2, dataSecondMatrix);					
			} else if (matrixMenu == 2) {
				//This part is the same thing for random operation
				matrixOperation(3, dataFirstMatrix);
				matrixOperation(3, dataSecondMatrix);		
			} else {
				return -1;
			}
			
			//Results.		
			matrixMulti(dataFirstMatrix, dataSecondMatrix, dataNewMatrix);
			printf("FIRST MATRIX : \n");
			matrixOperation(2, dataFirstMatrix);
			printf("Second MATRIX : \n");
			matrixOperation(2, dataSecondMatrix);
			printf("NEW MATRIX : \n");
			matrixOperation(2, dataNewMatrix);
					
		} else {
				printf("Unvalid calculation! The column of column of first matrix have to be equal to row of the second matrix!\n");
				printf ("--------------------------------------\n");
		}
	}
	
	//below code is to prevent console app exiting immediately after execution
	printf("\n");
	system("pause");
	return 0;
}

//Matrix operators. 1 --> Matric creation , 2 --> Print matrix, 3 --> Random matrix
void matrixOperation(int operationNumber, 
					 Matrix _matrix)
{
	if (operationNumber == 2) //Decoration only for print operator
		printf ("-----------\n");
		
	for (int i=0; i < *_matrix.row; i++) {
			for (int j=0; j < *_matrix.col; j++) {
				if (operationNumber == 1) {
					*_matrix.matrix = checkedValues(0);
					*_matrix.matrix++;
				} else if (operationNumber == 2) {
					printf("%d  ", *_matrix.matrix);
					_matrix.matrix++;
				} else if (operationNumber == 3) {
					*_matrix.matrix = rand() % 10;
					 _matrix.matrix++;
				} else {
					printf("\nError! Invalid array operation. Check arguments of the function.");
					exit(EXIT_FAILURE);
				}			
			}
			printf("\n");	
	}
	
	if (operationNumber == 2) ////Decoration only for print operator
		printf ("-----------\n\n");					
}

//Matrix multiplication function.
void matrixMulti (Matrix _firstMatrix, 
			      Matrix _secondMatrix, 
				  Matrix _newMatrix)
{				
	//New one calculated.
	int sum;
	for (int i=0; i < *_firstMatrix.row ; i++) {
		for (int j=0; j < *_secondMatrix.col; j++) {
			sum = 0; 
			for (int k = 0; k < *_secondMatrix.row; k++){
				//sum +=  firstMatrix[i][k] * secondMatrix[k][j];
				//Since array decayed to a pointer, life is not that easy anymore. We need to do some math.
				sum +=  (*(_firstMatrix.matrix + i*(*_secondMatrix.row) + k)) * (*(_secondMatrix.matrix + k*(*_secondMatrix.col) + j));
			}
			*(_newMatrix.matrix + i*(*_secondMatrix.col) + j) = sum;
			//newMatrix[i][j] = sum;
		}
	}
}

// This function check integer inputs are valid or not, and some possible error cases.
// option 1 for dimention restrictions, option 2 for menu restirictions.
int checkedValues(int option) {
	long a;
    char input[1024]; // just to be sure
    bool success; // flag for successful conversion
    do {
        if (!fgets(input, 1024, stdin)) {
            // reading input failed:
            return 1;
        }
		
        // have some input, convert it to integer:
        char *endptr;
        errno = 0; // reset error number
        a = strtol(input, &endptr, 10);
        if (*endptr != '\n') {
            // *endptr is neither end of string nor newline,
            // so we didn't convert the *whole* input
            printf("Please enter an integer.\n");
            success = false;
        } else if (endptr == input) {
            // no character was read
            printf("Please enter an integer.\n");
            success = false;
        } else if (errno == ERANGE || a <= 0){
        	//Check integer limits
        	printf("Sorry, this number is too small or too large! Please enter an integer.\n");
            success = false;  
        } else if ((option == 1) && (a > 100)){
			//This part for dimentions. Check whether dimentions exceed 100 or not.
			printf("Please mind that MAX value for this operation is 100.\n");
            success = false;		
		} else if ((option == 2) && !(a == 1 || a == 2)) {
			printf("Invalid option. Try again.\n");
            success = false;
		} else {
            success = true;
        }
    } while (!success); // repeat until we got a valid number
    return a;
}
