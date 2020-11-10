#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "basebuffer.h"
#include "funcs.h"
#ifdef __STRICT_ANSI__
#define inline
#endif

#define check_for(sign, error)                                                 \
  pass_ws(programIO);															\
  if (programIO->c != sign) {                                                 \
    lex_error(error);                                                          \
    return NULL;                                                               \
  }
  
void initLexer(Lexer* lex){
/*	init_base_buffer(lex->inputBuffer);*/
    lex->inputBuffer = NULL;
	initTokenStream(&lex->tokens);
	lex->previous_char = '\0';
	lex->current_char =  '\0';
    lex->passWS = 1;
    lex->individualTokens = 0;
}
inline int isWhitespace(Lexer* lex){
	return is_ws(lex->current_char);
}
inline int isEOF(Lexer* lex){
  	return lex->current_char == EOF;
}
inline int isEOS(Lexer* lex){
  	return lex->current_char == '\0';
}
inline int isNewline(Lexer* lex){
	return lex->current_char == '\n';
}
inline void pass_ws(Lexer* lex){
    while (isWhitespace(lex) || isNewline(lex))
		getNextChar(lex);
}
inline void getNextChar(Lexer* lex){
	lex->previous_char = lex->current_char;
	lex->current_char = (char)getchar(lex->inputBuffer);
}
inline void pushBackChar(Lexer* lex){
	lex->current_char = lex->previous_char;
	lex->previous_char = (char)ungetchar(lex->inputBuffer);
}
LexerToken tokenRunner(Lexer* lexer,LexerToken token,int type){
    LexerToken temp;
/*    if(lexer->individualTokens){
	   temp = tokenForLexeme(&lexer->current_char);
	   getNextChar(lexer);
	   return temp;
    }*/
    temp = peekTokenStack(&lexer->tokens.stack);
    if(!temp.lexeme){
	    pushNextTokenOnStack(lexer);
    }
    switch(type){
	   case 0:
		  if(token.id != (peekTokenStack(&lexer->tokens.stack)).id)
			  return defaultTokens[0];
	   case 1:
	   default:
		  return popTokenStack(&lexer->tokens.stack);
    }
}
LexerToken getNextToken(Lexer* lexer){
    return tokenRunner(lexer,tokenForType(NONE),1);
}
LexerToken matchToken(Lexer* lexer,LexerToken token){
    return tokenRunner(lexer,token,0);
}
void setIndividualTokens(Lexer* lexer, int status){
    LexerToken temp;
    int counter;
    switch(status){
	   case 1:
		  while((temp = peekTokenStack(&lexer->tokens.stack)).lexeme){
			 for(counter=0;counter<strlen(temp.lexeme);counter++){
				pushBackChar(lexer);
			 }
			 popTokenStack(&lexer->tokens.stack);
		  }
		  lexer->individualTokens = 1;
		  break;
	   case 0:
	   default:
		  lexer->individualTokens = 0;
    }
}

char* readRawStringUntilToken(Lexer* lex, const LexerToken token){
    LexerToken tempToken;
    char stringBuffer[8000];
    char *readString;
    int stringLength =0;
	 initToken(&tempToken);
    readString = NULL;
    while(1){
	   if(lex->current_char == token.lexeme[0]){
		  
		  if((tempToken = matchToken(lex,token)).lexeme){
			  deleteToken(tempToken);
			 break;
		  }
	   }
	   if( isEOF(lex) || isEOS(lex)){
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
void pushNextTokenOnStack(Lexer* lexer){
	LexerToken tempToken;
	tempToken = readNextToken(lexer);
	pushTokenStack(&lexer->tokens.stack,tempToken);
}
void pushBackLastToken(Lexer* lexer,LexerToken token){
	pushTokenStack(&lexer->tokens.stack,token);
}
LexerToken readNextToken(Lexer* lex){
	char tempChar[40];
	char* ptr;
	LexerToken tempToken;
	initToken(&tempToken);
	ptr = tempChar;
    if(lex->passWS)
	 	pass_ws(lex);
	if(isalphaC(lex->current_char)){
		tempToken = tokenForType(IDENTIFIER);
		do{
			*ptr = lex->current_char;
			ptr++;
			getNextChar(lex);
		    if(lex->individualTokens)
			   break;
		}while(isalphaC(lex->current_char));
		*ptr = '\0';
		tempToken.lexeme = strdup(tempChar);
	    tempToken.allocated= 1;
		return tempToken;
	}
	else if(isdigitC(lex->current_char)){
		tempToken = tokenForType(NUMBER);
		do{
			*ptr = lex->current_char;
			ptr++;
			getNextChar(lex);
		    if(lex->individualTokens)
			   break;
		}while(isdigitC(lex->current_char));
		*ptr = '\0';
		tempToken.lexeme = strdup(tempChar);
	    tempToken.allocated = 1;
		return tempToken;
	}
	else
		switch(lex->current_char){
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
			   if(!lex->individualTokens){
				getNextChar(lex);
				  if(lex->current_char == '='){
				    tempToken = tokenForType(EQUIV);
					 break;
				  }
				  else
				    pushBackChar(lex);
			   }
				tempToken = tokenForType(EQUALS);
				break;
			case '%':
			   if(!lex->individualTokens){
				  getNextChar(lex);
				  if(lex->current_char == '%'){
					 tempToken = tokenForType(SECTION_STARTER);
					 break;
				  }
				  else if(lex->current_char == '{'){
					 tempToken = tokenForType(OPEN_STARTER);
					 break;
				  }
				  else if(lex->current_char == '}'){
					 tempToken = tokenForType(CLOSE_STARTER);
					 break;
				  }
				  else
					 pushBackChar(lex);
			   }
			 tempToken = tokenForType(PERCENT);
			   break;
			case '<':
			   if(!lex->individualTokens){
				getNextChar(lex);
				if(lex->current_char == '='){
					 tempToken = tokenForType(LTE);
					 break;
				  }
				else
				    pushBackChar(lex);
			   }
			    tempToken = tokenForType(LESS);
				break;
			case '>':
			   if(!lex->individualTokens){
				  getNextChar(lex);
				  if(lex->current_char == '='){
					tempToken = tokenForType(GTE);
					 break;
				  }
				else
				    pushBackChar(lex);
			   }
			 tempToken = tokenForType(GREAT);
				break;
			case '!':
			   if(!lex->individualTokens){
				  getNextChar(lex);
				  if(lex->current_char == '='){
					tempToken = tokenForType(NOTEQUAL);
					 break;
				  }
				else
				    pushBackChar(lex);
			   }
				tempToken = tokenForType(NOT);
				break;
			case '.':
			   if(!lex->individualTokens){
				  getNextChar(lex);
				  if(lex->current_char == '.'){
					getNextChar(lex);
					 if(lex->current_char == '.'){
						tempToken = tokenForType(ELIPSE);
						break;
					 }
					else{
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
