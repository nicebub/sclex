#ifndef MEXPROR_H
#define MEXPROR_H

#include "basebuffer.h"
#include "tree.h"
#include "retodfa.h"
#include "lex_error.h"
#include "exprcat.h"
#include "lfile.h"
#include "baseset.h"
#include "chrset.h"
/** Function Prototype

	struct _node* expror(struct _cset ** ta,buffer *mbuf, char* c, struct _lfile* lfile);

Functionality: This function is part of the parser that recognizes list of expressions, followed
	by an optional '|' OR symbol followed by optional more lists of expressions. Only 1 will be
	recognized on the input stream, and  construts a parse tree  to represent them, then returns a
	pointer to that tree. Along the way, this function calls other parts of the parser to recognize
	further input.

Parameters: struct _cset ** ta: Is a memory address to a pointer to a character set(the alphabet
	of the language found thus far)
			buffer *mbuf: A pointer to the current buffered input stream
			char* c: the current character on the input stream
			struct _lfile * lfile:  the program file structure contains various internal data
				strutures passes throughout portions of the program.

Returns: A Parse tree as an internal node structure from pointer to the root node node*

Results: A parse tree is constructed to represent a list of expressions that are read
	from the input stream and are returned as a properly constructed tree. These expressions
	are all seperated by an '|' operator the OR, and only 1 has to be recognized on the input
	stream during lexing.


*/
struct _node* expror(base_set ** ta,buffer *mbuf, char* c, struct _lfile* lfile);/* char_set** */

#endif
