#ifndef MALLREGEX_H
#define MALLREGEX_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "regex.h"
#include "lfile.h"


/** Function Prototype

	struct _ta* regexpset(buffer* mbuf,char * c, struct _lfile* lfile);

Functionality: This function as part of the predicive parser recognizes
	the whole section of regular expressions and processes over the
	input as well as calling other functions to process their respective
	 parts.

Parameters: buffer* mbuf: an initialized buffer with input data
			char* c: the current input character
			_lfile* lfile: pointer to internal file data structures
				and other structures shared around the program.

Returns: Returns the full entire parse tree of all the regular expressions
	combined into one tree as a pointer to the tree structure struct _ta* 

Results: A tree structure type pointer _ta* is returned after being
	constructed from the input.

*/
/*struct _ta* regexpset(buffer* mbuf,char * c, struct _lfile* lfile);*/



#endif
