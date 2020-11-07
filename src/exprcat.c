/**
	This file includes the function exprlist() wich is the part of the parser that
recognizes a list of expressions, and construct a parse tree to represent the input
stream that it read as the so-called list. This parse tree is then returned with a
pointer to the structure.
	This function will call other parts of the parser to recognize and parse more
of the input stream.

*/

#include "Parser.h"
#include "retodfa.h"
#include "lex_error.h"
/*
#include "baseset.h"
#include "chrset.h"
*/
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

RegularExpressionTreeNode* parseExpressionList(Parser* parser){/* char_set** */
    /*
	1 or more expressions concatenated expr.expr.expr
	*/
    int firstrun;
	/* temporary node pointers to use to construct the parse tree while reading the input
	stream
	*/
    struct _node* temp;
    struct _node* temp2;
    struct _node* temp3;
    temp = temp2 = temp3 = NULL;
	/* At this point in the input stream, a few tokens tell us we aren't seeing
		an expression and we should skip the loops ahead */
    firstrun = 1;
    do{
		/* Call the expr() function to further process each individual expression
		*/
	   switch(firstrun){
		  case 1:
				temp = parseExpression(parser);
				firstrun = 0;
				break;
		  default:
				temp2 = parseExpression(parser);
				temp3 = create_node((char)CONCAT);
			 /* memory issues, then report and error and return NULL */
			 if(!temp3){
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

	   /* Call the firstpos and lastpos function to help create the sets for this
	   	new parse tree
	   */
	   }
	   firstpos(&temp);
	   lastpos(&temp);
	   /* either we're done or continue searching because we found whitespace
	   	in our regular expression where we shouldn't have
	   */
	   if(isWhitespace(&parser->lexer))
		  return temp;
	   
    }while(!isNewline(&parser->lexer) && parser->lexer.current_char != ')' && parser->lexer.current_char != '|' && parser->lexer.current_char != '\0' && !isEOF(&parser->lexer) );
		/* Call the expr() function to further process another expression or 
		more depending on the iteration of the while loop and concatenate it
		with any previously read and recognized expression from the input stream
		*/
    return temp;
}
