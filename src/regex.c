#include <string.h>
#include "Parser.h"
#include "lex_error.h"
/*
#include "baseset.h"
#include "chrset.h"
*/
RegularExpressionTreeNode* parseRegularExpression(RegularExpressionTreeArray ** ta,Io* programIO){
    struct _node * temp;
    temp = NULL;
    /*
	represents a regular expression on one line
	*/
    temp = parseFullExpression(&(*ta)->alphabet,programIO);

    if(programIO->own_lexer.current_char == '{'){
	   char sbuf[8000];
	   int scount =0;
	   int extrafrontbrackets = 0;
	   sbuf[0] = '{';
	   scount++;
	   while((programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer))!= EOF && programIO->own_lexer.current_char !='\0'){
		  if(programIO->own_lexer.current_char == '}'){
			 if(extrafrontbrackets != 0){
				extrafrontbrackets--;
				sbuf[scount] = programIO->own_lexer.current_char;
				scount++;
				/* programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer); */
			 }
			 else{
				sbuf[scount] = '}';
				scount++;
				sbuf[scount]='\0';
				(*ta)->action_array[(*ta)->used] = malloc(sizeof(char)*strlen(sbuf)+1);
				strncpy((*ta)->action_array[(*ta)->used],sbuf,strlen(sbuf)+1);
				programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
				while(is_ws(programIO->own_lexer.current_char) == 0)
				    programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
				if(programIO->own_lexer.current_char == '\n' || programIO->own_lexer.current_char == EOF || programIO->own_lexer.current_char == '\0')
				    return temp;
				else{
				    printf("error expecting a newline character but found %c\n",programIO->own_lexer.current_char);
				    exit(-1);
				}
			 }
		  }
		  else{
			 if(programIO->own_lexer.current_char == '{'){
				extrafrontbrackets++;
			 }
			 sbuf[scount] = programIO->own_lexer.current_char;
			 scount++;

		  }
	   }
	   return temp;
    }
    else{
	   lex_error(11);
	   printf("error expecting a '{' character but found %c\n",programIO->own_lexer.current_char);
	   exit(-1);
    }
}

RegularExpressionTreeNode* parseFullExpression(base_set ** set,Io* programIO){
/*
 represents a full expression on a line minus the newline character
 (expr) OR expr.op OR expr|expr OR [range] OR exprlist

 */
    return parseExpressionOR(set,programIO);
 }
