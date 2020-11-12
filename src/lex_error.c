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
/*0*/	   "Can't open file for writing: sclex.yy.c",
/*1*/	   "Must start with a declaration sections starting with %{",
/*2*/	   "Must use %% separator after definitions and before the translations",
/*3*/	   "Must use %% separator after the translations are done",
/*4*/	   "Couldn't create new file->fpos",
/*5*/	   "Couldn't create new set",
/*6*/	   "Couldn't create new ta in regexpset as full tree",
/*7*/	   "Is this an error:??? temp is NULL in regexpset",
/*8*/	   "Couldn't create new # node",
/*9*/	   "Couldn't create new CONCAT node",
/*10*/	   "Couldn't create new OR node",
/*11*/	   "Newline , EOF or NULL detected before { action }",
/*12*/	   "Couldn't create new expr node",
/*13*/	   "Expecting right  bracket",
/*14*/	   "Expecting right parens",
/*15*/	   "Couldn't create new STAR",
/*16*/	   "Couldn't create new PLUS",
/*17*/	   "Couldn't create new QUESTION",
/*18*/	   "Couldn't create new RANGE node",
/*19*/	   "Couldn't create new COMMA node",
/*20*/	   "Couldn't create new REPS node",
/*21*/	   "Couldn't create new charset inner node",
/*22*/	   "Error: can't have whitespace in character set",
/*23*/	   "Couldn't create new ALPHAUM/PRINTABLE",
/*24*/	   "Couldn't create new OR node in charset",
/*25*/	   "Couldn't create new CHARSET char node",
/*26*/	   "Please supply one argument: the lex file.",
/*27*/	   "Could not created ESCAPE CHAR node",
/*28*/	   "Declaration section must end with %}"
    };
	/* check to see if in array bounds */
    if(en <0 || en >28)
	   return;
    printf("%s\n",err_strings[en]);
}
