#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>


uintmax_t checkedValues();
uintmax_t primeCounter (uintmax_t  _numberP);


int main() {	   
	uintmax_t numberP, counter;
	 
	printf("A program to calculate number of primes.\n");
	printf("----------------------------------------------------\n");
	printf("\nUp to which number do you want to count prime numbers? : ");
	
	numberP = checkedValues();
	counter = primeCounter(numberP);
                
    printf("\nCounted Prime Numbers: %ju ", counter);
    
    //below code is to prevent console app exiting immediately after execution
	printf("\n");
	//system("pause");
	return 0;
}



uintmax_t primeCounter (uintmax_t _numberP)
{
	uintmax_t count=0;
	
	// Allocate memory for array.
	bool *isPrime = (bool*)malloc((_numberP+1) * sizeof(bool));
	//Check if allocation is succesful. If not, return error.
	if(!isPrime) {
		printf("Invalid pointer. Error allocating memory!\n");
		exit(EXIT_FAILURE);
	}
	
    isPrime[0] = false;
    isPrime[1] = false;
    isPrime[2] = true;
    isPrime[3] = true;
       
    //even numbers marked as false and odd numbers marked as true.
    for (uintmax_t i=4; i<_numberP; i+=2) {
        isPrime[i]   = false;
        isPrime[i+1] = true;
    }
    
    //if n is even, than above loop will skip the last element of the array. We must take care of it.
    if ((_numberP%2)==0) {
   		isPrime[_numberP] = false;
    }
       
    //mark non-primes <=N using Sieve of Eratosthenes    
    for (uintmax_t i=3; i<= sqrt(_numberP); i+=2) {
        //if is a prime,then mark multiples of i as non prime 
    	if (isPrime[i]){   
            for (uintmax_t j=i; (i*j)<=_numberP; j+=2) {
                isPrime[i*j] = false;
            }
        }
    }
        
    for(uintmax_t i=2 ; i<=_numberP; i++)
        if(isPrime[i]){
            count++;
            printf("%d. Prime Number = %d\n", count, i);
    }
    
    //Free the allocated memory.
    free(isPrime);       
    return count;   
}

uintmax_t checkedValues() {
	uintmax_t a;
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
        a = strtoull(input, &endptr, 10);
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
        else if (a >= UINTMAX_MAX || a <= 0){
        	//Check integer limits
        	printf("Sorry, this number is too small or too large! Please enter an integer.\n");
            success = false;  
        } 
		else {
            success = true;
        }
    } while (!success); // repeat until we got a valid number
    return a;
}
