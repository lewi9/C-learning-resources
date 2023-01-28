#define _GNU_SOURCE

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

#define PIPES 3
#define BUFORSIZE 256

#define PARZYSTA (  ( n = rand() + 1 ) % 2 ) ? ( ( n = ((n+1) % 128) ) ? n : n+2 ) : ( (n = n % 128) ? n : n+2 )
#define NIEPARZYSTA ( ( n = rand() + 1) % 2 ) ? n % 128 : n+1 % 128


// W tym kodzie użyłem tylko prostą obsługę błędów.

void errorP( char * message, int code ) { perror(message); exit(code); }
void errorF( char * message, int code ) { fprintf(stderr, "%s\n", message); exit(code); }

pid_t Tpid[2];
int Tdsc[2];

void potomny( int ktory, int PTab[][2] );
int konstrukcja();
int potoki( int PTab[][2] );
void potokuj();
int parsing( int argc, char ** argv );
void potokR(int x);

void childHandler()
{
	kill(Tpid[0], SIGKILL);
	kill(Tpid[1], SIGKILL);
}

void sigHandler(int signal)
{
	kill(Tpid[0], SIGKILL);
	kill(Tpid[1], SIGKILL);
}

int main( int argc, char ** argv )
{
	srand(0);
	int err;	
	int x = parsing( argc, argv );
	if( (err = konstrukcja()) )
	{
		if( err % 2 )
			errorP("CHILDREN", err);
		errorF("Konstrukcja się nie powiodła.", err);
	}
	atexit(childHandler);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, sigHandler);
	signal(SIGKILL, sigHandler);
	potokR(x);
}

void potomny( int ktory, int PTab[][2] )
{
	switch(ktory)
	{
		case 0:
			if( close(PTab[0][0]) || close(PTab[0][1]) || close(PTab[1][1]) || close(PTab[2][0]) ) errorP("CLOSE", EXIT_FAILURE);
			if( dup2(PTab[1][0], 0) == -1 ) errorP("DUP2", EXIT_FAILURE);
			if( dup2(PTab[2][1], 1) == -1 ) errorP("DUP2", EXIT_FAILURE);
			potokuj();
		case 1:
			if( close(PTab[0][0]) || close(PTab[1][0]) || close(PTab[1][1]) || close(PTab[2][1]) ) errorP("CLOSE", EXIT_FAILURE);
			if( dup2(PTab[2][0], 0) == -1 ) errorP("DUP2", EXIT_FAILURE);
			if( dup2(PTab[0][1], 1) == -1 ) errorP("DUP2", EXIT_FAILURE);
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
	for( int i = 0; i<PIPES-1; ++i )
	{
		int pid = fork();
		switch(pid)
		{
			case -1: 
				return PARZYSTA;
			case 0:
				potomny( i, PTab );
			default:
				Tpid[i] = pid;
		}
	}
	Tdsc[0] = PTab[0][0];
	Tdsc[1] = PTab[1][1];

	struct timespec p = {0, 30000L};
	if( nanosleep(&p,NULL) ) return PARZYSTA;
	for( int i = 0; i<PIPES-1; ++i )
	{
		if( waitid( P_PID, Tpid[i], NULL, WEXITED|WNOHANG ) == -1 ) return NIEPARZYSTA;
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

void potokuj()
{
	char bufor[BUFORSIZE];
	struct pollfd pfd = {0, POLLIN, 0};
	while(1)
	{
		read(0,bufor,1);
		int ready;
		if( (ready = poll(&pfd, 1, -1)) == -1 ) errorP("POLL", EXIT_FAILURE);
		if(pfd.revents != 0)
		{
			if(pfd.revents & POLLIN)
			
			{
				if( read(0, bufor, 255) == -1 ) errorP("READ", EXIT_FAILURE);
				char * p = bufor;
				int i = 0;
				for( ; *p; ++p, ++i );
				struct timespec pd = {1, 250000000L};
				if( nanosleep( &pd, NULL) ) errorP("SLEEP", EXIT_FAILURE);
				struct timespec d;
				clock_gettime(CLOCK_REALTIME, &d);
				strftime(p, BUFORSIZE-i, "-czas %D %T ", gmtime(&d.tv_sec));
				write(1, bufor, BUFORSIZE);
			}
		}
	}
}

void potokR(int x)
{
	char bufor[BUFORSIZE];
	struct pollfd pfd = {Tdsc[0], POLLIN, 0};
	for(; x; --x)
	{
		int i = 0;
		struct timespec d;
		clock_gettime(CLOCK_REALTIME, &d);
		strftime(bufor, BUFORSIZE, "-czas %D %T ", gmtime(&d.tv_sec));
		write(Tdsc[1], bufor, BUFORSIZE);
		for( int i = 0; i<PIPES-1; ++i )
		{
			if( waitid( P_PID, Tpid[i], NULL, WEXITED|WNOHANG ) == -1 ) errorP("Potomkom się coś stało", EXIT_FAILURE);
		}
	
		struct timespec p = {0, 500000000L};
		int ready;
		while(1)
		{
			if( (ready = ppoll(&pfd, 1, &p, NULL)) == -1 )
				errorP("POLL", EXIT_FAILURE);

			if(pfd.revents != 0)
			{
				if(pfd.revents & POLLIN)
				{	
					if( read(Tdsc[0], bufor, BUFORSIZE) == -1 ) errorP("READ", EXIT_FAILURE);
					printf("%s\n", bufor);
					break;
				}
			}
			else
			{
				++i;
				printf("Niecierpliwię się\n");
				if( i >= 5)
				{
					i = 0;
					for( int i = 0; i<PIPES-1; ++i )
					{
						if( waitid( P_PID, Tpid[i], NULL, WEXITED|WNOHANG ) == -1 ) errorP("Potomkom się coś stało", EXIT_FAILURE);
					}
				}
			}
		}

	}
	exit(EXIT_SUCCESS);
	
}

int parsing( int argc, char ** argv )
{
	int x = 0;
	int c = 0;
	int flagX = 0;
	char * endptr = NULL;
	while( (c = getopt(argc, argv, "x:")) != -1 )
	{
		switch(c)
		{
			case 'x':
				flagX = 1;
				//errno = 0;
				x = strtol(optarg, &endptr, 10);
				if( *endptr || x < 1 )
					errorF("invalid argument -x", EXIT_FAILURE);
				break;
			default:
				errorF("Given argument is not proper", EXIT_FAILURE);
		}
	}
	if( !flagX ) errorF("Nie podano opcji -x", EXIT_FAILURE);
	return x;
}
