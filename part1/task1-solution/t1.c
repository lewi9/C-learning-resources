#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// fd - file descriptor, this is result of open function
// int fd = open(path, flags)

int * createArray( int fd, int * N );

void readNumbers( int fd, int * ptr, int size );

void printNumbers( int * ptr, int size );

void freeHandler( int ev, void * ptr )
{
	free(ptr);
}

int main( int argc, char * argv[] )
{
	if( argc < 2 )
	{
		fprintf(stderr, "There is no file path given.\n");
		return 3;
	}

	if( argc > 2 )
	{
		fprintf(stderr, "Too much paths were given.\n");
		return 3;
	}

	int file = open(argv[1], O_RDONLY);
	int N = 0;
	int * ptr = createArray( file, &N );
	readNumbers( file, ptr, N );
	printNumbers( ptr, N);
	close(file);
	return 0;
}

int * createArray( int fd, int * N )
{
	if( read(fd, N, sizeof(int)) == -1 )
	{
		perror("READ");
		exit(EXIT_FAILURE);
	}

	int * array = calloc(*N, sizeof(int));
	if( !array )
	{
		perror("CALLOC");
		exit(EXIT_FAILURE);
	}

	on_exit(freeHandler, array);

	return array;
}

void readNumbers( int fd, int * ptr, int size )
{
	if( read( fd, ptr, sizeof(int)*size ) == -1 )
	{
		perror("READ");
		exit(EXIT_FAILURE);
	}
}

void printNumbers( int * ptr, int size )
{
	int * p = ptr;
	char string[14];
	for( int i = 0; i<size; ++p, ++i )
	{
		int firstDigit = *p;
		while( firstDigit >= 10 )
			firstDigit /= 10;
		sprintf(string, "%d", *p);
		printf("%.*s\n", firstDigit , string);
	}
}

