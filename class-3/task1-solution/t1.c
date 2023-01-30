
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parsing( int argc, char ** argv, char ** arguments);
char * parseOption( int * flag, char * string, char param );

void errorP( char * message, int code ) { perror(message); exit(code); }

int main( int argc, char ** argv )
{
	char * arguments[4];
	parsing( argc, argv, arguments);
	int fd1 = open(arguments[0], O_RDONLY);
	if( fd1 == -1 ) errorP("OPEN", 3);
	int fd2 = open(arguments[1], O_CREAT|O_TRUNC|O_WRONLY, 00666);
	if( fd2 == -1 ) errorP("OPEN", 3);
	if( dup2(fd1, 0) == -1 ) errorP("DUP", 4);
	if( dup2(fd2, 1) == -1 ) errorP("DUP", 4);
	execlp("tr", "tr", arguments[2], arguments[3], NULL);
	return 0;
}


char * parseOption( int * flag, char * string,  char param )
{
	if( !*flag )
	{
		*flag = 1;
		char * option = calloc(strlen(string), 1);
		if( !option ) errorP("CALLOC", 1);
		strcpy( option, string );
		return option;
	}
	fprintf(stderr, "Redifined flag -%c\n", param);
	exit(2);
}

void parsing( int argc, char ** argv, char ** arguments )
{
	int flagI, flagO, flagT, flagX;
	flagI = flagO = flagT = flagX = 0;
	int c = 0;
	while( (c = getopt(argc, argv, "i:o:t:x:")) != -1 )
	{
		switch(c)
		{
			case 'i':
				arguments[0]  = parseOption( &flagI, optarg, optopt );
				break;
			case 'o':
				arguments[1] = parseOption( &flagO, optarg, optopt);
				break;
			case 't':
				arguments[2] = parseOption( &flagT, optarg, optopt);
				break;
			case 'x':
				arguments[3] = parseOption( &flagX, optarg, optopt);
				break;
			case '?':
				fprintf(stderr, "Unknown option %c\n", optopt);
				exit(2);
			case ':':
				fprintf(stderr, "Missing argument for option %c\n", optopt);
				exit(2);
		}
	}
	if( !flagI || !flagO || !flagT || !flagX )
	{
		fprintf(stderr, "USAGE: -i <string> -o <string> -t <string> -x <string>\nAll flags are required and can used only once\n");
		exit(2);
	}
}
