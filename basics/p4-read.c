

// Now we will read some data from file
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// Let's declare an global array

#define SIZE 64
char array[SIZE];

void printAsInteger();

// Complete the declaration of these functions.
void printAsFloat();
void printAsDouble();
void printAsLongDouble();


int main( int argc, char * argv[] )
{
	// First is needed to open the file
	int file = open("/dev/urandom", O_RDONLY);

	// "/dev/urandom" is path to file. This is special Unix file; it provides random numbers.
	// O_RDONLY is flag and means READ ONLY, so we can only read from that file.
	
	// Error handling
	
	if( file == -1 )
	{
		// Note how perror works. He will print a given message, semicolon and error mesage
		// e.g. "File open: <error message>"
		perror("File open");
		exit(EXIT_FAILURE);
	}

	// Reading read(<file_descriptor>, <pointer_to_adress_where_data_will_be_saved>, <how_much_bytes_read>)
	// read return number of readed bytes. In case of error -1 is returned.

	//Both forms are correct
	//ssize_t readed = read(file, array, SIZE);
	int readed = read(file, array, SIZE);

	if( readed == -1 )
	{
		perror("Read");
		exit(EXIT_FAILURE);
	}

	printAsInteger();

	printAsFloat();

	printAsDouble();

	printAsLongDouble();

	exit(EXIT_SUCCESS);
}

void printAsFloat()
{
	//Your code here
}
void printAsDouble()
{
	//Your code here
}
void printAsLongDouble()
{
	//Your code here
}

void printAsInteger()
{
	for( int i = 0; i<SIZE/sizeof(int); ++i )
	{
		printf("Number %2d: %-*d\n", i+1, 18, ((int *)array)[i]);
	}
}

