#ifndef _MPARSER_H
#define _MPARSER_H
#include "lfile.h"
#include "tree.h"
#include "Lexer.h"

#define PTS_STACK_SIZE 50

enum _tokenType {
	OPEN_STARTER,
	CLOSE_STARTER,
	SECTION_STARTER,
	IDENTIFIER,
	NUMBER,
	LPAREN,
	RPAREN,
	LBRACKET,
	RBRACKET,
	LCURLY,
	RCURLY,
	COMMATOKEN,
	DOT,
	STARTOKEN,
	PLUSTOKEN,
	MINUSTOKEN,
	EQUALS,
	SEMICOLON,
	LESS,
	LTE,
	GREAT,
	GTE,
	NOTEQUAL,
	EQUIV,
	ADDRESS,
	ELIPSE,
	FSLASH,
	RPS,
	CHRSET,
	EPSLN,
	CNCAT,
	ORTOKEN,
	QUESTION,
	EMPTYTOKEN
	
} tokenTypes;

const static LexerToken  defaultTokens[] = {
	{NULL,-1,-1},
	 {"%{",0,OPEN_STARTER}, 
	 {"%}",1,CLOSE_STARTER}, 
	 {"%%",2,SECTION_STARTER},
	 {NULL,3,IDENTIFIER},
	 {NULL,4,NUMBER},
	 {"(",5,LPAREN},
	 {")",6,RPAREN},
	 {"[",7,LBRACKET},
	 {"]",8,RBRACKET},
	 {"{",9,LCURLY},
	 {"}",10,RCURLY},
	 {",",11,COMMATOKEN},
	 {".",12,DOT},
	 {"*",13,STARTOKEN},
	 {"+",14,PLUSTOKEN},
	 {"-",15,MINUSTOKEN},
	 {"=",16,EQUALS},
	 {";",17,SEMICOLON},
	 {"<",18,LESS},
	 {"<=",19,LTE},
	 {">",20,GREAT},
	 {">=",21,GTE},
	 {"!=",22,NOTEQUAL},
	 {"==",23,EQUIV},
	 {"&",24,ADDRESS},
	 {"...",25,ELIPSE},
	 {"/",26,FSLASH},
	 {NULL,27,RPS},
	 {NULL,28,CHRSET},
	 {NULL,29,EPSLN},
	 {NULL,30,CNCAT},
	 {"|",31,ORTOKEN},
	 {"?",32,QUESTION},
	 {"",33,EMPTYTOKEN},
	 
};

LexerToken tokenForType(enum _tokenType type);

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
void pushBackLastToken(Parser* parser, LexerToken token);

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
