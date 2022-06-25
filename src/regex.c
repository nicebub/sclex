#include <string.h>
#include "Parser.h"
#include "lex_error.h"
#include "log.h"

/*
#include "baseset.h"
#include "chrset.h"
*/
RegularExpressionTreeNode* parseRegularExpression(Parser* parser){
    struct _node * temp;
    temp = NULL;
    /*
	represents a regular expression on one line
	*/
    temp = parseFullExpression(parser);

    if(matchToken(&parser->lexer,tokenForType(LCURLY)).lexeme){
	   char sbuf[8000];
	   int scount =0;
	   int extrafrontbrackets = 0;
	   sbuf[0] = '{';
	   scount++;
	   while(parser->lexer.current_char != EOF && parser->lexer.current_char !='\0'){
		  if(parser->lexer.current_char == '}'){
			 if(extrafrontbrackets != 0){
				extrafrontbrackets--;
				sbuf[scount] = parser->lexer.current_char;
				scount++;
				/* parser->lexer.current_char = getchar(&parser->lexer.inputBuffer); */
			 }
			 else{
				sbuf[scount] = '}';
				scount++;
				sbuf[scount]='\0';
				parser->parseTree->action_array[parser->parseTree->used] = malloc(sizeof(char)*strlen(sbuf)+1);
				strncpy(parser->parseTree->action_array[parser->parseTree->used],sbuf,strlen(sbuf)+1);
				getNextChar(&parser->lexer);
				while(is_ws(parser->lexer.current_char))
				    getNextChar(&parser->lexer);
				if(parser->lexer.current_char == '\n' || parser->lexer.current_char == EOF || parser->lexer.current_char == '\0')
				    return temp;
				else{
				    LOG_ERROR("error expecting a newline character but found %c\n",parser->lexer.current_char);
				    exit(-1);
				}
			 }
		  }
		  else{
			 if(parser->lexer.current_char == '{'){
				extrafrontbrackets++;
			 }
			 sbuf[scount] = parser->lexer.current_char;
			 scount++;

		  }
		  getNextChar(&parser->lexer);
	   }
	   return temp;
    }
    else{
	   lex_error(11);
	   LOG_ERROR("Either no translation given, or expected '{' but found %c\n",parser->lexer.current_char);
	   exit(-1);
    }
}

RegularExpressionTreeNode* parseFullExpression(Parser* parser){
/*
 represents a full expression on a line minus the newline character
 (expr) OR expr.op OR expr|expr OR [range] OR exprlist

 */
    return parseExpressionOR(parser);
 }
