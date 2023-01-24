
// Let's look at printf, fprintf, sprintf;
//
// with printf you can write some data to terminal (stdin)
// with fprintf you also write some data to stdin, but also to stderr and any FILE * stream
// with sprintf you can write data char * buffer.
//
// The first one is just to simple terminal print
// The second you can use to write error messages or put data to file.
// The third you can use e.g to convert integer into string.

#include <stdio.h>

int main( int argc, char * argv[] )
{
	
	// %s - string
	// %d - integer
	// %lf - double
	// %c - char
	// %hd - short (half-integer)
	// %u - unsinged int
	// more in man

	printf("Hello word!\n");
	fprintf(stderr, "This is error...\n");

	// You can define digits number of printed variable with %.<number><format>
	printf("Two first digits of %u: %.2u\n", 123, 123);
	printf("Two first digits of %d: %.2d\n", 1, 1);
	

	// It's time to compile and see the effect.
	
	// When you pass 3 digits, when 2 are printed, you can see that all three are printed.
	// When you pass 1 digit, when 2 are printed, you can see the 0 at the beginning.
	// Chars are aligned to right.

	// If you want align text to left, use - insted of .
	
	printf("Two first digits of %u: %-4u\n", 123, 123);
	printf("Two first digits of %d: %-4d\n", 1, 1);

	// You can also give numbers of printed digits (chars) as argument by use *
	
	fprintf(stderr, "Error %-*d\n", 3, 21);
	fprintf(stderr, "Error %.*d\n", 8, 22);

	// If you don't use - or . the text will be aligned to right without zeros at the beginning.
	
	int a = 1231223112;
	printf("Number %d on field with 20 digits: %20d\n", a, a);

	// Let's see behavoiur for other formats than int and unsigned int
	
	char * string = "Lorem Ipsum";
	char * str = "Lorem";
	printf("String, %%5s <- \"%s\": %5s\n", string, string);
	printf("String, %%-5s <- \"%s\": %-5s\n", string, string);
	printf("String, %%.5s <- \"%s\": %.5s\n", string, string);
	printf("String, %%10s <- \"%s\": %10s\n", str, str);
	printf("String, %%-10s <- \"%s\": %-10s\n", str, str);
	printf("String, %%.10s <- \"%s\": %.10s\n", str, str);

	double d1 = 1.23;
	double d2 = 123.123;
	printf("double, %%5lf <- %lf: %5lf\n", d1, d1);
	printf("double, %%-5lf <- %lf: %-5lf\n", d1, d1);
	printf("double, %%.5lf <- %lf: %.5lf\n", d1, d1);
	printf("double, %%5lf <- %lf: %5lf\n", d2, d2);
	printf("double, %%-5lf <- %lf: %-5lf\n", d2, d2);
	printf("double, %%.5lf <- %lf: %.5lf\n", d2, d2);

	// We can cut string and change number of decimal digits.
	
	// Example of using sprintf - conversion int to string
	int i1 = 123456;
	char stringInt[7];
	sprintf(stringInt, "%d", i1);
	printf("%d converted to string: %s\n", i1, stringInt);
}
