/**
	This file includes the function exprlist() wich is the part of the parser that
recognizes a list of expressions, and construct a parse tree to represent the input
stream that it read as the so-called list. This parse tree is then returned with a
pointer to the structure.
	This function will call other parts of the parser to recognize and parse more
of the input stream.

*/

#include "../include/exprcat.h"
#include "baseset.h"
#include "chrset.h"

/**  

	struct _node* exprlist(struct _cset ** ta,Buffer * mbuf, char* c, struct _lfile* lfile)

Functionality: This function is part of the parser that recognizes list of expressions
	and construts a parse tree to represent them, then returns a pointer to that tree.
	Along the way, this function calls other parts of the parser to recognize further input.

Parameters: struct _cset ** ta: Is a memory address to a pointer to a character set(the alphabet
	of the language found thus far)
			Buffer *mbuf: A pointer to the current Buffered input stream
			char* c: the current character on the input stream
			struct _lfile * lfile:  the program file structure contains various internal data
				strutures passes throughout portions of the program.

Returns: A Parse tree as an internal node structure from pointer to the root node node*

Results: A parse tree is constructed to represent a list of expressions that are read
	from the input stream and are returned as a properly constructed tree.


*/

struct _node* exprlist(/*char** */base_set ** ta,Buffer * mbuf, char* c, struct _lfile* lfile){
    /*
	1 or more expressions concatenated expr.expr.expr
	*/
	
	/* temporary node pointers to use to construct the parse tree while reading the input
	stream
	*/
    struct _node* temp;
    struct _node* temp2;
    struct _node* temp3;
    temp = temp2 = temp3 = NULL;
	/* At this point in the input stream, a few tokens tell us we aren't seeing
		an expression and we should skip the loops ahead */
    if(*c != '\n' && *c != ')' && *c != '|' && *c != '\0' && *c != EOF ){
		/* Call the expr() function to further process each individual expression
		*/
	   temp = expr(ta,mbuf,c,lfile);
	   /* Call the firstpos and lastpos function to help create the sets for this
	   	new parse tree
	   */
	   pos(&temp,1);
	   pos(&temp,0);
	   /* either we're done or continue searching because we found whitespace
	   	in our regular expression where we shouldn't have
	   */
	   if(is_ws(*c) == 0)
		  return temp;
    }
	/* Just like before, att this point in the input stream, a few tokens tell
	us we aren't seeing an expression and we should skip the loops ahead 
	*/
    while(*c != '\n' && *c != ')' && *c != '|' && *c != '\0' && *c != EOF ){
		/* Call the expr() function to further process another expression or 
		more depending on the iteration of the while loop and concatenate it
		with any previously read and recognized expression from the input stream
		*/
	   temp2 = expr(ta,mbuf,c,lfile);
	   temp3 = create_node((char)CONCAT);
	   /* memory issues, then report and error and return NULL */
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }

	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
	   temp3 = NULL;
	   /* Call the firstpos and lastpos functions to generate the sets for the new
	   	parse tree just constructed
	   */
	   pos(&temp,1);
	   pos(&temp,0);
	   /* If we find any unexpected whitespace then return the parse tree */
	   if(is_ws(*c) == 0)
		 return temp;
    }
	/* Either we've skipped all the loops above and we are returning NULL or
		we have gone through the 1st loop and we are returning a parse tree
		of one expression, or we have gone through all the loops and we are
		returning a parse tree to a list of expressions, concatenated together
	*/
    return temp;
}
