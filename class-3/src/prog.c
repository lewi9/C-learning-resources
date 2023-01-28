#include "prog.h"

int main( int argc, char * argv[] )
{
	if( argc != 3 )
	{
		fprintf(stderr, "USAGE: <string> <int>\n");
		return 1;
	}
	char * endptr;
	int n = strtol(argv[2], &endptr, 10);
	if( *endptr )
	{
		perror("STRTOL");
		return 2;
	}
	function(argv[0], argv[1], n);
}
