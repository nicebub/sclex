/**
	lex_error() is the universal error printing function
		that makes the rest of the source code look more clean
		and simple.
*/
#include <stdio.h>
#include "../include/lex_error.h"

void lex_error(int en){

/* An array of error strings to print in case of error */
    const static char * err_strings[] = {
/*0*/	   "ERR0:can't open file for writing: sclex.yy.c",
/*1*/	   "ERR1:Declarations sections must be declared",
/*2*/	   "ERR2:Must use %% separator and have defintions written",
/*3*/	   "ERR3:Must use %% separator after the translations are done",
/*4*/	   "ERR4:couldn't create new file->fpos",
/*5*/	   "ERR5:couldn't create new set",
/*6*/	   "ERR6:couldn't create new ta in regexpset as full tree",
/*7*/	   "ERR7:is this an error:??? temp is NULL in regexpset",
/*8*/	   "ERR8:couldn't create new # node",
/*9*/	   "ERR9:couldn't create new CONCAT node",
/*10*/	   "ERR10:couldn't create new OR node",
/*11*/	   "ERR11:newline , EOF or NULL detected before { action }",
/*12*/	   "ERR12:couldn't create new expr node",
/*13*/	   "ERR13:expecting right  bracket",
/*14*/	   "ERR14:expecting right parens",
/*15*/	   "ERR15:couldn't create new STAR",
/*16*/	   "ERR16:couldn't create new PLUS",
/*17*/	   "ERR17:couldn't create new QUESTION",
/*18*/	   "ERR18:couldn't create new RANGE node",
/*19*/	   "ERR19:couldn't create new COMMA node",
/*20*/	   "ERR20:couldn't create new REPS node",
/*21*/	   "ERR21:couldn't create new charset inner node",
/*22*/	   "ERR22:error: can't have whitespace in character set",
/*23*/	   "ERR23:couldn't create new ALPHAUM/PRINTABLE",
/*24*/	   "ERR24:couldn't create new OR node in charset",
/*25*/	   "ERR25:couldn't create new CHARSET char node",
/*26*/	   "ERR26:please supply one argument: the lex file.",
/*27*/	   "ERR27:could not created ESCAPE CHAR node"
    };
	/* check to see if in array bounds */
    if(en <0 || en >27)
	   return;
    printf("%s\n",err_strings[en]);
}
