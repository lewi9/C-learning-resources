

// Structures.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define SIZE 50

// Declare structure with typedef

typedef struct Row{
	short number;
	char info[5];
	double value;
}Row;

void printRowPtr( Row * ptr );

// Implement missing function
// It should change value of short number to be in range [lower, upper+lower)
// e.g
// row[1].number == 124124
// row[2].number == -12451
// => using function [lower = 10, upper = 20] =>
// row[1].number == 14
// row[2].number == 21
// size means how many Rows are in Row*
void numberToRange( int lower, int upper, Row * ptr, int size );

int main( int argc, char * argv[] )
{
	int file = open("/dev/urandom", O_RDONLY);
	
	Row * array = calloc(SIZE, sizeof(Row));

	if( !array )
	{
		perror(NULL);
		return 1;
	}

	if( read(file, array, sizeof(Row)*SIZE) == -1 )
	{
		perror(NULL);
		return 2;
	}
	printRowPtr( array );
	free( array );
	close( file );
	return 0;
}

void printRowPtr( Row * ptr )
{
	Row * p = ptr;
	for( int i = 0; i<SIZE; ++i, ++p )
	{
		// Different ways to get acces to structure fields.
		printf("Number :%hd\tInfo:%.4s\tValue:%lf\n", ptr[i].number, (*p).info, p->value);	
	}
}
