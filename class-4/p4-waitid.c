// Zajmiemy się teraz funkcją waitid()
// jest ona bardziej rozbudowana niż dwie poprzednie, co daje więcej możliwości
// pierwszy argument to idtype, gdzie specyfikujemy na kogo czekamy
// możemy na konkretny proces, na grupę procesów bądź na jakikolwiek
// drugi parametr to id, podajemy tam id procesu lub grupy, w przypadku gdy czekamy na jakikolwiek proces to to pole jest ignorowane
// trzeci parametr to wskaźnik do struktury typu siginfo_t
// czwarty parametr specyfikuje opcje czekania

// Przeanalizuj kod, następnie w ramach testów uruchom program, sprawdź jak się zachowa, gdy sam zakończy działanie, zostanie zabity oraz zostanie wstrzymany
// Przydatne komendy:
// tty - sprawdza numer terminalna
// watch ps -t <numer_terminalna> -o pid,ppid,stat,args
// kill -SIGKILL <pid>
// kill -SIGSTOP <pid>
//
// potrzebne będą trzy terminalne. Jeśli program kończy działanie zanim wyślesz sygnał, to wydłuż czas pracy potomka
// Możesz zmodyfikować program tak, aby printowany był pid potomka, to może ułatwić zadanie

#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char ** argv )
{
	srand(time(NULL));
	siginfo_t info;
	switch( fork() )
	{
		case -1:
			perror(NULL);
			return 1;
		case 0:
			struct timespec d = {10,0};
			if( nanosleep(&d, NULL) )
			{
				perror(NULL);
				return 2;
			}
			return (getpid()*rand()) % 20;
		default:
			for( int k = 0;; ++k )
			{
				waitid(P_ALL, 0, &info, WEXITED|WSTOPPED|WNOHANG);
				if( info.si_code == CLD_EXITED )
				{
					printf("Proces %d zakończył działanie ze statusem: %d\n", info.si_pid, info.si_status);
					printf("Doliczyłem do: %d\n", k);
					return 0;
				}
				else if ( info.si_code == CLD_KILLED )
				{
					printf("Proces %d został zabity sygnałem o kodzie %d\n", info.si_pid, info.si_status);
					printf("Doliczyłem do: %d\n", k);
					return 0;
				}
				else if ( info.si_code == CLD_STOPPED )
				{
					printf("Proces %d został zatrzymany\n", info.si_pid);
					printf("Doliczyłem do: %d\n", k);
					if( kill(info.si_pid, SIGCONT) == -1 )
					{
						perror(NULL);
						return 3;
					}
					printf("Proces %d został wznowiony\n", info.si_pid);
				}
			}
	}
}
