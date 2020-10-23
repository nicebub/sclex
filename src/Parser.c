#include "Parser.h"
#include "Lexer.h"
RegularExpressionTreeArray* parseInputFile(Io* programIO){
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
	if(!matchedNextToken(&programIO->own_lexer,OPEN_STARTER)){
		/*fail*/
	}
	programIO->lexfile.decs = parseDeclarations(programIO);

	if(!matchedNextToken(&programIO->own_lexer,CLOSE_STARTER)){
		/*fail*/
	}
	parseDefinitions(programIO);
	
	if(!matchedNextToken(&programIO->own_lexer,SECTION_STARTER)){
		/* fail */
	}
    programIO->lexfile.tree = parseTranslations(programIO);

	if(matchedNextToken(&programIO->own_lexer,SECTION_STARTER)){
		/* optional aux */
		aux(programIO);
	}
	
	return NULL;
}


/*
        char* aux(buffer* mbuf, char*c){

Functionality; To include all the code found in the auxilary
        portion of the specification file. Currently its unimplemented
*/
/*
char *aux(buffer *mbuf, char *c) { return NULL; }
*/
/* DEBUG Function for displaying memory usage */
/*
void display_memstats(void) {
  int tnm = tnum_created();
  printf("+--------------------------------------------------------------------"
         "-------------------+\n");
  printf("+ value		|	ta	|	t	|	"
         "sa	|	s		+\n");
  printf("+ created	|	%d	|	%d	|	%d	"
         "|	%d		+\n",
         atnum_created(), tnm, asnum_created(), snum_created());
  printf("+ deleted	|	%d	|	%d	|	%d	"
         "|	%d		+\n",
         atnum_deleted(), tnum_deleted(), asnum_deleted(), snum_deleted());
  printf("+Total Loss	|	%d	|	%d	|	%d	"
         "|	%d		+\n",
         atnum_created() - atnum_deleted(), tnm - tnum_deleted(),
         asnum_created() - asnum_deleted(), snum_created() - snum_deleted());
  printf("+--------------------------------------------------------------------"
         "-------------------+\n");
  printf("*note - ta is tree arrays, t are tree nodes, sa are set \n");
  printf("*note - arrays, and s are sets themselvese\n\n");
}
*/
