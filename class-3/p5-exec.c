

// Jako ostatni temat tego modou zostanie omówiony exec, a właściwie rodzina funkcji exec
// Skupimy się na 4 funkcjach, resztę można doczytać w manualu
// Te 4 funkcje to
// execl()
// execlp()
// execv()
// execvp()

#include <unistd.h>

int main( int argc, char ** argv )
{
	// Proszę użytkownika o kolejne odkemetowanie kodu, skompilowanie programu i sprawdzenia działania
	// Następnie zakomentować odpalony kod i odkomentować kolejny
	
	// Jako pierwsza funkcja execl()
	// Generalnie wywołanie funkcji z rodziny exec wiąże się z tym, że bieżący proces zostanie zastąpiony nowym procesem wskazanym w wywołaniu funkcji
	// literka l i v oznacza w jaki sposób podawane są dodatkowe argumenty
	// literka p oznacza, że podajemy nazwę pliku, a jej brak, że zostanie podana pełna ścieżka do pliku
	
	// KOD:
	//execl("/bin/ls", "ls", "-l", "-A", NULL);

	// Powyższy fragment kodu jest odpowiedzialny za uruchomienie programu ls z parametrem -l oraz -A
	// Nie ma literki p - zatem podajemy ścieżkę programu
	// Pierwszy argument - ścieżka programu
	// Kolejny parametry:
	// Zgodnie z przyjętą konwencją pierwszym parametrem jest nazwa uruchomionego programu
	// Następnie po przecinku podajemy opcję -l
	// Następnie -A
	// Jako ostatni argument NALEŻY podać NULL
	// literka l oznacza w nazwie execl, że parametry będziemy podawać po przecinku

	// KOD:
	//execlp("ls", "ls", "-l", "-A", NULL);

	// Powyższy zapis zwróci taki sam rezultat jak wcześniej wywołanie
	// użycie literki p pozwala podać nam nazwę programu
	

	// KOD:
	/*
	char * arr[] = {"ls", "-l", "-A", NULL};
	execv("/bin/ls", arr);
	*/
	
	// Także powyższy zapis zwróci to samo
	// literka v - argumenty podajemy w postaci char **
	// inaczej mówiąc - w tablicy stringów
	// ostatni elemeny musi mieć wartość NULL
	// Więcej pisania, czy warto?
	// Z racji tego, że jest to tablica, możemy z łatwością edytować elementy wywołania funkcji, może być ich różna ilość
	// Unikniemy też błędu jakim mogłoby być podanie argumentu w innej postaci niż string
	
	// KOD:
	/*	
	char * arr[] = {"ls", "-l", "-A", NULL};
	execvp("ls", arr);
	*/
}	
