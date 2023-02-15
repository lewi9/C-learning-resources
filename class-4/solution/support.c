#include "support.h"

int stringToInt( char * string )
{
	char * endptr;
	errno = 0;
	int integer = strtol(string, &endptr, 10);
	if( errno )
	{
		perror(NULL);
		exit(-1);
	}
	if( *endptr )
	{
		fprintf(stderr, "%s in not intger, because: %s\n", string, endptr);
		exit(-1);
	}
	return integer;
}

void validInt( int integer )
{
	if( integer <= 0 )
	{
		fprintf(stderr, "Argument for -%c flag should be integer greater than zero\n", optopt);
	       	exit(-2);
	}
}
