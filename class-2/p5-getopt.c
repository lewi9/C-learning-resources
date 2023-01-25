

// getopt.
// This is very usefull tool.


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// compile code and check some usages
// ./prog -a 23
// ./prog -a 245 -a 242
// ./prog -a 142 -c 345 random_path
// ./prog random_path -a 12
// ./prog -a -b -c 12
// ./prog random_path -b -c 12 -a
// ./prog random_path_first -a 124 random_path_second -b 
// ./prog -a 12421 random_path -d 12

int main( int argc, char ** argv )
{
	// set flags to 0
	int flagA, flagB, flagC, flagPath;
	flagA = flagB = flagC = flagPath = 0;

	char a[10];
	char c[10];
	char path[20];

	// declare int to get option
	int n;

	// "-:a:bc:" define what flags we are searching
	// "-:" - position argument, it must be first
	// "a:" - -a flag with value
	// "b" - -b flag without value
	// "c:" - -c flag with value 
  	while ( (n = getopt(argc, argv, "-:a:bc:")) != -1 ) 
	{
		switch (n) 
		{    
			//when -a is given
			case 'a':
				// check flag to be immune for redeclare flags (sometimes we can allow to redeclaring flags)
				if( !flagA )
				{
					flagA = 1;
					// optarg value is value provided bu user

					// NOTE THAT VALUE OBTAINED BY ERRNO IS STRING, SO IF WE WANT OBTAIN LONG WE NEED TO USE STRTOL
   					printf("Option a has arg: %s\n", optarg);

					// It's forbiden assign string to array, it's needed to use strcpy
					// strcpy(destionation, source)
					strcpy(a, optarg);
					break;	
				}
				// not perror(); because perror is connected with errno
				// in that case errno won't be set, because that's not error of function workin
				// That is error because we DEFINE that is error
				// So using fprintf is better in that case
				fprintf(stderr, "You cannot redeclare flag -a\n");
				exit(EXIT_FAILURE);
			case 'b':
				if( !flagB )
				{
					flagB = 1;
					printf("Option b was provided\n");
					break;
				}
				fprintf(stderr, "You cannot redeclare flag -b\n");
				exit(EXIT_FAILURE);
			case 'c':
				// now we allow to redeclare flag c
				flagC = 1;
				printf("Option c has arg: %s\n", optarg);
				strcpy(c, optarg);
				break;
			// This case is when user provides unknown flag - not specific in string "-:a:bc:" e.g. -d
			case '?':
				printf("Unknown option: %c\n", optopt);
				break;
			// This case is when user provides flag without value. User should provide -a 123, when provides -a without value this case is called
			case ':':
				printf("Missing arg for %c\n", optopt);
				break;
			// This case handle positional argument
			case 1:
				// we allow to redeclare path
				printf("Non-option arg: %s\n", optarg);
				flagPath = 1;
				strcpy(path, optarg);
				break;
		}	
	}

	// Now we can check required argument
	// e.g -a and path can be requierd
	
	if( !flagA || !flagPath )
	{
		fprintf(stderr, "Flag -a and Path (positional argument) are required\n");
		exit(EXIT_FAILURE);
	}

	if( flagB )
	{
		printf("a Value: %s\tc Value: %s\tpath: %s\n", a, c, path);
	}
  	return 0;
}



