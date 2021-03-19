#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>
#include <errno.h>

#define MAX_SIZE 10000 //maximum size of an array allowed in this program.
#define LOTTERY_SIZE 6 //size of a lottery array.
#define LOTTERY_MAX 49 //max value of a lottery number.

 
/* This program is converted from my upgrated InsertionSort program, which use insertion algorithm instead if merge algorithm.
 * InsertionSort function is replaced with MergeSort function.
 * This program has two options to create an array, and an extra feature to create lottery numbers (Six random number up to 49).
*/
 
//This program requires at least C99. Change the C version as C99 or C11 in compiler options.
 
// Here we store fields for array.
typedef struct NumberArray
{
	int size;
	int max;
	int *array;
}NumberArray;


//Function declarations. Functions are defined below the main function.
int checkedValues(int option);
void createArray(NumberArray arr, int option);
void printArray(NumberArray A);
void merge(NumberArray A, NumberArray L, NumberArray R);
void mergeSort(NumberArray A);

int main() {
	
	//Here we create fields for NumberArray struct. 
	NumberArray arrayObject;
	
	//srand() sets the seed which is used by rand to generate “random” numbers.
	//If we don't use srand function, we will have the same random numbers at each run.
	srand(time(0)); 
	
	
	printf("[1] Manuel Entrance\n");
	printf("[2] Random Integer Array\n");
	printf("[3] Lottery Number Generator\n");
	int arrayMenu = checkedValues(1);
	
	//If block for Lottery option, else block for other two option.
	
	if (arrayMenu == 3) {
		//Fields for third option
		arrayObject.size = LOTTERY_SIZE;
		arrayObject.max = LOTTERY_MAX;
		int arrayRandom[arrayObject.size];
		arrayObject.array = &arrayRandom[0];	
		
		printf("How many lottery game do you want to generate ? : ");
		int lotteryNumber = checkedValues(2);
		
		for (int i = 0; i < lotteryNumber; i++){
			//Here we create lottery objects and sort them with mergeSort, and print with printArray.
			createArray(arrayObject, arrayMenu);	
			mergeSort(arrayObject);
			printArray(arrayObject);
		}
				
	} else {
		//Option 1 and Option 2 run here.
		
		printf("Enter the size of the array: ");
		arrayObject.size = checkedValues(2);
		
		int arrayRandom[arrayObject.size];
		arrayObject.array = &arrayRandom[0];	
		
		//Array is created and sorted with mergeSort.
		createArray(arrayObject, arrayMenu);	
		printf("\n\n------------\n");
  		printf("Order of Sorted Elements: ");
		mergeSort(arrayObject);
		printArray(arrayObject);
		printf("\n\n------------\n");
	}
	
	//below code is to prevent console app exiting immediately after execution
	printf("\n");
	system("pause");
	return 0;
}



//An array creation function. Takes NumberArray struct as an argument. Option 1 : manuel array , Option 2: random array, Option 3: random lottery array 
void createArray(NumberArray arr, int option)
{
	//This is a flag used to create a random array with unique elements.
	bool uniqueFlag;
	
	printf("\n------------\n");
	
	if (option == 1) {
		printf("The Manuel Array:\n");
		
	} else if (option == 2){
		printf("Enter the value range of the array elements: ");
		arr.max = checkedValues(0);
		printf("\n\n------------\n");
		printf("The Random Array: ");
		
	} else if (option == 3) {
		//Empty
	} else {
		printf("Invalid menu option is passed as an argument.");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 0; i < arr.size; i++) {
		if (option == 1) {
			//Create an array which has a size of arraySize and value range of arrayValueRange.
			printf("[%d]: ", i);
			*(arr.array + i) = checkedValues(0);
			
		} else  {
			//Create an random array which has a size of arraySize and value range of arrayValueRange. Min value is 1, Max value is arr.max
			//If value range is equal or qreater than array size, we seek uniqueness. This is a rule that I made up at my own sweet will.
			do {
				*(arr.array + i) = ( rand() % arr.max ) + 1;
				uniqueFlag = false;
				if (arr.max >= arr.size &&  i >= 1) {
					for (int j = 0; j < i ; j++) {
						if ( *(arr.array + j) == *(arr.array + i) )
							 uniqueFlag = true;
					}
				}
				
			} while (uniqueFlag);
			
			if (option == 2) {
				//Print created array.
				printf(" %d", *(arr.array + i) );
			}	
			
		}
	} 	
}



void printArray(NumberArray A) {
	for(int i = 0; i < A.size; i++){
	    	printf(" %d", * ( A.array + i));
	}
}


void merge(NumberArray A, NumberArray L, NumberArray R) {
	int i,j,k;

	// i - to mark the index of left sub-array (L)
	// j - to mark the index of right sub-array (R)
	// k - to mark the index of merged sub-array (A)
	i = 0; j = 0; k =0;

	while(i < L.size && j < R.size) {
		if(L.array[i]  < R.array[j]) A.array[k++] = L.array[i++];
		else A.array[k++] = R.array[j++];
	}
	while(i < L.size) A.array[k++] = L.array[i++];
	while(j < R.size) A.array[k++] = R.array[j++];
}

// Recursive function to sort an array of integers. 
void mergeSort(NumberArray A) {
	NumberArray L, R;
	int mid,i;
	if(A.size < 2) return; // base condition. If the array has less than two element, do nothing. 

	mid = A.size/2;  // find the mid index.
	L.size = mid;
	R.size = (A.size - mid); 

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array 
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L.array = (int*)malloc(L.size*sizeof(int)); 
	R.array = (int*)malloc(R.size*sizeof(int)); 
	
	for(i = 0; i < mid; i++) L.array[i] = A.array[i]; // creating left subarray
	for(i = mid; i < A.size; i++) R.array[i-mid] = A.array[i]; // creating right subarray

	mergeSort(L);  // sorting the left subarray
	mergeSort(R);  // sorting the right subarray
	merge(A, L, R);  // Merging L and R into A as sorted list.
	
    free(L.array);
    free(R.array);
}



// Used the function that I created to check inputs, if they are valid integer or not.
// option  1 for menu restrictions, option 2 for array size.
int checkedValues(int option) 
{
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
        }
        else if (endptr == input) {
            // no character was read
            printf("Please enter an integer.\n");
            success = false;
        }
        else if (errno == ERANGE || a <= 0){
        	//Check integer limits
        	printf("Sorry, this number is too small or too large! Please enter an integer.\n");
            success = false;  
        } else if (option == 2 && a > MAX_SIZE) {
        	printf("Max size defined as 10000. Please enter an integer smaller than this: ");
            success = false; 
		} else if ( (option == 1) && !(a == 1 || a == 2 || a == 3) ) {
			printf("Invalid option. Try again.\n");
            success = false;
		} else {
            success = true;
        }
    } while (!success); // repeat until we got a valid number
    return a;
}
