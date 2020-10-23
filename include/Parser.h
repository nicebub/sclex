#ifndef _MPARSER_H
#define _MPARSER_H
#include "lfile.h"
#include "tree.h"
#include "Lexer.h"

#define PTS_STACK_SIZE 50


const static LexerToken  defaultTokens[] = {
	{NULL,-1,-1}, {"%{",0,0},{"%}",1,1},{"%%",2,2}
};

const static LexerToken*  const OPEN_STARTER = &defaultTokens[1];
const static LexerToken*  const CLOSE_STARTER = &defaultTokens[2];
const static LexerToken*  const SECTION_STARTER = &defaultTokens[3];


typedef TreeNode RegularExpressionTreeNode;
typedef TreeArray RegularExpressionTreeArray;

typedef struct _parserTokenStack LStack;
struct _parserTokenStack {
	LexerToken stack[PTS_STACK_SIZE];
	LexerToken* top;
};
typedef struct _parserTokenStream TokenStream;
struct _parserTokenStream {
	LStack stack;
};

typedef struct _parser Parser;
struct _parser {
	Lexer lexer;
	TokenStream tokens;
	RegularExpressionTreeArray* parseTree;
    Buffer **defbuf;
    base_vector *fpos; /* int_vector* */
	char** defs;
	char* decs;
	char* aux;
	int num_defs;
};


void initTokenStack(LStack* stack);
void pushTokenStack(LStack* stack, LexerToken token);
LexerToken peekTokenStack(LStack* stack);
LexerToken popTokenStack(LStack* stack);

void initTokenStream(TokenStream* stream);
LexerToken matchToken(Parser* parser,LexerToken token);

void initParser(Parser* parser);
void initParserWithFilename(Parser* parser,char* arg);

RegularExpressionTreeArray* parseRegularExpressionSet(Parser* parser);
RegularExpressionTreeArray* parseInputFile(Parser* parser);
RegularExpressionTreeArray* parseTranslations(Parser* parser);

RegularExpressionTreeNode* parseCharSet(base_set ** set, Parser* parser);
RegularExpressionTreeNode* parseEscapeChars(base_set** set, Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseExpression(base_set ** set,Parser* parser); /* char_set** */
RegularExpressionTreeNode* apply_def(base_set** set,Parser* parser); /* char_set** */
RegularExpressionTreeNode* parseExpressionList(base_set ** set,Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseExpressionOR(base_set ** set,Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseFullExpression(base_set ** set,Parser* parser);
RegularExpressionTreeNode* parseRegularExpression(RegularExpressionTreeArray ** ta,Parser* parser);

char* aux(Parser* parser);
char* parseDeclarations(Parser* parser);
void parseDefinitions(Parser* parser);

#endif
