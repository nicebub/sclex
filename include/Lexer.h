#ifndef _MLEXER_H
#define _MLEXER_H

#include "basebuffer.h"
#include "token.h"

typedef struct _lexer Lexer;
struct _lexer {
    Buffer inputBuffer;
    TokenStream tokens;
    char previous_char;
    char current_char;
    int passWS;
    int individualTokens;

};

/*
void* getLexerByFilename();
void* getLexerByFile();
void* getLexerByString();
void* getLexerByBuffer();
void* getNextToken();
void* consumeWhiteSpace();
*/

void initLexer(Lexer* lex);

 void pass_ws(Lexer* lex);

 int isEOF(Lexer* lex);
 int isEOS(Lexer* lex);
 int isNewline(Lexer* lex);
 int isWhitespace(Lexer* lex);

 void getNextChar(Lexer* lex);
 void pushBackChar(Lexer* lex);
void pushNextTokenOnStack(Lexer* lexer);

LexerToken getNextToken(Lexer* lex);
LexerToken matchToken(Lexer* lexer,LexerToken token);
void pushBackLastToken(Lexer* lexer,LexerToken token);

LexerToken matchedNextToken(Lexer* lex,const LexerToken token);
char* readRawStringUntilToken(Lexer* lex, const LexerToken token);
LexerToken readNextToken(Lexer* lex);
void setIndividualTokens(Lexer* lexer, int status);

#endif
