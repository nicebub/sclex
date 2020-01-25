#ifndef MCHARSET_H
#define MCHARSET_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "escape.h"

/* Function Prototype

	struct _node* charset(struct _cset ** ta,buffer* mbuf, char*c);

Functionality: Charset is the part of the predictive parser that
	recognizes and puts into the parse tree character sets [a-z]|[tbt@m;]

Parameters: a memory address of a character set pointer _cset** ta
			an initialized buffer pointer buffer* mbuf
			the current input character pointer char* c

Returns: returns a tree structure of nodes to be added to the parse
	tree

Results: a parse tree of nodes is constructed to represent the character
	classes/sets found in the input stream

*/
struct _node* charset(struct _cset ** ta,buffer* mbuf, char*c);

#endif
