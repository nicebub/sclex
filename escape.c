/**
 This files has code for the parser to recognize and deal with escape
	character sequences by constructing nodes of a parse tree and 
	returning them as a representation for the input.
Examples of escqpe character sequences:
	\t
	\n
	\r
	\0

*/
#include "escape.h"

/**

	struct _node* escape_char(struct _cset **ta,buffer* mbuf,char* c)

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
struct _node* escape_char(struct _cset **ta,buffer* mbuf,char* c){
	/* temporary node help create new nodes and add them to a tree */
    struct _node* temp;

    temp = NULL;

    *c = getchar(mbuf);

	/* create the node and return it,
		switch statement for later use
	*/
    switch(*c){
	   case 'n':
		  temp = create_node('\n');
		  return temp;
	   case 't':
		  temp = create_node('\t');
		  return temp;
	   case '\\':
	   case '\'':
	   case '"':
	   case '%':
	   case '*':
	   case '+':
	   case '?':
	   case '{':
	   case '}':
	   case '[':
	   case ']':
	   case '(':
	   case ')':
	   case '/':
	   case '.':
		  temp = create_node(*c);
		  return temp;
		  /* If all else fails, then report an error and return NULL */
	   default:
		  printf("doesn't support that kind of escape character\n");
		  return NULL;
    }
    
}
