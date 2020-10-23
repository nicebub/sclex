#ifndef _MLEXER_H
#define _MLEXER_H

#include "basebuffer.h"
#define STACK_SIZE 50
typedef struct _lexerToken LexerToken;
struct _lexerToken {
	char* lexeme;
};

typedef struct _lexerTokenStack LStack;
struct _lexerTokenStack {
	LexerToken stack[STACK_SIZE];
	LexerToken* top;
};


void initTokenStack(LStack* stack);
void pushTokenStack(LStack* stack, LexerToken token);
LexerToken peekTokenStack(LStack* stack);
LexerToken popTokenStack(LStack* stack);

typedef struct _lexer Lexer;
struct _lexer {
	Buffer inputBuffer;
	LStack tokenStack;
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




LexerToken matchedNextToken(Lexer* lex,char* token);
char* readRawStringUntilToken(Lexer* lex, char* token);
void pushBackLastToken(Lexer* lex);

#endif