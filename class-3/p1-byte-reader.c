//LANGUAGE = POLISH

// Od teraz kod będzie częściowo skrócony
// Nie będę poświęcał czasu na osbługę dokładną błędów funkcji z poprzednich tematów
// Skupię się na tłumaczeniu nowych zagadnień

// Zaprezenntuję kod do oczytywania plików stworzonych w poprzednim zadaniu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZEINFO 5
#define SIZEPATH 13

typedef struct Row{
	short number;
	char info[SIZEINFO];
	double value;
}Row;

void errorF( char * message ) { fprintf(stderr, "%s\n", message); exit(EXIT_FAILURE); }
void errorP( char * message ) { perror(message); exit(EXIT_FAILURE); }

void readPrint( int fd );

int main( int argc, char ** argv )
{
	// Obsługa parametru - podanej nazwy pliku
	char path[SIZEPATH] = "res.bin";
	if( argc == 2 ) ( strlen(argv[1]) < SIZEPATH ) ? strcpy(path, argv[1]) : errorF("Too long file name.");
	if( argc > 2 ) 
	{
		fprintf(stderr, "USAGE: <prog_name> <result_file_name>. Max file name: %d chars.\n", SIZEPATH-1);
		exit(EXIT_FAILURE);
	}
	// Otwarcie pliku
	int file = open(path, O_RDONLY);
	if( file == -1 ) errorP("OPEN");

	readPrint(file);
	close(file);
	return 0;
}

void readPrint( int fd )
{
	Row * ptr = calloc(1, sizeof(Row));
	if( !ptr ) errorP("CALLOC");
	// Czytaj tak długo, dopóki nie pojawi się błąð albo jest co wczytać.
	while( read(fd, ptr, sizeof(Row)) > 0 )
	{
		// Wydruk odczytanych danych
		printf("Number: %hd\tInfo: %.*s\tValue: %lf\n", ptr->number, SIZEINFO, ptr->info, ptr->value);
	}
	free(ptr);
}
