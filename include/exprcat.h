#ifndef MEXPRCAT_H
#define MEXPRCAT_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "expr.h"
#include "lfile.h"
#include "baseset.h"
#include "chrset.h"

/** Function Prototype

	struct _node* exprlist(struct _cset ** ta,buffer *mbuf, char* c,struct _lfile* lfile);

Functionality: This function is part of the parser that recognizes list of expressions
	and construts a parse tree to represent them, then returns a pointer to that tree.
	Along the way, this function calls other parts of the parser to recognize further input.

Parameters: struct _cset ** ta: Is a memory address to a pointer to a character set(the alphabet
	of the language found thus far)
			buffer *mbuf: A pointer to the current buffered input stream
			char* c: the current character on the input stream
			struct _lfile * lfile:  the program file structure contains various internal data
				strutures passes throughout portions of the program.

Returns: A Parse tree as an internal node structure from pointer to the root node node*

Results: A parse tree is constructed to represent a list of expressions that are read
	from the input stream and are returned as a properly constructed tree.


*/
struct _node* exprlist(base_set ** ta,buffer *mbuf, char* c,struct _lfile* lfile);/* char_set** */


#endif
