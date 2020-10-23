#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "basebuffer.h"
#include "funcs.h"
#ifdef __STRICT_ANSI__
#define inline
#endif

/*#define pass_ws()                                                              \
  while ((is_ws(*current_char)) || *current_char == '\n')                 \
    *current_char = getchar(inputBuffer);*/
#define check_for(sign, error)                                                 \
  pass_ws(programIO);															\
  if (programIO->c != sign) {                                                 \
    lex_error(error);                                                          \
    return NULL;                                                               \
  }

void initLexer(Lexer* lex){
	init_base_buffer(&lex->inputBuffer);
	lex->file = NULL;
	lex->previous_char = '\0';
	lex->current_char =  '\0';
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
    while (is_ws(lex->current_char) || isNewline(lex))
		getNextChar(lex);
}

inline void getNextChar(Lexer* lex){
	lex->previous_char = lex->current_char;
	lex->current_char = getchar(&lex->inputBuffer);
}
inline void pushBackChar(Lexer* lex){
	lex->current_char = lex->previous_char;
	ungetchar(&lex->inputBuffer);
}

LexerToken matchedNextToken(Lexer* lex,char* token){
	LexerToken temp;
	temp.lexeme=NULL;
	if(lex->current_char == token[0]){
		getNextChar(lex);
		if(lex->current_char == token[1]){
			getNextChar(lex);
			temp.lexeme = token;
		}
		else
			pushBackChar(lex);
	}
	return temp;
}

char* readRawStringUntilToken(Lexer* lex, char* token){
    char stringBuffer[8000];
    char *readString;
    int stringLength =0;
    readString = NULL;
/*	getNextChar(lex);*/
	while(!(matchedNextToken(lex,token).lexeme)){
		if( isEOF(lex) || isEOS(lex))
			return NULL;
		stringBuffer[stringLength] = lex->current_char;
		stringLength++;
		getNextChar(lex);
	}
	stringBuffer[stringLength]='\0';
	readString = malloc(sizeof(char)*strlen(stringBuffer)+1);
	strncpy(readString,stringBuffer,strlen(stringBuffer)+1);
	return readString;
}
/*#undef pass_ws*/
#undef check_for
