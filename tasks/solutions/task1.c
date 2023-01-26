#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <poll.h>
#include <pipe.h>

#define PIPES 3

#define PARZYSTA (  ( n = rand() + 1 ) % 2 ) ? (n+1) % 128 : n % 128 ;
#define NIEPARZYSTA ( ( n = rand() + 1) % 2 ) ? n % 128 : n+1 % 128;

void errorP( char * message, int ev ) { perror(message); exit(ev); }

pid_t Tpid[2];
int Tdsc[2];

void potomny( int ktory, int PTab[][2] );
int konstrukcja();
int potoki( int PTab[][2] );
void potokuj();
int parsing( int argc, char ** argv );

int main( int argc, char ** argv )
{
	srand(NULL);
	int err;
	if( err = konstrukcja )
	{
		if( err % 2 )
			errorP("CHILD", err);
		fprintf(stderr, "Konstrukcja się nie powiodła, liczba: %d", err);
		exit(EXIT_FAILURE);
	}
}

void potomny( int ktory, int PTab[][2] )
{
	switch(ktory)
	{
		case 0:
			close(PTab[0][0]);
			close(PTab[0][1]);
			close(PTab[1][1]);
			close(PTab[2][0]);
			dup2(PTab[1][0], 0);
			dup2(PTab[2][1], 1);
			potokuj();
		case 1:
			close(PTab[0][0]);
			close(PTab[1][0]);
			close(PTab[1][1]);
			close(PTab[2][1]);
			dup2(PTab[2][0], 0);
			dup2(PTab[0][1], 1);
			potokuj();
		default:
			exit(EXIT_FAILURE);
	}
}

int konstrukcja()
{	
	int PTab[PIPES][2];
	int n;
	if( potoki(PTab) ) return PARZYSTA;	
	for( int i = 0; i<PIPE-1; ++i )
	{
		int pid = fork();
		switch(pid)
		{
			case -1: 
				return PARZYSTA;
			case 0:
				potomny( i, PTab );
			default:
				TPid[i] = pid;
		}
	}
	Tdsc[0] = PTab[0][0];
	Tdsc[1] = PTab[1][1];

	struct timespec p = {0, 30000L};
	if( nanoslep(&p,NULL) ) return PARZYSTA;
	for( int i = 0; i<PIPE-1; ++i )
	{
		if( waitid( P_PID, Tpid[i], NULL, WNOHANG ) == -1 ) return NIEPARZYSTA
	}
	return 0;
}

int potoki( int PTab[][2] )
{
	for( int i = 0; i<PIPES; ++i )
	{
		if( pipe(PTab[i]) == -1) return 1;
	}
	return 0;	
}

void potokuj();

int parsing( int argc, char ** argv );
