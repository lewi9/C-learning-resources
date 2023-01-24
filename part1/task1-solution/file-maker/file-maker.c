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

	int file = creat( argv[1], 00666 );

	int arr [5] = {4, 34684, 356843, 23589, 56};
	write(file, arr, sizeof(int)*5);
	close(file);
	return 0;
}
