

// You can run your compiled code e.g with command './program-name first-argument second-argument'.
// Let's handle it.


#include <stdio.h>

// Compile and run the program with some arguments.

int main( int argc, char * argv[] )
{
	// The first argument is program name, so we need compare argc with 2
	// argc is the argument count
	// argv is the argumens value

	if( argc < 2 )
	{
		printf("There is no given arguments");
		return 0;
	}

	for( int i = 0; i<argc; ++i )
	{
		printf("Argument %2d: %s\n", i+1, argv[i]); 
	}
}
