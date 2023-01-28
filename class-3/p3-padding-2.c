// Aby lepiej zilustrować padding zajmijmy się poniższymi przykładami

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct A{
	short a;
	double b;
	short c;
	int d;
	char e[3];
}A;

typedef struct B{
	short a;
	short c;
	double b;
	int d;
	char e[3];
}B;

typedef struct C{
	short a;
	short c;
	int d;
	double b;
	char e[3];
}C;

void printMem( void * ptr, int size )
{
	char * p = (char *)ptr;
	for( int i = 0; i<size; i++ )
	{
		printf("%hhx ", p[i]);
	}
	printf("\n\n");
}

int main( int argc, char ** argv )
{
	int fd = open("/dev/urandom", O_RDONLY);
	if( fd == -1 )
	{
		perror(NULL);
		return 1;
	}
	A a;
	B b;
	C c;
	close(fd);

	if( read(fd, &a, sizeof(a)) == -1 || read(fd, &b, sizeof(b)) == -1 || read(fd, &c, sizeof(c)) == -1 )
	{
		perror(NULL);
		return 1;
	}
	printf("Size of A: %ld\n", sizeof(A));
	printf("Size of B: %ld\n", sizeof(B));
	printf("Size of C: %ld\n", sizeof(C));
	printf("\n");
	printf("===========================================\n");
	// Skompiluj program i zwróć uwagę na 3 pierwsze wiersze
	// Struktura a ma 32 bajtów rozmiaru, kiedy pozostałe mają 24
	// Wyświetlmy teraz ich zawartość tekstowo i bajtowo
	printf("%hd %lf %hd %d %.3s\n", a.a, a.b, a.c, a.d, a.e);
	printMem(&a, sizeof(a));
	printf("%hd %hd %lf %d %.3s\n", b.a, b.c, b.b, b.d, b.e);
       	printMem(&b, sizeof(b));
	printf("%hd %hd %d %lf %.3s\n", c.a, c.c, c.d, c.b, c.e);
	printMem(&c, sizeof(c));
	printf("===========================================\n");
	// Skompilu program i zwróć uwagę na następne 3 wydruki po 2 wiersze
	// Spróbujmy teraz poczyścić wiersze zgodnie z podaną w poprzednim przykładzie wiedzą
	// Pierwsza struktura to będzie 2 bajty i 2 bajty śmieci, 4 bajty śmieci, 8 bajtów, 2 bajty i 2 bajty śmieci, 4 bajty, 3 bajty i 1 bajt śmieci, 4 bajty śmiec = 32
	// Wyrównanie do wieloktroności 8, bo double ma rozmiar 8
	// Druga struktura: 2 bajty i 2 bajty, 4 bajty śmieci, 8 bajtów, 4 bajty, 3 bajty 1 bajt śmieć = 24
	// Trzecia struktura: 2 bajty i 2 bajty, 4 bajty, 8 bajtów, 3 bajty i 1 bajt śmieć, 4 bajty śmieci = 24  
	
	// Rzutujemy naszą strukturę na wskaźnik char *, i przesuwamy do miejsca, które chcemy wyczyścić
	// memset(<wskaźnik>, <jaką wartość wpisać>, <ile pól>)
	// Wpisujmey 0 na śmieciowe bajty
	memset((char *)&a+2, 0, 6); memset((char *)&a+18, 0, 2); memset((char *)&a+27, 0, 5);
	
	memset((char *)&b+4, 0, 4); memset((char *)&b+23, 0, 1);

	memset((char *)&c+19, 0, 5);

	// Zwróć uwagę na ostatnie 3 wydruki po 2 wiersze
	// Wniosek - projektuj struktury uważnie
	// W ramach ćwiczeń zmodyfikuj p2 tak, aby wyświetlał wiersze tekstowo oraz bajtowo
	// Następnie wyczyjść niepotrzebny bajt
	// Sprawdź czy na wyjściu są takie same dane po wyczysczeniu niepotrzebnego bajtu danych	
	printf("%hd %lf %hd %d %.3s\n", a.a, a.b, a.c, a.d, a.e);
	printMem(&a, sizeof(a));
	printf("%hd %hd %lf %d %.3s\n", b.a, b.c, b.b, b.d, b.e);
       	printMem(&b, sizeof(b));
	printf("%hd %hd %d %lf %.3s\n", c.a, c.c, c.d, c.b, c.e);
	printMem(&c, sizeof(c));
}
