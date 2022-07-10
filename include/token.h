#ifndef _MTOKEN_H
#define _MTOKEN_H

#define PTS_STACK_SIZE 50


typedef struct _lexerToken LexerToken;
struct _lexerToken
{
	char* lexeme;
	int id;
	int type;
	int allocated;
};

typedef struct _parserTokenStack LStack;
struct _parserTokenStack
{
	LexerToken stack[PTS_STACK_SIZE];
	LexerToken* top;
};
typedef struct _parserTokenStream TokenStream;
struct _parserTokenStream
{
	LStack stack;
};

enum _tokenType
{
   NONE,
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
   EMPTYTOKEN,
   NOT,
   UNDERSCORE,
   BSLASH,
   SQUOTE,
   DBLQUOTE,
   HASHMARK,
   AMPERSAND,
   CAROT,
   DOLLAR,
   ATSIGN,
   TILDA,
   FQUOTE,
   COLON,
   SPACE,
   TAB,
   PERCENT
};

const static LexerToken  defaultTokens[] = {
   {NULL,-1,NONE,0},
	{"%{",0,OPEN_STARTER,0},
	{"%}",1,CLOSE_STARTER,0},
	{"%%",2,SECTION_STARTER,0},
	{NULL,3,IDENTIFIER,0},
	{NULL,4,NUMBER,0},
	{"(",5,LPAREN,0},
	{")",6,RPAREN,0},
	{"[",7,LBRACKET,0},
	{"]",8,RBRACKET,0},
	{"{",9,LCURLY,0},
	{"}",10,RCURLY,0},
	{",",11,COMMATOKEN,0},
	{".",12,DOT,0},
	{"*",13,STARTOKEN,0},
	{"+",14,PLUSTOKEN,0},
	{"-",15,MINUSTOKEN,0},
	{"=",16,EQUALS,0},
	{";",17,SEMICOLON,0},
	{"<",18,LESS,0},
	{"<=",19,LTE,0},
	{">",20,GREAT,0},
	{">=",21,GTE,0},
	{"!=",22,NOTEQUAL,0},
	{"==",23,EQUIV,0},
	{"&",24,ADDRESS,0},
	{"...",25,ELIPSE,0},
	{"/",26,FSLASH,0},
	{NULL,27,RPS,0},
	{NULL,28,CHRSET,0},
	{NULL,29,EPSLN,0},
	{NULL,30,CNCAT,0},
	{"|",31,ORTOKEN,0},
	{"?",32,QUESTION,0},
	{"",33,EMPTYTOKEN,0},
	{"!",34,NOT,0},
   {"_",35,UNDERSCORE,0},
   {"\\",36,BSLASH,0},
   {"'",37,SQUOTE,0},
   {"\"",38,DBLQUOTE,0},
   {"#",39, HASHMARK,0},
   {"&",40, AMPERSAND,0},
   {"^",41, CAROT,0},
   {"$",42,DOLLAR,0},
   {"@",43,ATSIGN,0},
   {"~",44,TILDA,0},
   {"`",45,FQUOTE,0},
   {":",46,COLON,0},
   {" ",47,SPACE,0},
   {"	",48,TAB,0},
   {"%",49,PERCENT,0}
};
#define TOKENSDEFINED 50

void initToken(LexerToken* token);
LexerToken tokenForType(const enum _tokenType type);
LexerToken tokenForLexeme(char* lexeme);
char* lexemeForType(const enum _tokenType type);
int tokensMatch(LexerToken one, LexerToken two);

void initTokenStack(LStack* stack);
void pushTokenStack(LStack* stack, LexerToken token);
LexerToken peekTokenStack(LStack* stack);
LexerToken popTokenStack(LStack* stack);

#define initTokenStream(stream) initTokenStack(&((stream)->stack))
void deleteToken(LexerToken token);
#endif

