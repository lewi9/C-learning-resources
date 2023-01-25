#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 150
#define SIZEC 50
#define SIZEINFO 5
#define SIZEPATH 13

typedef struct Row{
	short number;
	char info[SIZEINFO];
	double value;
}Row;

int parsing( int argc, char ** argv, short *l, short *u, char * path );
Row * allocate( int size );
void fillStructure( Row * ptr, int size );
void normNumber( short l, short u, Row * ptr, int size );
void writeToFile( Row * ptr, int size, char * path );

void errorP(char * str) { perror(str);  exit(EXIT_FAILURE);}
void errorF(char * str) { fprintf(stderr, "%s\n", str); exit(EXIT_FAILURE);}
void freeHandler(int ev, void * ptr) { free(ptr); }

int main( int argc, char ** argv )
{
	short l,u;
	char path[SIZEPATH] = "res.bin";
	int c = parsing( argc, argv, &l, &u, path );
	c = (c) ? SIZEC : SIZE;
	Row * ptr = allocate(c);
	fillStructure( ptr, c );
	normNumber( l, u, ptr, c );
	writeToFile( ptr, c, path );
	return 0;
}

void writeToFile( Row * ptr, int size, char * path )
{
	Row * p = ptr;
	int fd;
	if( !(fd = open(path, O_CREAT|O_TRUNC|O_WRONLY, 00666)) )
		errorP("open");
	for( int i = 0; i<size; ++i, ++p )
	{
		if( lseek(fd, sizeof(Row)*p->number, SEEK_SET) == -1 )
			errorP("lseek");
		if( write(fd, p, sizeof(Row)) == -1 )
			errorP("write");
	}
}

void normNumber( short l, short u, Row * ptr, int size )
{
	Row * p = ptr;
	for( int i = 0; i<size; ++i, ++p  )
	{
		p->number = ( p->number % u < 0 ) ? -(p->number % u) + l : p->number % u + l;
	}
}
void fillStructure( Row * ptr, int size )
{
	int fd;
	if( !(fd = open("/dev/urandom", O_RDONLY)) )
		errorP("open");
	if( read(fd, ptr, sizeof(ptr)*size) == -1 )
		errorP("read");
	close(fd);
}

Row * allocate(int size)
{
	Row * ptr = calloc(size, sizeof(Row));
	if( !ptr )
		errorP("calloc");
	on_exit(freeHandler, ptr);
	return ptr;
}

int parsing( int argc, char ** argv, short *l, short *u, char * path )
{
	int n;
	int flagL, flagU, flagPath, flagC;
	flagL = flagU = flagPath = flagC = 0;
	char * endptr;
	while( (n=getopt(argc, argv, "-:l:u:c")) != -1 )
	{
		switch(n)
		{
			case 'l':
				if( !flagL )
				{
					flagL = 1;
					char * lValue = optarg;
					errno = 0;
					*l = strtol(lValue, &endptr, 10);
					if( *endptr )
						errorF("invalid argument for -l");
					if( errno )
						errorP("-l");
					if( *l > SHRT_MAX || *l < 0 )
						errorF("value of -l argument is out of range");
					break;
				}
				errorF("You can only once use -l flag");
			case 'u':
				if( !flagU )
				{
					flagU = 1;
					char * uValue = optarg;
					errno = 0;
					*u = strtol(uValue, &endptr, 10);
					if( *endptr )
						errorF("invalid argument for -u");
					if( errno )
						errorP("-u");
					if( *u > SHRT_MAX || *u < 0 )
						errorF("value of -u argument is out of range");
					break;
				}
				errorF("You can only once use -u flag");

			case 'c':
				if( !flagC )
					flagC = 1;
				break;
			case 1:
				if( !flagPath )
				{
					flagPath = 1;
					if( strlen(optarg) > SIZEPATH ) 
					{
						fprintf(stderr, "path name is too long, can't be longer than %d chars\n", SIZEPATH-1);
						exit(EXIT_FAILURE);
					}
					strcpy(path, optarg);
					break;
				}
				errorF("You can't give more than one path to file");
			case '?':
				fprintf(stderr, "Unknown option %c\n", optopt);
				exit(EXIT_FAILURE);
			case ':':
				fprintf(stderr, "Missing argument for %c option\n", optopt);
				exit(EXIT_FAILURE);
			default:
				errorP("getopt");
		}
	}
	if( !flagL || !flagU )
		errorF("missing flag -l or -u");
	return flagC;
}
