#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	
	// Print the required text - "Hello world!"
   	printf("Hello world!\n");

	int min = 0; 	// Lower Limit for random number
	int max = 199;	// Upper Limit for random number

	/* Here, rand() function is used to generate the random number
	 * By default it returns a random number between 0 and RAND_MAX
	 * In order to restrict the limit between 0 and 199, 
	 * we shall divide the random number by 199 - 0 + 1 = 200 and find the remainder
	 * The remainder is then added to the lower limit (0) to get a value between 0 and 199*/

	/* srand() function is used to initialize random number generators
	 * Without srand() we would get the same random number whenever the output file is run
	 * The argument to srand() is a seed that is used by a random number generator
	 * Different input arguments to srand ensures a different random number when the file is run
	 * time() function returns UTC time in seconds. This serves as a unique input for srand()*/

	srand(time(0));
	
	int random = min + rand() % (max - min + 1);
	
	// Print the required text - Random number whose value is between 0 and 199
	printf("%d\n", random);	
	
	// Print the required text - Blank line
	printf("\n");

	// Exit
   	return 0;
}
