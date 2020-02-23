%{
#include <stdio.h>
#include "scy.tab.h"
	/* declarations */
	int a;
%}

letter ([a-z]|[A-Z]|_)
digit [0-9]
nonzero [1-9]
ident {letter}({letter}|{digit})*
ws [ \t\n]
witho [ \t]
singles [\(\)+*]
integer (0|({nonzero}{digit}*))

%%
{ws}+ {
}

{singles} {
	switch(sctext[0]){
		case '*':
			return TIMES;
		case '+':
			return PLUS;
		case ')':
			return RPAREN;
		case '(':
			return LPAREN;
	}
}

{ident} {
//	yylval = sctext;
	return IDENT;
}

{integer} {
	yylval = atoi(sctext);
	return INTEGER;
}

%%
