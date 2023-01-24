
// To compile program on Unix systems you can use gcc
// Example of using gcc command to compile that program
// gcc -Wall <program-code> -o <result-program-name>
// gcc -Wall p1-size-of-variables.c -o p1
//
// For more details read the manual

// When do you want read more about any of used commands you can read manual. Often this is page 2 or 3
// e.g man 3 printf 


// Let's check the size of differents types in C language

#include <stdio.h>



int main( int argc, char * argv[] )
{
	printf("Sizeof %-12s: %-2lu\n", "char", sizeof(char) );
	printf("Sizeof %-12s: %-2lu\n", "short", sizeof(short) );
	printf("Sizeof %-12s: %-2lu\n", "integer", sizeof(int) );
	printf("Sizeof %-12s: %-2lu\n", "unsigned int", sizeof(unsigned int) );
	printf("Sizeof %-12s: %-2lu\n", "long", sizeof(long) );
	printf("Sizeof %-12s: %-2lu\n", "long long", sizeof(long long) );
	printf("Sizeof %-12s: %-2lu\n", "float", sizeof(float) );
	printf("Sizeof %-12s: %-2lu\n", "double", sizeof(double) ); 
	return 0;
}
