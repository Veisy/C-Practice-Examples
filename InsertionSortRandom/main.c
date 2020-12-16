#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>
#include <errno.h>

#define MAX_SIZE 10000
#define LOTTERY_SIZE 6
#define LOTTERY_MAX 49

//This program requires at least C99. Change the C version as C99 or C11 in compiler options.
 


// Here we store fields for array.
typedef struct NumberArray
{
	int size;
	int max;
	int *array;
}NumberArray;


//Function declarations. Functions are defined below.
int checkedValues(int option);
void createArray(NumberArray arr, int option);
void insertionSort (NumberArray arr);


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
	
	if (arrayMenu == 3) {
		arrayObject.size = LOTTERY_SIZE;
		arrayObject.max = LOTTERY_MAX;
		int arrayRandom[arrayObject.size];
		arrayObject.array = &arrayRandom[0];	
		
		printf("How many lottery game do you want to generate ? : ");
		int lotteryNumber = checkedValues(2);
		
		for (int i = 0; i < lotteryNumber; i++){
			createArray(arrayObject, arrayMenu);	
			insertionSort(arrayObject);
		}
				
	} else {
		printf("Enter the size of the array: ");
		arrayObject.size = checkedValues(2);
		
		int arrayRandom[arrayObject.size];
		arrayObject.array = &arrayRandom[0];	
	
		createArray(arrayObject, arrayMenu);	
		printf("\n\n------------\n");
  		printf("Order of Sorted elements: ");
		insertionSort(arrayObject);
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
		printf("Enter value range of the array elements: ");
		arr.max = checkedValues(0);
		printf("\n\n------------\n");
		printf("The Random Array: ");
		
	} else if (option = 3) {
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
			
		} else if (option == 2 || option == 3) {
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
			
		} 	else {
			printf("\nError! Invalid array operation. Check arguments of the function.");
			exit(EXIT_FAILURE);
		}
	} 	
}



//This function sort the elements of the array.
	/*
	The Algorithm :
	1 - If it is the first element, it is already sorted.
	2 - Pick the next element.
	3 - Compare with all the elements in sorted sub-list.
	4 - Shift all the the elements in sorted sub-list that is greater than the value to be sorted.
	5 - Insert the value.
	6 - Repeat until list is sorted.
	*/
void insertionSort (NumberArray arr) 
{
	int tempValue;
	
	for(int j, i = 1; i < arr.size; i++){
		
     	j = i;

        while ( j > 0 &&  *( arr.array + (j-1) ) > *(arr.array + j) ){	        
			tempValue              = *(arr.array + j);
			*(arr.array + j)       = *( arr.array + (j-1) );
        	*( arr.array + (j-1) ) = tempValue;
            j--;
            }
  	}
  	//Print sorted elements.

  	for(int i = 0; i < arr.size; i++){
    	printf(" %d", * ( arr.array + i));
	}
} 



// Used the same function again (with some modification) that I created to check inputs, if they are valid integer or not.
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
        if (*endptr && *endptr != '\n') {
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
		} 
		else if ( (option == 1) && !(a == 1 || a == 2 || a == 3) ) {
			printf("Invalid option. Try again.\n");
            success = false;
		}
		else {
            success = true;
        }
    } while (!success); // repeat until we got a valid number
    return a;
}
