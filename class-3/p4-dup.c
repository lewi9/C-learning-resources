
// Teraz pora na funkcję dup(), a dokładniej dup2()

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void errorP( char * message ){ errorP(message); exit(EXIT_FAILURE); }

int main( int argc, char * argv[] )
{
	// Najpierw zajmijmy się zwykłym dup()
	
	// Tworzymy sobie plik
	
	int fd1 = open("dup.txt", O_CREAT|O_TRUNC|O_WRONLY, 00666);
	if( fd1 == -1 ) errorP("OPEN");

	// Używamy dup(). 
	// Co robi dup?
	// Tworzy kopię deskryptora podanego jako argument i używa najmniejszej wolnej liczby, aby mu ją przypisać
	
	int fd2;
	if ( (fd2 = dup(fd1)) == -1 ) errorP("DUP");

	// wartość deskryptorów
	printf("%d %d\n", fd1, fd2);

	// czy są sobie równe
	printf("%d\n", fd1 == fd2);

	char * string1 = "Piszę za pomocą skopiowanego deskryptora\n";
	if( write(fd2, string1, strlen(string1)) == -1 ) errorP("WRITE1");
	
	char * string2 = "Piszę za pomocą pierwotnego deskryptora\n";
	if( write(fd1, string2, strlen(string2)) == -1 ) errorP("WRITE2");
	
	close(fd2);

	// O wiele ciekawszy jest dup2()
	// Generalnie zwraca on także kopię deskryptora
	// Różnica jest taka, że zamiast użyć najmniejszej wolnej liczby, używa podanej liczby jako drogi argument
	// Domyślnie: 0 - strumień wejścia, 1 - strumień wyjścia, 2 - strumień diagnostyczny
	// Daje to nam sporo możliwości, możemy np. utworzyć plik log.txt i tak zapisywać wszystkie błędy zamiast zwracać je do konsoli
	// Możemy także sprawić, aby printf zapisywał do pliku zamiast do konsoli
	
	// tutaj nie musimy zapisać do pliku nowego fd, ponieważ printf domyślnie używa fd o numerze 1
	if ( dup2(fd1, 1) == -1 ) errorP("DUP2");

	// W wyniku powyższego działania, ta wiadomość nie zostanie wyświetlona w konsoli tylko zapisana do pliku
	printf("Piszę za pomocą printf\n");

	close(fd1);
}
