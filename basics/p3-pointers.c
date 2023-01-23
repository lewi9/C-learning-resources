// Let's do some operations with pointers
//

#include <stdio.h>
#include <stdlib.h>

// This function take as argument any pointer (void *), char - type of array element 
// and  int - size of array. The function will print array content.
void arrayPrint( void * ptr, char type, int size );

// This function take as argument any pointer to array, any pointer with value, 
// char - type of array element and int - size of array. The function will init array with that value.
void arrayInit( void * ptr, void * value, char type, int size );

// This function take as argument char - type of array element and int - size of array.
// The function will return a pointer to the array.
void * arrayCreate( char type, int size );

//This function free a memory allocated to pointer.
void freeHandler( int ev, void * ptr );

// 0. Analyze code. Note that we can iterrate in different ways.
// 1. Run the code 
// 2. Can you explain why the number are increasing and suddenly the value is under 0?
// 3. Modify the code that width of field, where number are printed, has width as wide as max number
// e.g. width: 3 because 100 is 3 digits wide.
//  1
// 10
//100  
// 4. Add code to handle some other types, e.g unsigned short, int, char.
int main( int argc, char * argv[] )
{
	short * array = arrayCreate( 's', 20 );
	short value = 1;
	// When you have variable like 'value' and you want give a pointer to that variable, use &
	arrayInit( array, &value, 's', 20 );
	arrayPrint( array, 's',  20 );
	exit(EXIT_SUCCESS);
}

void arrayPrint( void * ptr, char type, int size )
{
	switch( type )
	{
		case 's':
			short * ptr1 = (short *) ptr;
			short * ptr2 = (short *) ptr;
			for( ; ptr1-ptr2<size; ++ptr1 )
			{
				printf("%10hd\n", *ptr1);
			}
			break;
		default:
			fprintf(stderr, "arrayPrint problem - unknown type %c", type);
			exit(EXIT_FAILURE);

	}
}

void arrayInit( void * ptr, void * value, char type, int size ) 
{
	switch( type )
	{
		case 's':
			short * pointer = (short *)ptr;
			short val = *(short *)(value);
			for( int i = 0; i<size; ++i )
			{
				pointer[i] = val;
				//bit shift 0000 0001 << 1 == 0000 0010
				val = val<<1;
			}
			break;
		default:
			fprintf(stderr, "arrayInit problem - unknown type %c", type);
			exit(EXIT_FAILURE);

	}
}

void * arrayCreate( char type, int size )
{
	switch( type )
	{
		case 's':
			// If you read it in vim, you can put cursor on the name function and press esc and next shift+k to go to the manual page.
			short * ptr = calloc( size, sizeof(short)*20 );
			// Error handling
			if( !ptr ) 
			{
				perror("arrayCreate -> calloc");
				exit(EXIT_FAILURE);
			}
			// Register function to exit procedure.
			// It will be called when program exit.
			on_exit(freeHandler, ptr);
			return ptr;
		default:
			fprintf(stderr, "arrayCreate problem - unknown type %c", type);
			exit(EXIT_FAILURE);
	}
}

void freeHandler( int ev, void * ptr )
{
	free( ptr );
}
