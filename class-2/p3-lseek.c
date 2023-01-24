
// Lseek.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "p3-lseek.h"

#define SIZE 50

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
	printRowPtr( array, SIZE );
	free( array );
	close( file );
	return 0;
}


