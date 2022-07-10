#ifndef _XOPEN_SOURCE
# define _XOPEN_SOURCE 500
#endif /* _XOPEN_SOURCE */

#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE 200809L
#endif /* _POSIX_C_SOURCE */

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#ifndef _DEFAULT_SOURCE
# define _DEFAULT_SOURCE
#endif /* _DEFAULT_SOURCE */

#ifndef _BSD_SOURCE
# define _BSD_SOURCE
#endif /* _BSD_SOURCE */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Lexer.h"
#include "basebuffer.h"
#include "funcs.h"
#include "log.h"
#ifdef __STRICT_ANSI__
#define inline
#endif

#define check_for(sign, error)\
{\
   pass_ws(programIO);\
   if (programIO->c != sign)\
   {\
      lex_error(error);\
      return NULL;\
   }\
}

void initLexer(Lexer* lex)
{
   if (NULL != lex)
   {
      memset(lex,0,sizeof(*lex));
      initTokenStream(&lex->tokens);
      lex->passWS = 1;
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}
extern inline int isWhitespace(Lexer* lex)
{
   int ret = false;

   if(NULL != lex)
   {
      ret = is_ws(lex->current_char);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return ret;
}
extern inline int isEOF(Lexer* lex)
{
   int ret = false;

   if(NULL != lex)
   {
      ret = lex->current_char == EOF;
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return ret;
}
extern inline int isEOS(Lexer* lex)
{
   int ret = false;

   if(NULL != lex)
   {
      ret = lex->current_char == '\0';
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return ret;
}
extern inline int isNewline(Lexer* lex)
{
   int ret = false;

   if(NULL != lex)
   {
      ret = lex->current_char == '\n';
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return ret;
}
extern inline void pass_ws(Lexer* lex)
{
   if(NULL != lex)
   {
      while ((true == isWhitespace(lex)) || (true == isNewline(lex)))
      {
         getNextChar(lex);
      }
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}
extern inline void getNextChar(Lexer* lex)
{
   if(NULL != lex)
   {
      lex->previous_char = lex->current_char;
      lex->current_char = (char)getchar(lex->inputBuffer);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}
extern inline void pushBackChar(Lexer* lex)
{
   if(NULL != lex)
   {
      lex->current_char = lex->previous_char;
      lex->previous_char = (char)ungetchar(lex->inputBuffer);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}
LexerToken tokenRunner(Lexer* lexer,LexerToken token,int type)
{
   LexerToken temp = {0};
   if (NULL != lexer)
   {
      temp = peekTokenStack(&lexer->tokens.stack);
      LOG_0("lexeme found <%s>\n", temp.lexeme);
      if(NULL == temp.lexeme)
      {
         pushNextTokenOnStack(lexer);
         temp = peekTokenStack(&lexer->tokens.stack);
      }
      switch(type)
      {
         case 0:
         {
            if(token.id != (temp.id))
            {
               LOG_0("setting default token\n");
               temp = defaultTokens[0];
            }
            else
            {
               temp = popTokenStack(&lexer->tokens.stack);
            }
            break;
         }
         case 1:
         default:
         {
            temp = popTokenStack(&lexer->tokens.stack);
            break;
         }
      }
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }

   return temp;
}
LexerToken getNextToken(Lexer* lexer)
{
   LexerToken t = {0};
   if (NULL != lexer)
   {
      t = tokenRunner(lexer,tokenForType(NONE),1);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return t;
}
LexerToken matchToken(Lexer* lexer,LexerToken token)
{
   LexerToken t = {0};
   if (NULL != lexer)
   {
      t = tokenRunner(lexer, token, 0);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   return t;
}
void setIndividualTokens(Lexer* lexer, int status)
{
   LexerToken temp = {0};
   int     counter = 0;
   if(NULL != lexer)
   {
      switch(status)
      {
	      case 1:
         {
            while((temp = peekTokenStack(&lexer->tokens.stack)).lexeme)
            {
			      for(counter=0;counter<strlen(temp.lexeme);counter++)
               {
   				   pushBackChar(lexer);
	   		   }

		   	   popTokenStack(&lexer->tokens.stack);
		      }

            lexer->individualTokens = 1;

            break;
         }
   	   case 0:
	      default:
         {
   		   lexer->individualTokens = 0;
            break;
         }
      }
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}

char* readRawStringUntilToken(Lexer* lex, const LexerToken token)
{
    LexerToken    tempToken = {0};
    char stringBuffer[8000] = {'\0'};
    char *       readString = NULL;
    int        stringLength = 0;

    while(1)
    {
	   if(lex->current_char == token.lexeme[0])
      {
		  
		  if((tempToken = matchToken(lex,token)).lexeme)
        {
			  deleteToken(tempToken);
			 break;
		  }
	   }
	   if( isEOF(lex) || isEOS(lex))
      {
		  deleteToken(tempToken);
			return NULL;
	   }
	  deleteToken(tempToken);
		stringBuffer[stringLength] = lex->current_char;
		stringLength++;
		getNextChar(lex);
	}
	stringBuffer[stringLength]='\0';
	readString = malloc(sizeof(char)*strlen(stringBuffer)+1);
	strncpy(readString,stringBuffer,strlen(stringBuffer)+1);
	return readString;
}
void pushNextTokenOnStack(Lexer* lexer)
{
	LexerToken tempToken = {0};
   if (NULL != lexer)
   {
   	tempToken = readNextToken(lexer);
      LOG_0("pushing this token onto stack <%s>\n",tempToken.lexeme);
	   pushTokenStack(&lexer->tokens.stack,tempToken);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}

void pushBackLastToken(Lexer* lexer,LexerToken token)
{
   if(NULL != lexer)
   {
      pushTokenStack(&lexer->tokens.stack,token);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}

LexerToken readNextToken(Lexer* lex)
{
   char    tempChar[40] = {'\0'};
   char*            ptr = tempChar;
   LexerToken tempToken = {0};

   if(true == lex->passWS)
   {
      pass_ws(lex);
   }
   if(true == isalphaC(lex->current_char))
   {
      tempToken = tokenForType(IDENTIFIER);
      do
      {
         *ptr = lex->current_char;
         ptr++;
         getNextChar(lex);
         if(true == lex->individualTokens)
         {
            break;
         }
		}while(true == isalphaC(lex->current_char));

		*ptr = '\0';
		tempToken.lexeme = strndup(tempChar, strlen(tempChar));
	    tempToken.allocated= 1;
		return tempToken;
	}
	else if(isdigitC(lex->current_char))
   {
		tempToken = tokenForType(NUMBER);
		do
      {
			*ptr = lex->current_char;
			ptr++;
			getNextChar(lex);
		    if(lex->individualTokens)
          {
			    break;
          }
		}while(isdigitC(lex->current_char));
		*ptr = '\0';
		tempToken.lexeme = strdup(tempChar);
	    tempToken.allocated = 1;
		return tempToken;
	}
	else
		switch(lex->current_char)
      {
		    case '\'':
			   tempToken = tokenForType(SQUOTE);
			   break;
		    case '\"':
			   tempToken = tokenForType(DBLQUOTE);
			   break;
		    case '\\':
			   tempToken = tokenForType(BSLASH);
			   break;
		    case ' ':
			   tempToken = tokenForType(SPACE);
			   break;
		    case '	':
			   tempToken = tokenForType(TAB);
			   break;
		    case '#':
			   tempToken = tokenForType(HASHMARK);
			   break;
		    case '_':
			   tempToken = tokenForType(UNDERSCORE);
			   break;
			case '[':/*]*/
				tempToken = tokenForType(LBRACKET);
				break;
			case '{':/*}*/
				tempToken = tokenForType(LCURLY);
				break;
			case '(':/*)*/
				tempToken = tokenForType(LPAREN);
				break;
			case ']':
				tempToken = tokenForType(RBRACKET);
				break;
			case '}':
				tempToken = tokenForType(RCURLY);
				break;
			case ')':
				tempToken = tokenForType(RPAREN);
				break;
			case ',':
				tempToken = tokenForType(COMMATOKEN);
				break;
			case '*':
				tempToken = tokenForType(STARTOKEN);
				break;
			case '+':
				tempToken = tokenForType(PLUSTOKEN);
				break;
			case '-':
				tempToken = tokenForType(MINUSTOKEN);
				break;
			case ';':
				tempToken = tokenForType(SEMICOLON);
				break;
			case '&':
				tempToken = tokenForType(ADDRESS);
				break;
			case '/':
				tempToken = tokenForType(FSLASH);
				break;
			case '|':
				tempToken = tokenForType(ORTOKEN);
				break;
			case '?':
				tempToken = tokenForType(QUESTION);
				break;
			case '\0':
				tempToken = tokenForType(EMPTYTOKEN);
				break;
			case '=':
				getNextChar(lex);
				  if(lex->current_char == '=')
              {
				    tempToken = tokenForType(EQUIV);
					 break;
				  }
				pushBackChar(lex);
				tempToken = tokenForType(EQUALS);
				break;
			case '%':
				  getNextChar(lex);
				  if(lex->current_char == '%')
              {
					 tempToken = tokenForType(SECTION_STARTER);
					 break;
				  }
				  else if(lex->current_char == '{')
              {
					 tempToken = tokenForType(OPEN_STARTER);
					 break;
				  }
				  else if(lex->current_char == '}')
              {
					 tempToken = tokenForType(CLOSE_STARTER);
					 break;
				  }
			 pushBackChar(lex);
			 tempToken = tokenForType(PERCENT);
			   break;
			case '<':
				getNextChar(lex);
				if(lex->current_char == '=')
            {
					 tempToken = tokenForType(LTE);
					 break;
				}
				    pushBackChar(lex);
			    tempToken = tokenForType(LESS);
				break;
			case '>':
				  getNextChar(lex);
				  if(lex->current_char == '=')
              {
					tempToken = tokenForType(GTE);
					 break;
				  }
			    pushBackChar(lex);
			 tempToken = tokenForType(GREAT);
				break;
			case '!':
				  getNextChar(lex);
				  if(lex->current_char == '=')
              {
					tempToken = tokenForType(NOTEQUAL);
					 break;
				  }
				    pushBackChar(lex);
				tempToken = tokenForType(NOT);
				break;
			case '.':
			   if(!lex->individualTokens)
            {
				  getNextChar(lex);
				  if(lex->current_char == '.')
              {
					getNextChar(lex);
					 if(lex->current_char == '.')
                {
						tempToken = tokenForType(ELIPSE);
						break;
					 }
					else
               {
						pushBackChar(lex);
					    pushBackChar(lex);
					}
				  }
				  else
				    pushBackChar(lex);
			   }
				    tempToken = tokenForType(DOT);
				    break;
			default:
				tempToken =  defaultTokens[0];
				break;
	}
    getNextChar(lex);
    return tempToken;
}
/*
LexerToken matchedNextToken(Lexer* lex,const LexerToken token){
	LexerToken temp;
	initToken(&temp);
    if(token.type == IDENTIFIER){
	   temp = getNextToken(lex);
	   
	   if(temp.type == IDENTIFIER){
		  getNextChar(lex);
		  return temp;
	   }
	   if(temp.lexeme && temp.allocated)
		  free(temp.lexeme);
	   initToken(&temp);
    }
    else if(token.type == NUMBER){
	   int counter;
	   temp = getNextToken(lex);
	   
	   if(temp.type == NUMBER){
		  getNextChar(lex);
		  return temp;
	   }
	   for(counter=0;counter<strlen(temp.lexeme)-1;counter++)
		  pushBackChar(lex);
		  deleteToken(temp);
	   initToken(&temp);

    }
    */
	 /*
    else{
	   temp = getNextToken(lex);
	   getNextChar(lex);
	   if(temp.type == token.type){
		  if(!(strcmp(temp.lexeme,token.lexeme)==0)){
			 return defaultTokens[0];
		  }
	   }
	   return temp;
    }
    */
/*    else{
	   int counter;
	   for(counter=0;counter<strlen(token.lexeme);counter++){
		  if(lex->current_char != token.lexeme[counter]){
			 while(counter--)
				pushBackChar(lex);
			 initToken(&temp);
			 return temp;
		  }
		  getNextChar(lex);
	   }
	   getNextChar(lex);
	   temp.lexeme = token.lexeme;
	   temp.id = token.id;
	   temp.type = token.type;

    }

	else if(lex->current_char == token.lexeme[0]){
		getNextChar(lex);
		if(lex->current_char == token.lexeme[1]){
			getNextChar(lex);
			temp.lexeme = token.lexeme;
			temp.id = token.id;
			temp.type = token.type;
		}
		else
			pushBackChar(lex);
	}*/
/*
	return temp;
}*/

/*#undef pass_ws*/
#undef check_for
