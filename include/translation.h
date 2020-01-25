#ifndef MTRANSLAT_H
#define MTRANSLAT_H

#include "basebuffer.h"
#include "set.h"
#include "tree.h"
#include "lfile.h"
#include "allregex.h"
#include "lex_error.h"
#include "retodfa.h"

/** Function Prototype

	struct _ta* translations(buffer* mbuf, char*c, struct _lfile *);

Functionality: The function of the parser that recognizes and translates
	into an entire parse tree for the whole definitions part of the spec-
	ifications file. 

Parameters: buffer* mbuf: an initialiazed buffer
			char * c: the current input character
			struct _lfile*: a pointer to an _lfile structure used
				to hold various data structures shared around the program

Returns: A pointer to a tree structure that for one holds the entire parse
	tree of all the regular expressions, combined. 

Results: The input stream is parsed for definitions and code and the parse
	tree is constructed, the source code is read and held to be associated
	later, and it is finally returned in a struct _ta.
*/
struct _ta* translations(buffer* mbuf, char*c, struct _lfile *);



#endif
