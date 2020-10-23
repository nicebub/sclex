#ifndef MESCAP_H
#define MESCAP_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "baseset.h"
#include "chrset.h"
/*

	struct _node* escape_char(struct _cset **ta,buffer* mbuf,char* c);

Functionality: This runs the part of the parser that recognizes escape
	character sequences and constructs nodes for the parse tree to reprsent
	this. This representation is then returned, or an error happens and NULL
	is returned.

Parameters: a memory location of a pointer to a character set _cset **ta
			an already existing and initialized buffer pointer buffer* mbuf
			a character pointer char* c that is points to the current input
			character

Returns: returns a tree structure to be added to the parse tree that represents
	the esapce character sequence, or NULL if an error is detected.

Results: a node is created to represent the escape character and it is
	returned

*/
struct _node* escape_char(base_set **ta,Buffer* inputBuffer,char* c); /* char_set** */
#endif
