
// Family of strto functions


// strtol - convert string to long
// long strtol( char * ptr, char ** endptr, int base)
// First argument is pointer to string
// The second one argument is pointer
// after conversion *ednptr will point the next character after digits
// If there is no chars after digits, it will point 0
// base - numeric system e.g. 10 - result will be decimal number:w
//
// strtod - to double
// strtof - to float
// strtold - long double
//
// double strtod(char * ptr, char ** endptr)
// First argument is pointer to string
// The second one argument is pointer
// after conversion in *endptr will be stored addres of the next character after digits
// if there is no chars, NULL will be stored

// strtok - ...
// later

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define SIZE 5

void toL( char ** strings );
void toF( char ** strings );
void toD( char ** strings );

int main( int argc, char ** argv )
{
	char * str1 = "Lorem Ipsum";
	char * str2 = "123.56abc";
	char * str3 = "3.402823e+40";
	char * str4 = "123.42";
	char * str5 = "-2";
	char * strings[SIZE] = {str1, str2, str3, str4, str5};
	toL(strings);
	toF(strings);
	toD(strings);
	return 0;
}

void toL( char ** strings )
{
	char * endptr;
	for( int i=0; i<SIZE; ++i )
	{
		errno = 0;
		endptr = NULL;
		long ld = strtol( strings[i], &endptr, 10 );
		// Simple error Handling, but only if 0 is assigment to the errno immediately before strto*() call
		if( errno )
		{
			perror(NULL);
			//exit(EXIT_FAILURE);
		}
		if( *endptr )
		{
			fprintf(stderr, "Invalid string given to conversion: %s\n", strings[i]);
			//exit(EXIT_FAILURE);
		}
		printf("%s after conversion: %ld\n", strings[i], ld);
		printf("*endptr after conversion: %c\nendptr after conversion:%s\n\n",*endptr, endptr);
	}
	printf("\n\n");
}
void toF( char ** strings )
{
	char * endptr;
	for( int i=0; i<SIZE; ++i )
	{
		errno = 0;
		endptr = NULL;
		float f = strtof( strings[i], &endptr );
		// Simple error Handling, but only if 0 is assigment to the errno immediately before strto*() call
		if( errno )
		{
			perror(NULL);
			//exit(EXIT_FAILURE);
		}
		if( *endptr )
		{
			fprintf(stderr, "Invalid string given to conversion: %s\n", strings[i]);
			//exit(EXIT_FAILURE);
		}

		printf("%s after conversion: %f\n", strings[i], f);
		printf("*endptr after conversion: %c\nendptr after conversion:%s\n\n",*endptr, endptr);
	}
	printf("\n\n");
}
void toD( char ** strings )
{
	char * endptr;
	for( int i=0; i<SIZE; ++i )
	{
		errno = 0;
		endptr = NULL;
		double lf = strtod( strings[i], &endptr );
		// Simple error Handling, but only if 0 is assigment to the errno immediately before strto*() call
		if( errno )
		{
			perror(NULL);
			//exit(EXIT_FAILURE);
		}
		if( *endptr )
		{
			fprintf(stderr, "Invalid string given to conversion: %s\n", strings[i]);
			//exit(EXIT_FAILURE);
		}

		printf("%s after conversion: %lf\n", strings[i], lf);
		printf("*endptr after conversion: %c\nendptr after conversion:%s\n\n",*endptr, endptr);
	}
	printf("\n\n");
}

