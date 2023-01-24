
// Usage of write function

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( int argc, char * argv[] )
{
	if( argc != 2 )
	{
		fprintf(stderr, "You should 1 path give");
		return 1;
	}

	// creat is responsible for creating a file. 
	// First argument is path to file, the second one is file mode bits in octal. 00666 - read and write
	// creat(path, 00666) is equal to open(path, O_CREAT|O_WRONLY|O_TRUNC, 00666)
	int file = creat( argv[1], 00666 );


	int arr[5] = {4, 34684, 356843, 23589, 56};

	// If you want write something to file, you need call write() function.
	// The first argument is path, the second is pointer to data, the third is size of data
	// if error -1 is returned
	if( write(file, arr, sizeof(int)*5) == -1 )
	{
		perror(NULL);
		return 2;
	}
	close(file);
	return 0;
}
