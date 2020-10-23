#include "Parser.h"
#include "Lexer.h"
RegularExpressionTreeArray* parseInputFile(Io* programIO){
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
	if(!matchedNextToken(&programIO->own_lexer,OPEN_STARTER).lexeme){
		/*fail*/
		return NULL;
	}
	programIO->lexfile.decs = parseDeclarations(programIO);

	if(!matchedNextToken(&programIO->own_lexer,CLOSE_STARTER).lexeme){
		/*fail*/
		return NULL;
	}
	parseDefinitions(programIO);
	
	if(!matchedNextToken(&programIO->own_lexer,SECTION_STARTER).lexeme){
		/* fail */
		return NULL;
	}
    programIO->lexfile.tree = parseTranslations(programIO);

	if(matchedNextToken(&programIO->own_lexer,SECTION_STARTER).lexeme){
		/* optional aux */
		aux(programIO);
	}
	
	return NULL;
}

char* aux(Io* programIO){}

