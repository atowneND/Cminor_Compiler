/*
This is the standard library of functions for cminor, implemented in C.  
The print statement in C-minor expects there to exist a function
for each type that can be printed.
*/

#include <stdio.h>

void print_integer( int x );
void print_string( const char *s );
void print_boolean( int b );
void print_character( char c );
int integer_power( int x, int y );
