#ifndef _MPARSER_H
#define _MPARSER_H
#include "lfile.h"
#include "tree.h"

static char OPEN_STARTER[] = "%{";
static char CLOSE_STARTER[] = "%}";
static char SECTION_STARTER[] = "%%";

typedef TreeNode RegularExpressionTreeNode;
typedef TreeArray RegularExpressionTreeArray;

RegularExpressionTreeArray* parseRegularExpressionSet(Io* programIO);
RegularExpressionTreeArray* parseInputFile(Io* programIO);
RegularExpressionTreeArray* parseTranslations(Io* programIO);

RegularExpressionTreeNode* parseCharSet(base_set ** set, Io* programIO);
RegularExpressionTreeNode* parseEscapeChars(base_set** set, Io* programIO);/* char_set** */
RegularExpressionTreeNode* parseExpression(base_set ** set,Io* programIO); /* char_set** */
RegularExpressionTreeNode* apply_def(base_set** set,Io* programIO); /* char_set** */
RegularExpressionTreeNode* parseExpressionList(base_set ** set,Io* programIO);/* char_set** */
RegularExpressionTreeNode* parseExpressionOR(base_set ** set,Io* programIO);/* char_set** */
RegularExpressionTreeNode* parseFullExpression(base_set ** set,Io* programIO);
RegularExpressionTreeNode* parseRegularExpression(RegularExpressionTreeArray ** ta,Io* programIO);

char* aux(Io* programIO);
char* parseDeclarations(Io* programIO);
void parseDefinitions(Io* programIO);

#endif
