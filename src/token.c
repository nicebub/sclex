#include <string.h>
#include <stdlib.h>
#include "Lexer.h"
#include "token.h"
#include "log.h"
void initToken(LexerToken* token)
{
	*token = defaultTokens[NONE];
}

void deleteToken(LexerToken tempToken){
  if(tempToken.lexeme && tempToken.allocated)
  {
	 free(tempToken.lexeme);
	 tempToken.lexeme= NULL;
  }
}
LexerToken tokenForType(enum _tokenType type)
{
	return defaultTokens[type];
}

LexerToken tokenForLexeme(char* lexeme)
{
	int counter;
	for(counter=0;counter<TOKENSDEFINED;counter++)
	{
	    if(defaultTokens[counter].lexeme)
		if(strcmp(lexeme,defaultTokens[counter].lexeme)==0)
			return defaultTokens[counter];
	}
	return defaultTokens[NONE];
}
char* lexemeForType(const enum _tokenType type)
{
	return defaultTokens[type].lexeme;
}
int tokensMatch(LexerToken one, LexerToken two)
{
	return (strcmp(one.lexeme,two.lexeme)==0);
}

void initTokenStack(LStack* stack)
{
	if(NULL != stack)
	{
      memset(stack,0,sizeof(*stack));	
      stack->top = &stack->stack[0];
	}
}
void pushTokenStack(LStack* stack, LexerToken token)
{
	*stack->top = token;
	stack->top++;
}
LexerToken peekTokenStack(LStack* astack)
{
   LexerToken t = {0};

   if(NULL != astack)
   {
      if(astack->top == astack->stack)
      {
		LOG_0("equal to top of stack\n");
         t = defaultTokens[0];
      }
      else
      {
		LOG_0("not equal to top of stack\n");
         t = *(astack->top-1);
      }
   }

   return t;
}
LexerToken popTokenStack(LStack* stack)
{
	LexerToken temp = {0};

   
	if(stack->top != stack->stack)
	{
		stack->top--;
		temp = *stack->top;
		stack->top->lexeme=NULL;
	}
	return temp;
}