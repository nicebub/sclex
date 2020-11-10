#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
RegularExpressionTreeArray* parseRegularExpressionSet(Parser* parser){
	 struct _node* concatParent;
	 struct _node* hashChild;
	 struct _node* regex;
    int counter;
 	int firstrun;
    regex  = concatParent = hashChild = NULL;
    counter =0;
	/* create the initial parse tree structure */
    parser->parseTree = create_ta(512);
    if(!parser->parseTree){
	   lex_error(6);
	   return NULL;
    }
	/* Start parsing the input stream , if we have found
	end of file,its coming next, or we found a '%' symbolizing
	the end of the definition section, then don't start further
	parsing for regular expressions. Otherwise DO.
	*/
	firstrun = 1;
	do{
		concatParent = create_node((char)CONCAT);
		if(!concatParent){
			lex_error(9);
			return NULL;
		}
		hashChild = create_node('#');
		if(!hashChild){
			lex_error(8);
			return NULL;
		}
	   regex = parseRegularExpression(parser);
		if(!regex){
			switch(firstrun){
				case 1:
					lex_error(7);
					return NULL;
				default:
				  getNextChar(&parser->lexer);
 			  		continue;
			}
		}
		concatParent->left = regex;
		concatParent->right = hashChild;
		firstpos(&concatParent);
		lastpos(&concatParent);
      parser->parseTree->t[counter] = concatParent;
      parser->parseTree->used++;
      parser->parseTree->finalpos[parser->parseTree->num_re] =hashChild->uniq;
	   parser->parseTree->num_re++;
	   counter++;
		switch(firstrun){
			case 1:
		      parser->parseTree->atop = concatParent;
				firstrun = 0;
				break;
			case 0:
			default:
				hashChild = create_node((char)OR);
		   	if(!hashChild){
					lex_error(10);
			  	 return NULL;
				}
				hashChild->left = parser->parseTree->atop;
				hashChild->right = concatParent;
				firstpos(&hashChild);
		   	lastpos(&hashChild);
		   	parser->parseTree->atop = hashChild;
				break;
		}
/*	   pass_ws(&parser->lexer);*/
	 /*  if(parser->lexer.current_char == '%' || parser->lexer.current_char == EOF) return parser->parseTree;*/
	}while(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme);

	return parser->parseTree;
}
