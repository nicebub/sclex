#include "lex_error.h"

void lex_error(int en){
    const static char * err_strings[] = {
	   "can't open file for writing: sclex.yy.c",
	   "Declarations sections must be declared",
	   "Must use %% separator and have defintions written",
	   "Must use %% separator after the translations are done",
	   "couldn't create new file->fpos",
	   "couldn't create new set",
	   "couldn't create new ta in regexpset as full tree",
	   "is this an error:??? temp is NULL in regexpset",
	   "couldn't create new # node",
	   "couldn't create new CONCAT node",
	   "couldn't create new OR node",
	   "newline , EOF or NULL detected before { action }",
	   "couldn't create new expr node",
	   "expecting right  bracket",
	   "expecting right parens",
	   "couldn't create new STAR",
	   "couldn't create new PLUS",
	   "couldn't create new QUESTION",
	   "couldn't create new RANGE node",
	   "couldn't create new COMMA node",
	   "couldn't create new REPS node",
	   "couldn't create new charset inner node",
	   "error: can't have whitespace in character set",
	   "couldn't create new ALPHAUM/PRINTABLE",
	   "couldn't create new OR node in charset",
	   "couldn't create new CHARSET char node",
	   "please supply one argument: the lex file.",
	   "could not created ESCAPE CHAR node"
    };
    if(en <0 || en >26)
	   return;
    printf("%s\n",err_strings[en]);
}
