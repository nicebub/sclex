#ifndef _MLEXER_H
#define _MLEXER_H

#include "basebuffer.h"
typedef struct _lexer Lexer;
struct _lexer {
	Buffer inputBuffer;
	char* file;
	char previous_char;
	char current_char;

};

void* getLexerByFilename();
void* getLexerByFile();
void* getLexerByString();
void* getLexerByBuffer();
void* getNextToken();
void* consumeWhiteSpace();

void initLexer(Lexer* lex);

 void pass_ws(Lexer* lex);

 int isEOF(Lexer* lex);
 int isEOS(Lexer* lex);
 int isNewline(Lexer* lex);
 int isWhitespace(Lexer* lex);

 void getNextChar(Lexer* lex);
 void pushBackChar(Lexer* lex);

char* matchedNextToken(Lexer* lex,char* token);
char* readRawStringUntilToken(Lexer* lex, char* token);
void pushBackLastToken(Lexer* lex);

#endif