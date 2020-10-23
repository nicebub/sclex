#include "Parser.h"
#include "Lexer.h"
#include "lex_error.h"

#ifdef __STRICT_ANSI__
#define inline
#endif


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
	temp.lexeme = NULL;
	if(stack->top != stack->stack){
		stack->top--;
		temp = *stack->top;
		stack->top->lexeme=NULL;
	}
	return temp;
}



inline void initTokenStream(TokenStream* stream){
	initTokenStack(&stream->stack);
}

LexerToken matchToken(Parser* parser,LexerToken token){
	LexerToken temp;
	temp = peekTokenStack(&parser->tokens.stack);
	if(!temp.lexeme)
		return matchedNextToken(&parser->lexer,token);

	if(token.id == temp.id)
		return popTokenStack(&parser->tokens.stack);
	
	return defaultTokens[0];
}


void initParser(Parser* parser){
	initLexer(&parser->lexer);
	initTokenStream(&parser->tokens);
	parser->parseTree=NULL;
	parser->defs=NULL;
	parser->decs=NULL;
	parser->aux=NULL;
	parser->num_defs=0;
	
}
inline void initParserWithFilename(Parser* parser,char* arg){
	initParser(parser);
	parser->lexer.inputBuffer = *buffer_from_filename(arg);/* initialize buffer from filename given */
    getNextChar(&parser->lexer);
}

RegularExpressionTreeArray* parseInputFile(Parser* parser){
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
/*	if(!matchedNextToken(&parser->lexer,OPEN_STARTER).lexeme){*/
	if(!matchToken(&parser,*OPEN_STARTER).lexeme){
		/*fail*/
		lex_error(SCERR_DECL_UNDECLARED);
		return NULL;
	}
	parser->decs = parseDeclarations(parser);

	if(!matchToken(&parser,*CLOSE_STARTER).lexeme){
		/*fail*/
		lex_error(SCERR_MUST_USE_SEPR);
		return NULL;
	}
	parseDefinitions(parser);
	
	if(!matchToken(&parser,*SECTION_STARTER).lexeme){
		/* fail */
		lex_error(SCERR_MUST_USE_SEPR);
		return NULL;
	}
    parser->parseTree = parseTranslations(parser);

	if(!matchToken(&parser,*SECTION_STARTER).lexeme){
		/* fail */
		lex_error(SCERR_SEPR_AFTER_TRANS);
		return NULL;
		
	}
	/* optional aux */
	aux(parser);
	
	return NULL;
}
void pushBackLastToken(Lexer* lex){
	
}

char* aux(Parser* parser){
	return NULL;
}

