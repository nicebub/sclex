#ifndef MLEXER_H
#define MLEXER_H

#include <stdio.h>

/* Function Prototype
	
	void lex_error(int en);

Functionality: Print an error message depending on err number
	given as input

Parameter: an integer that represents which string in the 
	internal array represents the error to print

Results: Print an error message to stdout

*/
void lex_error(int en);



#endif