#include <string.h>
#include <stdlib.h>
#include "Lexer.h"
#include "token.h"

void initToken(LexerToken* token){
	*token = defaultTokens[NONE];
}

void deleteToken(LexerToken tempToken){
  if(tempToken.lexeme && tempToken.allocated){
	 free(tempToken.lexeme);
	 tempToken.lexeme= NULL;
  }
}
LexerToken tokenForType(enum _tokenType type){
	return defaultTokens[type];
}

LexerToken tokenForLexeme(char* lexeme){
	int counter;
	for(counter=0;counter<TOKENSDEFINED;counter++){
		if(strcmp(lexeme,defaultTokens[counter].lexeme)==0)
			return defaultTokens[counter];
	}
	return defaultTokens[NONE];
}
char* lexemeForType(const enum _tokenType type){
	return defaultTokens[type].lexeme;
}
int tokensMatch(LexerToken one, LexerToken two){
	return (strcmp(one.lexeme,two.lexeme)==0);
}

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
LexerToken peekTokenStack(LStack* astack){
    if(astack->top == astack->stack)
	   return defaultTokens[0];
    return *(astack->top-1);
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

 void initTokenStream(TokenStream* stream){
	initTokenStack(&stream->stack);
}
