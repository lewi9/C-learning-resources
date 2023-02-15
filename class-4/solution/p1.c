#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "support.h"


void parsing( int argc, char ** argv, int * x, int * e, int * n );

int main( int argc, char ** argv )
{
	int x, e, n;
	parsing(argc, argv, &x, &e, &n);
	srand(x);
	int id = rand()%x;
	char iden[12];
	sprintf(iden, "%d", id);
	int counter = e;
	while( counter!=0 )
	{
		int j = rand()%n+1;
		char path[PATH_LENGTH];
		sprintf(path, "file_%d", j);
		int fd = open(path, O_CREAT|O_WRONLY|O_EXCL, 00666);
		if( fd == -1 )
		{
			--counter;
			continue;
		}
		write(fd, iden, sizeof(iden));
		close(fd);
		counter = e;
		struct timespec d = {0, 10000000l};
		if( nanosleep(&d,NULL) )
		{
			perror(NULL);
			exit(-3);
		}
	}
	return id;
}


void parsing( int argc, char ** argv, int * x, int * e, int * n )
{
	int c;
	int flagX, flagE, flagN;
	flagX = flagE = flagN = 0;
	while( (c = getopt(argc, argv, "x:e:n:")) != -1 )
	{
		switch(c)
		{
			case 'x':
				flagX = 1;
				*x = stringToInt(optarg);
				validInt(*x);	
				break;
			case 'e':
				flagE = 1;
				*e = stringToInt(optarg);
				validInt(*e);				
				break;
			case 'n':
				flagN = 1;
				*n = stringToInt(optarg);
				validInt(*n);	
				break;
			case '?':
				fprintf(stderr, "Unknown flag -%c\n", optopt);
				exit(2);
			case ':':
				fprintf(stderr, "Missing argument for flag -%c\n", optopt);
				exit(2);
		}
	}
	if( !flagX || !flagE || !flagN )
	{
		fprintf(stderr, "USAGE: ./%s -x <int> -e <int> -n <int>; all int should be greater than 0\n", argv[0]);
		exit(-2);
	}
}
