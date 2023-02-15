#include "support.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

void parsing( int argc, char ** argv, int * p, int * n, int * e );
void print( int ** pid , int p );

int main( int argc, char ** argv )
{
	int p,n,e;
	parsing(argc, argv, &p, &n, &e);
	srand(p);
	int ** pid = calloc(p, sizeof(int*));
	if( !pid )
	{
		perror(NULL);
		exit(-4);
	}

	for( int i = 0; i<p; ++i )
	{
		pid[i] = calloc(3, sizeof(int));
		if( !pid[i] )
		{
			perror(NULL);
			exit(-4);
		}
	}

	for( int i = 1; i<=p; ++i )
	{
		pid[i-1][0] = fork();
		switch(pid[i-1][0])
		{
			case -1:
				perror(NULL);
				exit(-5);
			case 0:
				char X[15];
				sprintf(X, "-x%d", ( rand() % 128 )+i);
				char E[12];
				sprintf(E, "-e%d", e);
				char N[12];
				sprintf(N, "-n%d", n);
				if( execlp( "./p1", "p1", X, E, N, NULL ) == -1 )
				{
					perror(NULL);
					exit(-6);
				}
		}
	}
	for( int i=0; i<p; ++i )
	{
		siginfo_t  ptr;
		waitid( P_ALL, 0, &ptr, WEXITED );
		if( ptr.si_code == CLD_EXITED )
		{
			for( int i=0; i<p; ++i )
			{
				if( pid[i][0] == ptr.si_pid ) pid[i][1] = ptr.si_status;
			}
		}
		else
		{
			fprintf(stderr, "Child has ended work because %d\n", ptr.si_code);
			exit(-7);
		}
	}
	for( int i=0; i<=n; ++i )
	{
		char path[PATH_LENGTH];
		char iden[12];
		sprintf(path, "file_%d", i+1);
		int fd = open(path, O_RDONLY);
		if( fd == -1 ) continue;
		read(fd, iden, sizeof(iden));
		close(fd);
		int id = stringToInt(iden);
		for( int j=0; j<p; ++j )
		{
			if( pid[j][1] == id ) ++pid[j][2];
		}
		unlink(path);
	}
	print(pid, p);
}

void print( int ** pid, int p )
{
	for( int i = 0; i<p; ++i )
	{
		printf("%d\t%d\t%d\n", pid[i][0], pid[i][1], pid[i][2]);
	}
}

void parsing( int argc, char ** argv, int * p, int * n, int * e )
{
	int c;
	int flagP, flagE, flagN;
	flagP = flagE = flagN = 0;
	while( (c = getopt(argc, argv, "p:e:n:")) != -1 )
	{
		switch(c)
		{
			case 'p':
				flagP = 1;
				*p = stringToInt(optarg);
				validInt(*p);	
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
				exit(-2);
			case ':':
				fprintf(stderr, "Missing argument for flag -%c\n", optopt);
				exit(-2);
		}
	}
	if( !flagP || !flagE || !flagN )
	{
		fprintf(stderr, "USAGE: ./%s -p <int> -e <int> -n <int>; all int should be greater than 0\n", argv[0]);
		exit(-2);
	}
}
