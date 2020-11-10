%{
#include <stdio.h>
#include "scy.tab.h"*/
	/* declarations */
	int a;
%}

number [0-9]+.?|[0-9]*.[0-9]+
singles [\+\*\)\(-\/]
%%
[ ] { }
{number} { sscanf(sctext, "%lf",&yylval); return NUMBER;}
[\n] { return NEWLINE; }
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
		case '-':
			return MINUS;
		case '/':
			return DIV;
	}
}
%%
