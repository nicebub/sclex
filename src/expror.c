/**
	This file includes the function expror() wich is the part of the parser that
recognizes a list of expressions, and construct a parse tree to represent the input
stream that it read as the so-called list. This parse tree is then returned with a
pointer to the structure. The list is one expression optionally seperated by a
'|' token, OR. Only one of these epxressions will later on be recognized on the
input stream during lexing.
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
RegularExpressionTreeNode* parseExpressionOR(base_set ** set,Parser* parser){/* char_set** */
    /*
	1 or more expressions OR'ed expr|expr|expr
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
    if(parser->lexer.current_char != '\n' && parser->lexer.current_char != ')' && parser->lexer.current_char != '\0' && parser->lexer.current_char != EOF ){
		/* Call the exprlist() function to further process each list of expressions
			found
		*/
	   temp = parseExpressionList(set,parser);
	   /* Call the firstpos and lastpos function to help create the sets for this
   		new parse tree
   		*/
	   pos(&temp,1);
	   pos(&temp,0);
	   /* either we're done or continue searching because we found whitespace
   		in our regular expression where we shouldn't have
   		*/
	   if(is_ws(parser->lexer.current_char)==0){
		  while(is_ws(parser->lexer.current_char)==0)
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  return temp;
	   }
    }
	/* have we vound a '|' symbol OR, and more expression lists?? */
    if(parser->lexer.current_char == '|'){
	   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
    }
	
	/* Just like before, att this point in the input stream, a few tokens tell
	us we aren't seeing an expression list and we should skip the loops ahead 
	*/
    while(parser->lexer.current_char != '\n' && parser->lexer.current_char != ')' && parser->lexer.current_char != '\0' && parser->lexer.current_char != EOF ){
		/* Call the exprlist() function to further process another expression list or 
		more depending on the iteration of the while loop and OR them
		with any previously read and recognized expression list from the input stream
		*/
	   temp2 = parseExpressionList(set,parser);
	   temp3 = create_node((char)OR);

	   /* memory issues, then report and error and return NULL */
	   if(temp3 == NULL){
		  lex_error(10);
		  return NULL;
	   }
	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
	   /* Call the firstpos and lastpos functions to generate the sets for the new
   		parse tree just constructed
   		*/
	   pos(&temp,1);
	   pos(&temp,0);
	   
	   /* If we find any unexpected whitespace then return the parse tree */
	   if(is_ws(parser->lexer.current_char)==0){
		  while(is_ws(parser->lexer.current_char)==0)
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  return temp;
	   }
	   /* we may still want to stay in the while loop as we've seen another '|' OR symbol */
	   if(parser->lexer.current_char == '|'){
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	   }
    }
	/* return NULL or any parse tree we've constucted from recognized input */
    return temp;

}
