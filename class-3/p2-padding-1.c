//LANGUAGE = POLISH

// Zmieńmy teraz trochę program - zamiast wyświetlać tekstwo poszczególne wartości pól wczytanej struktury wyświetlmy je bajt po bajcie

// Skompiluj program i zobacz jak działa na pliku res.bin

// Policzmy ile bajtów powinno się wyśwtielić: rozmiar shorta (2 bajty) + rozmiar char[SIZEINFO] (5 bajtów) + rozmiar double (8 bajtów) = 15 bajtów 
// Ile bajtów jest na ekranie? 16
//
// Skąd ta różnica jednego bajta?
// To zjawisko nazywa się padding - wyrównanie pamięci
// W przypadku poniższe struktury zapis bajtów będzie wyglądał następująco SSCC CCCX DDDD DDDD
// Ten X to właśnie bajt, który powstał dodadtkowo na skutek wyrównania pamięci
// Nie znajduje się w nim istotna informacja z punktu widzenia naszych danych
// Został doklejony, aby nastąpiło wyrównanie
// Dlaczego zatem nie SSCC CCCD DDDD DDDX ?
// Kompilator kieruje się następującymi zasadami
// 1-bajtowe obiektry trafiają do jakichkolwiek adresów (tablica typu char to kilka jednobajtowych obiektów)
// 2-bajtowe obiekty trafiają do adresów, które są wielokrotnością dwójki
// Oznacza to, że jeślibyśmy w strukturze mieli short, short, int to zostaną one zapisane jako SSSS IIII
// jeślibyśmy mieli short, int, short, to wtedy taki zapis będzie wyglądać SSXX IIII SSXX
// 4-bajtowe obiekty trafiają do adresów, które są wielokrotnością czwórek
// 8-bajtowe obiekty trafiają do adresów, które są wieloktrotnością ósemek

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
		char * p = (char *)ptr;
		char * q = (char *)ptr;
		for(; p-q<sizeof(Row); ++p)
		{
			// hhx - format odpowiedzialny za wyświetlanie jednego bajta
			printf("%hhx ", *p);
		}
		printf("\n");
	}
	free(ptr);
}
