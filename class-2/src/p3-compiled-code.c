#include "p3-lseek.h"


void numberToRange( short lower, short upper, Row * ptr, int size )
{
	for( int i = 0; i<size; ++i ) 
	{
		ptr[i].number = ( ptr[i].number % upper >= 0 ) ? ptr[i].number % upper + lower : -(ptr[i].number % upper) + lower;
	}
}


void printRowPtr( Row * ptr, int size )
{
	Row * p = ptr;
	for( int i = 0; i<size; ++i, ++p )
	{
		// Different ways to get acces to structure fields.
		printf("Number :%hd\tInfo:%.4s\tValue:%lf\n", ptr[i].number, (*p).info, p->value);	
	}
}
