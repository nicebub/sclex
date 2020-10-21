%{
#include <stdio.h>
	/* declarations */
	int a;
#define IDENT 0
#define INTEGER 1
#define EQUALS 2
#define SEMICOLON 3
#define SYMBOL 4
#define RELATION 5
#define STRING 6
#define LPAREN 7
#define RPAREN 8
#define LCBRA 9
#define RCBRA 10
#define LBRA 11
#define RBRA 12
#define COMMA 13
#define LESS 14
#define GREAT 15
#define EQAL 16
#define PLUS 17
#define MINS 18
#define FORW 19
#define STAR 20
#define GRE 21
#define LTE 22
#define NEQ 23
#define EQUIV 24
#define ADDRESS 25
#define ELIP 26

%}

letter ([a-z]|[A-Z]|_)
digit [0-9]
nonzero [1-9]
ident {letter}({letter}|{digit})*
ws [ \t\n]
witho [ \t]
singles [\(\)\{\};,<>=+-\/\*&]
doubles (>=)|(<=)|(!=)|(==)|(\.\.\.)
integer (0|({nonzero}{digit}*))
squote 	\"
literal {squote}({singles}|{doubles}|{ident}|\%|\\|{witho})*{squote}


%%
{ws}+ {
	printf("eating up whitespace, space, tabs and newlines\n");
}

{singles} {
	printf("found %s with length %d\n",sctext,scleng);
	switch(sctext[0]){
		case '(':
			return LPAREN;
		case ')':
			return RPAREN;
		case '{':
			return LCBRA;
		case '}':
			return RCBRA;
		case '[':
			return LBRA;
		case ']':
			return RBRA;
		case ';':
			return SEMICOLON;
		case ',':
			return COMMA;
		case '<':
			return LESS;
		case '>':
			return GREAT;
		case '=':
			return EQAL;
		case '+':
			return PLUS;
		case '-':
			return MINS;
		case '/':
			return FORW;
		case '*':
			return STAR;
		case '&':
			return ADDRESS;
		
	}
	return SYMBOL;
}

{doubles} {
	printf("found %s with length %d\n",sctext,scleng);
	switch(sctext[0]){
		case '>':
			return GRE;
		case '<':
			return LTE;
		case '!':
			return NEQ;
		case '=':
			return EQUIV;
		case '.':
			return ELIP;		
	}
	
	return RELATION;	
}


{ident} {
	printf("found %s with length %d\n",sctext,scleng);	
	return IDENT;
}

{integer} {
	printf("found a digit yay, %s length of %d\n", sctext, scleng);
	return INTEGER;
}

{literal} {
	printf("hopefully found a string, %s of length %d\n",sctext,scleng);
	return STRING;
}


%%
