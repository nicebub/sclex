/**
 This file includes the code to the parser that takes all the different 
parse trees of each individual regular expression definition and 
combines them into one tree. This is returned at a tree type structure
by pointer.
  The regular expression set recognizer (this recognizer), calls the 
regexp()mfunction, which continues to parse individual regular expressions.

*/
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
/**  

	struct _ta* regexpset(buffer* parser->lexer.inputBuffer,char * c, struct _lfile* lfile)

Functionality: This function as part of the predicive parser recognizes
	the whole section of regular expressions and processes over the
	input as well as calling other functions to process their respective
	 parts.

Parameters: buffer* parser->lexer.inputBuffer: an initialized buffer with input data
			char* c: the current input character
			_lfile* lfile: pointer to internal file data structures
				and other structures shared around the program.

Returns: Returns the full entire parse tree of all the regular expressions
	combined into one tree as a pointer to the tree structure struct _ta* 

Results: A tree structure type pointer _ta* is returned after being
	constructed from the input.

*/

RegularExpressionTreeArray* parseRegularExpressionSet(Parser* parser){
	/* temporary node pointers used to construct new nodes of the parse tree
	during parsing */
    struct _node * temp;
    struct _node * temp2;
    struct _node * temp3;
    struct _node * temp4;
	/* an initial pointer used to point to a tree type structure to house
		the whole parse tree of the specification file */
    struct _ta * ta;
	/* integer counter for the number of regular expression definitions found */
    int ct;
	
    ta = NULL;
    temp = temp2 = temp3 = temp4 = NULL;
    ct =0;
	/* create the initial parse tree structure */
    ta = create_ta(512);
	/* if for some reason a memory error or other reason the tree
		can't be created, an error is printed an NULL is returned */
    if(ta == NULL){
	   lex_error(6);
	   return NULL;
    }
	/* Start parsing the input stream , if we have found
	end of file,its coming next, or we found a '%' symbolizing
	the end of the definition section, then don't start further
	parsing for regular expressions. Otherwise DO.
	*/
    if(parser->lexer.current_char != EOF  && parser->lexer.current_char != '%' && (parser->lexer.current_char = getchar(&parser->lexer.inputBuffer))!= EOF){
		/* call regexp to further parse the input stream as a regular
		expression, and store the parse tree returned in temp */
	   temp = parseRegularExpression(&ta,parser);
	   /*  if NULL we have a problem, so print an error and keep
	   	returning NULL */
	   if(temp == NULL){
		  lex_error(7);
		  return NULL;
	   }
	   /* end of REGEXP character attached for processing */
	   temp2 = create_node('#');
	   /* memory error ?? print error and return NULL */
	   if(temp2 == NULL){
		  lex_error(8);
		  return NULL;
	   }
	   /* CONCAT token node created to construct parse tree with '#' */
	   temp3 = create_node((char)CONCAT);
	   /* memory error ?? print error and return NULL */
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }
	   
	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
    }
	/* calling pos calls the firstpos and lastpos functions on the current
	parse tree found which would be only 1 initial regular expression 
	definition */
    pos(&temp,1);
    pos(&temp,0);
	
	/* the tree has a shortcut array to find regular expressions later
		for faster processing */
    ta->t[ct] = temp;
	/* used: keeps track of regular expression memory space */
    ta->used++;
	/* atop is the top of the current parse tree */
    ta->atop = temp;
	/* final position sets initial construction */
    ta->finalpos[ta->num_re] =temp2->uniq;
	/* sets number of regular expressions found thus far */
    ta->num_re++;
    ct++;
    /* skip certain whitespace tokens */
    while((is_ws(parser->lexer.current_char) ==0) || parser->lexer.current_char == '\n')
	   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	/* end of definiton section if finding '%' token now so exit with
		current parse tree returned */
    if(parser->lexer.current_char == '%')
	  return ta;
	/* otherwise if we haven't found the end of the file or the end of
	the defnition section, loop around parsing each regular expression
	defnition 
		Inside the loop repeats the process above */
    while(parser->lexer.current_char != EOF && parser->lexer.current_char != '%'){

	   temp2 = parseRegularExpression(&ta,parser);
	   if(temp2 == NULL){
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  continue;
	   }
	   temp3 = create_node((char)CONCAT);
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }
	   temp4 = create_node('#');
	   if(temp4 == NULL){
		  lex_error(8);
		  return NULL;
	   }

	   temp3->left = temp2;
	   temp3->right = temp4;
	   pos(&temp3,1);
	   pos(&temp3,0);
	   ta->t[ct] = temp3;
	   ta->used++;
	   ta->finalpos[ta->num_re] = temp4->uniq;
	   ct++;
	   ta->num_re++;
	   /* Now add the newly parsed regular expression's parse
	   	tree and add it to the other regular expressions found
	   	in one large parse tree, all OR'd together
	   */
	   temp4 = create_node((char)OR);
	   /* error if no memory, print error, and return NULL */
	   if(temp4 == NULL){
		  lex_error(10);
		  return NULL;
	   }
	   
	   temp4->left = temp;
	   temp4->right = temp3;
	   /* firstpos and lastpos sets are constructed or changed if needed */
	   pos(&temp4,1);
	   pos(&temp4,0);
	   /* reset the head of the tree */
	   temp = temp4;
	   ta->atop = temp;
	   /* Get rid of any whitespace characters left in the input stream */
	   while((is_ws(parser->lexer.current_char) ==0) || parser->lexer.current_char == '\n')
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	   /* if we found the end of the definitions symbol '%' then return
	   	a pointer to the current parse tree structure */
	   if(parser->lexer.current_char == '%'){
		  return ta;
	   }
    }
	/* We've found some sort of way around or out of the definitions loop so return
		a pointer to the current parse tree structure */
    return ta;
}
