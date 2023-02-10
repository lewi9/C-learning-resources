// Czy proces rodzicielski może jakoś uzyskać informacje od potomka?
// Tak. Może np. badać z jakim statusem zakończył on swoje działanie
// Do tego służy funkcja wait() oraz waitpid() i waitid()
// Na razie zajmijmy się dwoma pierwszymi

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>

int main( int argc, char ** argv )
{
	int pid = getpid();
	printf("I'm process %d\n", pid);

	int pidArr[3];

	for( int i = 0; i<3; ++i )
	{
		switch( fork() )
		{
			case -1:
				perror("FORK");
				return 1;
			case 0:
				srand(time(NULL));
				struct timespec p = {3,0};
				if( nanosleep(&p, NULL) )
				{
					perror("CHILD");
					return 2;
				}
				// return random number from range [3;7]
				return rand()%5+3;
			default:
				// do tej zmiennej przechwycimy status, z jakim potomek zakończył działanie (return value)
				int wstatus;
				pid = wait(&wstatus);
				// Sprawdzamy czy potomek zakończył działanie (mógł np. zostać zabity przez sygnał, wtedy wartość tego wyrażenia będzie równe 0
				if( WIFEXITED(wstatus) )
				{
					// To jest niepoprawne, ponieważ aby odczytać status należy użyć odpowiedniego makra...
					printf("%d died and returned value %d\n", pid, wstatus);
					// To jest poprawne
					printf("%d died and returned value %d\n\n", pid, WEXITSTATUS(wstatus));
				}			
		}
	}
}
