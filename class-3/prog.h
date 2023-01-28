#ifndef _C1_
#define _C1_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <time.h>

struct ColRow{
	int col;
	int row;
};

void function( char * patk, char * param1, int n);

#endif
