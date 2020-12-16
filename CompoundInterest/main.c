#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	double compRatePer;
	double compRateDec;
	int numPerYear;
	int years;
	double principal;
	
	double partA = 1;
	
	double compoundTotal;
	double compoundOnly;
	
	printf("Welcome to compound interest calculator.\n");
	printf("Enter the principal, starting money : ");
	scanf("%lf", &principal);
	printf("Enter the interest rate. (For %%x interest, enter x) : ");
	scanf("%lf", &compRatePer);
	printf("Enter compound interval. (For exp. mounthly -> 12 , daily -> 365) : ");
	scanf("%d", &numPerYear);
	printf("Enter calculation period. (For n years, enter n) : ");
	scanf("%d", &years);
	
	compRateDec = compRatePer / 100;
	for (int i = 0; i < (numPerYear*years); i++) {
		partA *= (1 + (compRateDec/numPerYear));
	}
	
	compoundTotal = principal * partA;
	compoundOnly = compoundTotal - principal;
	
	printf("\nThe compounded money after %d years : %.2f\n", years, compoundTotal);
	printf("The amount of interest earned : %.2f\n", compoundOnly);
	
	//below code is to prevent console app exiting immediately after execution
	printf("\n");
	system("pause");
	return 0;
}
