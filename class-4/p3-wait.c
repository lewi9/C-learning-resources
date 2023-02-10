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
		printf("Tworze potomka\n");
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

	// To dobry moment, aby skompilować program i sprawdzić jego działanie
	
	// No dobrze, czyli proces tworzy potomka, czeka na niego, tworzy kolejnego, czeka ... Ale czy moglibyśmy to jakoś usprawnić, aby najpierw tworzył potomków, a potem na nich czekał?
	// Zmodyfikujmy trochę pogram
	for( int i = 0; i<3; ++i )
	{
		printf("Tworze potomka\n");
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
		}
	}

	int potomki = 3;
	long long suma = 0;
	// Symulujmy, że proces rodzcielski coś robi w tle
	for( int k = 0;; ++k )
	{
		suma += k;
		for( int i = 0; i<3; ++i )
		{
			int wstatus;
			pid = wait(&wstatus);

			if( WIFEXITED(wstatus) )
			{
				printf("%d died and returned value %d\n", pid, WEXITSTATUS(wstatus));
				printf("Doliczyłem do %lld\n\n", suma);
				--potomki;
				break;
			}
		}
		if( !potomki ) break;
	}

	// Sprawdź działanie programu

	// Jednak mimo wszystko program dalej musi czekać i nie może w tym czasie nic wykonywać...
	// W takim razie skorzystjamy z bardziej wyrafinowanej funkcji waitpid()
	
	for( int i = 0; i<3; ++i )
	{
		printf("Tworze potomka\n");
		// Zapamiętajmy numery potomków
		switch( (pidArr[i] = fork()) )
		{
			case -1:
				perror("FORK");
				return 1;
			case 0:
				srand(time(NULL));
				struct timespec p = {20,0};
				if( nanosleep(&p, NULL) )
				{
					perror("CHILD");
					return 2;
				}
				// return random number from range [3;7]
				return rand()%5+3;		
		}
	}

	potomki = 3;
	suma = 0;
	// Dodajmy zewnętrznego fora, a by symulować, że program coś robi w międzyczasie
	for( int k = 0;; ++k )
	{
		suma += k;
		for( int i = 0; i<3; ++i )
		{
			int wstatus;
			// Podajemy numer potomka, na którego ma czekać, adres zmiennej do której ma zostać zapisany status oraz flag
			// Użyjemy tutaj flagi WNOHANG(nie zatrzymuj się, tylko sprawdź status i idź dalej)
			if( pidArr[i] == -1 ) continue;

			pid = waitpid(pidArr[i], &wstatus, WNOHANG);
			// Tym razem użyjemy pid == -1, to znaczy, że wait zwrócił -1, czyli pojawił się błąd lub NIE MA NA KOGO CZEKAĆ tzn. proces o danym numerze pid nie istnieje
			if( pid == -1 )
			{
				printf("%d died and returned value %d\n", pidArr[i], WEXITSTATUS(wstatus));
				printf("Doliczyłem do %lld\n\n", suma);
				potomki -= 1;
				// Zapamiętajmy, że potomek już nie pracuje
				pidArr[i] = -1;
			}
		}
		if( !potomki ) break;
	}
	// Jak widać, programy potomne działają dłużej - jest to związane z tym, że procesor przydziela im mniej czasu na swoje działanie - proces rodzicielski pracuje i to on zabiera zasoby procesora
	// Zwracana wartość potomków jest taka sama?
	// Pewnie dlatego, że inicjowane są w tym samym czasie, więc srand(time(NULL)) dla każdego jest takie same
	// Kończą działanie w tym samym czasie - zatem rand() zwróci taką samą wartość, to tylko generator liczb pseudolosywch oparty na pewnym ziarnie (seed) (tutaj time(NULL)) tego generatora, zatem skoro kończą działanie po 3 sekundach SWOJEGO czasu działania, to rand() opiera się na tym samym
	
	// DODAJ KOD: pobierz na początku programu czas z CLOCK_MONOTONIC, za każdym razem jak potomek kończy działanie wyświetl ile upłynęło sekund od początku programu
	// DODAJ KOD: na początku działania procesu potomengo pobierz czas na podstawie zegara CLOCK_PROCESS_CPUTIME_ID, a następnie przed zwróceniem wartości przez niego (zakończenie działania) wyświetl ile czasu upłynęło według tego zegara.
}
