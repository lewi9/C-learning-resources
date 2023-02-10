// Sometimes you want to return more than one value from functio
// Sure, you can return an array with values
// When you want return values of different types, you can cast all to string and cast is back outside of function
// There is better way - reference
// You can use adress of variable as argument
//

#include <stdio.h>

void func( int * x, int * y, char * a )
{
	// Note that x,y and a are now pointers, because you put adress as argument
	*x = 3;
	*y = 1;
	*a = 'c';
}

int main( int argc, char ** argv )
{
	int x = 0;
	int y = 0;
	char a = 'a';
	printf("%d %d %c\n", x, y, a);
	func( &x, &y, &a );
	printf("%d %d %c\n", x, y, a);
}

