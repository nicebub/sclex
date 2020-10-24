#ifndef _MLEXER_H
#define _MLEXER_H

#include "basebuffer.h"

typedef struct _lexerToken LexerToken;
struct _lexerToken {
	char* lexeme;
	int id;
	int type;
};

typedef struct _lexer Lexer;
struct _lexer {
	Buffer inputBuffer;
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




LexerToken matchedNextToken(Lexer* lex,const LexerToken token);
char* readRawStringUntilToken(Lexer* lex, const LexerToken token);

#endif