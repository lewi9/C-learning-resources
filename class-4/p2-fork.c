// Z posiadaną już wiedzą możemy przejść do tego co nas naprawdę interesuje - procesy potomne
// Proces potomny, w uproszczeniu, powstaje poprzez "rozdzielenie" procesu rodzicielskiego
// Wywołanie funkcji fork() spowoduje utworzenie nowego programu
// Będzie on posiadał obecny "stan wiedzy" rodzica
// To znaczy, że wszystkie zmienne oraz bufory będą miały taką wartość jak w procesie rodzicielskim
// Jednak zmiana wartości zmiennych w jednym procesie już po forku, nie zmieni tej wartości w drugim procesie

// Spróbujmy to przeanalizować na prostym przykładzie

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main( int argc, char ** argv )
{
	// Funkcja getpid() zwraca wartość pid - id procesu
	pid_t pid = getpid();
	printf("PID of parent process: %d\n", pid);
	printf("Something in buffer not printed + ");
	switch( fork() )
	{
		// obsługa błędu tzn. fork się nie powdiół
		case -1:
			perror("FORK");
			return 1;
		// proces potomny ( fork zwrócił wartość 0 )
		case 0:
			printf("Value od pid variable (Child process) %d\n", pid);
			struct timespec p = {2,0};
			if( nanosleep(&p, NULL) )
			{
				perror("CHILD");
				return 2;
			}
			pid = getpid();
			printf("PID of child process: %d\n", pid);
			struct timespec d = {4,0};
			if( nanosleep( &d, NULL ) )
			{
				perror("CHILD");
				return 2;
			}
			printf("I have just ended work\n");
			return 0;
		// Proces rodzicielski (fork zwrócił wartość pid procesu potomnego np. 5432);
		default:
			printf("Value of pid variable (Parent process) %d\n", pid);
			struct timespec r = {4,0};
			if( nanosleep(&r, NULL) )
			{
				perror("PARENT");
				return 2;
			}
			printf("Value of pid variable (child changed value of that var): %d\n", pid);
			return 0;
	}
}
