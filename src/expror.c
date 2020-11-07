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
RegularExpressionTreeNode* parseExpressionOR(Parser* parser){/* char_set** */
    /*
	1 or more expressions OR'ed expr|expr|expr
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
		/* Call the exprlist() function to further process another expression list or 
		more depending on the iteration of the while loop and OR them
		with any previously read and recognized expression list from the input stream
		*/
	   switch(firstrun){
		  case 1:
			 temp = parseExpressionList(parser);
			 firstrun = 0;
			 break;
		  default:
			 temp2 = parseExpressionList(parser);
			 temp3 = create_node((char)OR);
			 if(!temp3){
				lex_error(10);
				return NULL;
			 }
			 temp3->left = temp;
			 temp3->right = temp2;
			 temp = temp3;
	   }

	   /* memory issues, then report and error and return NULL */
	   /* Call the firstpos and lastpos functions to generate the sets for the new
   		parse tree just constructed
   		*/
	   firstpos(&temp);
	   lastpos(&temp);
	   
	   /* If we find any unexpected whitespace then return the parse tree */
	   if(isWhitespace(&parser->lexer)){
		  pass_ws(&parser->lexer);
		  return temp;
	   }
	   /* we may still want to stay in the while loop as we've seen another '|' OR symbol */
	   if(parser->lexer.current_char == '|'){
		  getNextChar(&parser->lexer);
	   }
    }while(!isNewline(&parser->lexer) && parser->lexer.current_char != ')' && parser->lexer.current_char != '\0' && !isEOF(&parser->lexer) );
	/* return NULL or any parse tree we've constucted from recognized input */
    return temp;

}
