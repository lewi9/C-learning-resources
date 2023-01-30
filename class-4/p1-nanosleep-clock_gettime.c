

// Nanosleep to całkiem prosta rzecz
// Będziemy używać go do spania zamiast sleep, ponieważ jest dokładniejszy 
// Ponadto zajmiemy się odmierzaniem czasu
//
// Nanosleep wymaga użycia struktury
// struct timespec {
// 	time_t tv_sec
// 	long tv_nsec
// 	};
//
// 	Wyróżnione zostanę cztery zegary:
// 	CLOCK_REALTIME - czas "rzeczywisty" 
// 	CLOCK_MONOTONIC - czas monotoniczny mierzony od pewnego punktui, przez system, oznacza to, że działa on niezależnie od procesu
// 	To znaczy, że nawet jeśli procesy będą przełączane, to on będzie stale rosnął
//	CLOCK_PROCESS_CPUTIME_ID - czas procesu 
//	CLOCK_THREAD_CPUTIME_ID - czas wątku
//

#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main( int argc, char ** argv )
{
	struct timespec t1_monotonic;
	struct timespec t2_monotonic;
	struct timespec t1_process;
	struct timespec t2_process;
	// 1 sekunda i 500 000 000 nanosekund czyli 1.5s
	// struct timespec delay;
	// delay.tv_sec = 1;
	// delay.tv_nsec = 500000000;
	// literka L od long
	struct timespec delay = {1, 500000000L};
	// pobierzmy czas
	clock_gettime(CLOCK_MONOTONIC, &t1_monotonic);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1_process);
	// Wartość zwracana tej funkcji to czas którego proces nie przespał na skutek sygnału, tutaj to zignurujemy
	sleep(1);
	clock_gettime(CLOCK_MONOTONIC, &t2_monotonic);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2_process);
	// Przyjmiemy pewne uproszczenie, bo np. 3.2s - 2.3s = 0.9s, a tutaj wskaże nam 1s -100ns
	printf("Proces spał %ld sekund i %ld nanosekund\n", t2_monotonic.tv_sec - t1_monotonic.tv_sec, t2_monotonic.tv_nsec - t1_monotonic.tv_nsec);
	printf("Według wskazania process cputime czas ten trwał %ld sekund i %ld nanosekund\n", t2_process.tv_sec - t1_process.tv_sec, t2_process.tv_nsec - t1_process.tv_nsec);
	clock_gettime(CLOCK_MONOTONIC, &t1_monotonic);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1_process);
	// drugi parametr to fu
	// funkcja zwraca -1 jeśli spanie się nie powiedzie albo zostanie przerwane
	// drugi parametr to adres struktury do której ma zostać zapisany czas nieprzespany, tutaj damy NULL, ponieważ nas to nie intereuje
	// Przydatne, jeżeli chcemy, aby proces spał 1.5s, spanie zostanie przerwane na skutek sygnału, proces coś wykona i chcemy oszacować ile jeszcze powinien spać
	if( nanosleep(&delay, NULL) )
	{
		perror(NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &t2_monotonic);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2_process);
	// Przyjmiemy pewne uproszczenie, bo np. 3.2s - 2.3s = 0.9s, a tutaj wskaże nam 1s -100ns
	printf("Proces spał %ld sekund i %ld nanosekund\n", t2_monotonic.tv_sec - t1_monotonic.tv_sec, t2_monotonic.tv_nsec - t1_monotonic.tv_nsec);
	printf("Według wskazania process cputime czas ten trwał %ld sekund i %ld nanosekund\n", t2_process.tv_sec - t1_process.tv_sec, t2_process.tv_nsec - t1_process.tv_nsec);
	// Wniosek z uruchomienia: nanosleep jest dokładniejszy, możemy spać x sekund po przecinku,  ponadto poinformuje nas o błędach, dlatego jego używajmy
	return 0;
	
}
