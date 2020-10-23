#include "Parser.h"
#include "Lexer.h"


void initTokenStack(LStack* stack){
	int counter;
	stack->top = stack->stack;
	for(counter=0;counter<PTS_STACK_SIZE;counter++)
		stack->stack[counter].lexeme = NULL;
	
}
void pushTokenStack(LStack* stack, LexerToken token){
	*stack->top = token;
	stack->top++;
}
LexerToken peekTokenStack(LStack* stack){
	return *(stack->top-1);
}
LexerToken popTokenStack(LStack* stack){
	LexerToken temp;
	stack->top--;
	temp = *stack->top;
	stack->top->lexeme=NULL;
	return temp;
}







void initParser(Parser* parser){
	initLexer(&parser->lexer);
	initTokenStack(&parser->tokenStack);
	parser->parseTree=NULL;
	parser->defs=NULL;
	parser->decs=NULL;
	parser->aux=NULL;
	parser->num_defs=0;
	
}

RegularExpressionTreeArray* parseInputFile(Parser* parser){
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
	if(!matchedNextToken(&parser->lexer,OPEN_STARTER).lexeme){
		/*fail*/
		return NULL;
	}
	parser->decs = parseDeclarations(parser);

	if(!matchedNextToken(&parser->lexer,CLOSE_STARTER).lexeme){
		/*fail*/
		return NULL;
	}
	parseDefinitions(parser);
	
	if(!matchedNextToken(&parser->lexer,SECTION_STARTER).lexeme){
		/* fail */
		return NULL;
	}
    parser->parseTree = parseTranslations(parser);

	if(matchedNextToken(&parser->lexer,SECTION_STARTER).lexeme){
		/* optional aux */
		aux(parser);
	}
	
	return NULL;
}
void pushBackLastToken(Lexer* lex){
	
}

char* aux(Parser* parser){
	return NULL;
}

