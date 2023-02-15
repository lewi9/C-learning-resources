#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void parsing( int argc, char ** argv, int x, int e, int n );
int stringToInt( char * string ) 
int main( int argc, char ** argv )
{

}

void parsing( int argc, char ** argv, int x, int e, int n )
{
	int c;
	int flagX, flagE, flagN;
	flagX = flagE = flagN = 0;
	while( (c = getopt(argc, argv, "x:e:n:")) != -1 )
	{
		switch(c)
		{
			case x:


		}
	}
			

}
