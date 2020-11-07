#ifndef _MPARSER_H
#define _MPARSER_H
#include "lfile.h"
#include "tree.h"
#include "Lexer.h"
#include "token.h"



typedef TreeNode RegularExpressionTreeNode;
typedef TreeArray RegularExpressionTreeArray;

typedef struct _definition Definition;
struct _definition {
/*	Buffer buffer;*/
	LexerToken name;
	char* expression;
};

typedef struct _parser Parser;
struct _parser {
	Lexer lexer;
	RegularExpressionTreeArray* parseTree; /* old ta */
    Buffer **definitionBuffer;
    Definition* definitionList;
    base_vector *fpos; /* int_vector* */
	char** defs;
	char* decs;
	char* aux;
	int num_defs;
};



void initParser(Parser* parser);
void initParserWithFilename(Parser* parser,char* arg);
void initNextDefinition(Parser* parser);
void setupdefinitionList(Parser* parser);
void parseDefinitionValue(Parser* parser, LexerToken name);

RegularExpressionTreeArray* parseRegularExpressionSet(Parser* parser);
RegularExpressionTreeArray* parseInputFile(Parser* parser);
RegularExpressionTreeArray* parseTranslations(Parser* parser);

RegularExpressionTreeNode* parseCharSet(base_set ** set, Parser* parser);
RegularExpressionTreeNode* parseEscapeChars(Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseExpression(Parser* parser); /* char_set** */
RegularExpressionTreeNode* apply_def(Parser* parser); /* char_set** */
RegularExpressionTreeNode* parseExpressionList(Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseExpressionOR(Parser* parser);/* char_set** */
RegularExpressionTreeNode* parseFullExpression(Parser* parser);
RegularExpressionTreeNode* parseRegularExpression(Parser* parser);

char* aux(Parser* parser);
char* parseDeclarations(Parser* parser);
void parseDefinitions(Parser* parser);
Definition* definitionExists(Parser* parser,LexerToken name);

#endif
