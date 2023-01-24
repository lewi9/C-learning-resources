
#ifndef _P3LSEEK_H_
#define _P3LSEEK_H_

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct Row{
	short number;
	char info[5];
	double value;
}Row;

// Print rows from stored in row ptr
void printRowPtr( Row * ptr, int size );

// Change number field to value of range [lower, upper+lower)
void numberToRange( short lower, short upper, Row * ptr, int size );

#endif

