
#include "prog.h"

// Ten plik przeczytaj dopiero jak przerobisz wszystkie przykłady z tego rodziału
// Jest to łamigłówka

// Spraw aby program wyświetlił "Poprawnie zakończyłem działanie"
// W tym celu popraw istniejący kod
// Obecnie kod błędu podawany jest na strumień diagnostczny (numer deskryptora pliku :2)
// Przeanalizuj poniższy kod i korzystając z dotychczsowej wiedzy napraw go
// Minimalne naprawienie nie powinno zająć więcej niż 2 linijki kodu, bez obsługi błędów


// Poprawnie działający kod wyświetli
// "I'm doing my job"
// "Poprawnie zakończyłem działanie"

// Jeśli wyświetli się więcej niż jeden raz "I'm doing my job" to nie jest poprawne rozwiązanie

// Możliwy błąd który zobaczysz: USAGE: <sting> <int>
// Może on się pojawić mimo, że wywołując program podałeś odpowiednie parametry
// Możesz też zobaczyć inny błąd - zależy od twojego systemu linux
// np. BAD ADRESS
// Co jest jego przyczyną?
// Plik prog.c został poprawnie napisany
// Plik prog.o także jest poprawny

// Skompiluj ten kod wraz z plikiem "prog.o"
// uruchom go z dwoma parametrami pozycyjnymi -a i 3
// ./prog -a 3

void function( char * path, char * param1, int n )
{
	int fd0 = open("log.txt", O_CREAT|O_TRUNC|O_WRONLY|O_EXCL, 00666);
	if( fd0 == -1 )
	{
		fd0 = open("log.txt", O_WRONLY);
		if( fd0 == -1 )
		{	
			perror("OPEN");
			exit(EXIT_FAILURE);
		}
		if( dup2(fd0, 2) == -1 )
		{
			perror("DUP");
			exit(EXIT_FAILURE);
		}
	}
	close(fd0);
	if( n == 1 )
	{
		fprintf(stdout, "I'm doing my job\n");
		int i = 0;
		while(1)
		{
			srand(0);
			i += rand() % 5;
			if( i > 25 ) break;
		}
		for( ; i<40; ++i) 
		{
			++i;
			struct timespec p = {0, 2*i};
			struct timespec d;
			if( nanosleep(&p, &d) )
			{
				perror("NANOSLEEP");
				exit(EXIT_FAILURE);
			}
		}
		int fd = open("/dev/urandom", O_RDONLY);
		if( fd == -1 )
		{
			perror("OPEN");
			exit(EXIT_FAILURE);
		}

		int * a = calloc(n, sizeof(int));
		if( !a )
		{
			perror("CALLOC");
			exit(2);
		}
		if( read(fd, a, sizeof(int)*n) == -1 )
		{
			perror("READ");
			exit(3);
		}
		close(fd);
		if( execlp( path, path, param1, n-1, NULL ) == -1 )
		{
			perror("EXEC");
			exit(4);
		}
	}
	if( n == 0 )
	{
		printf("Poprawnie zakończyłem działanie\n");
		close(fd0);
		exit(EXIT_SUCCESS);
	}
	function(path, param1, n-1);
}
