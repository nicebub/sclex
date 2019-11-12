/**
	lex_error() is the universal error printing function
		that makes the rest of the source code look more clean
		and simple.
*/
#include "../include/lex_error.h"

void lex_error(int en){

/* An array of error strings to print in case of error */
    const static char * err_strings[] = {
	   "ERR0:can't open file for writing: sclex.yy.c",
	   "ERR1:Declarations sections must be declared",
	   "ERR2:Must use %% separator and have defintions written",
	   "ERR3:Must use %% separator after the translations are done",
	   "ERR4:couldn't create new file->fpos",
	   "ERR5:couldn't create new set",
	   "ERR6:couldn't create new ta in regexpset as full tree",
	   "ERR7:is this an error:??? temp is NULL in regexpset",
	   "ERR8:couldn't create new # node",
	   "ERR9:couldn't create new CONCAT node",
	   "ERR10:couldn't create new OR node",
	   "ERR11:newline , EOF or NULL detected before { action }",
	   "ERR12:couldn't create new expr node",
	   "ERR13:expecting right  bracket",
	   "ERR14:expecting right parens",
	   "ERR15:couldn't create new STAR",
	   "ERR16:couldn't create new PLUS",
	   "ERR17:couldn't create new QUESTION",
	   "ERR18:couldn't create new RANGE node",
	   "ERR19:couldn't create new COMMA node",
	   "ERR20:couldn't create new REPS node",
	   "ERR21:couldn't create new charset inner node",
	   "ERR22:error: can't have whitespace in character set",
	   "ERR23:couldn't create new ALPHAUM/PRINTABLE",
	   "ERR24:couldn't create new OR node in charset",
	   "ERR25:couldn't create new CHARSET char node",
	   "ERR26:please supply one argument: the lex file.",
	   "ERR27:could not created ESCAPE CHAR node"
    };
	/* check to see if in array bounds */
    if(en <0 || en >27)
	   return;
    printf("%s\n",err_strings[en]);
}
