
// Lseek.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>



// You can compile code from this file and merge with another .o(bject) file
// In p3-lseek.h are declared two functions and struct Row
// Code of that functions is delivered in p3-compiled-code.o
// To compile type something like:
// gcc -Wall p3-lseek.c p3-compiled-code.o -o p3
// gcc <flags> <name of file .c> <name of file .o> -o <result file>

#include "p3-lseek.h"

#define SIZE 50

#define OUTPUT_FILE "res-p3.bin"

void writer( int fd, Row * ptr, int size );

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

	close(file);

	numberToRange( 0, 50, array, SIZE );

	file = open(OUTPUT_FILE, O_CREAT|O_WRONLY|O_TRUNC, 00666);

	writer( file, array, SIZE );

	close( file );

	free( array );
	return 0;
}

void writer( int fd, Row * ptr, int size )
{
	for( int i=0; i<size; ++i)
	{
		// lseek is responsible for cursor "move"
		// first argument is file descriptor
		// second is how much bytes move
		// third is type of move
		// here the second argument is equal size of structure row * value of field number
		// if number == 3, the cursos will move by 3 sizes of structure row
		// result will be
		// 0 0 0 ... <- row is size of structure row
		// 0 0 0 ...
		// 0 0 0 ...
		// data....
		// SEEK_SET will set move from byte 0 to number, so cursor will be just on second argument position
		// SEEK_CUR will move from current position about x bytes
		// SEEK_END will move from end of file about x bytes
		if( lseek(fd, sizeof(Row) * ptr[i].number, SEEK_SET) == -1 )
		{
			perror("LSEEK");
			exit(EXIT_FAILURE);
		}
		if( write(fd, ptr+i, sizeof(Row)) == -1 )
		{
			perror("WRITE");
			exit(EXIT_FAILURE);
		}
	}
}
