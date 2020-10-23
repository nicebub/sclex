#include "sclex.h"
#include "Parser.h"
#include "lex_error.h"
#include "gen.h"
int main(int argc, const char **argv) {
	static Io programIO;
	static struct _DFA *dfa;		/* DFA structure pointer to point to DFA record created with this lexer */

	dfa = NULL;			/* Initialize Variables */
	initIO(&programIO);

  if (argc != ARGUMENTS_NEEDED) { /* Expecting 1 argument plus the executable name only */
    lex_error(SCERR_NEED_ARGUMENT);
    exit(EXIT_FAILURE);
  }  
  initializeParserWithArgument(&programIO,(char*)argv[FILENAME_ARG]);
  parseInputFile(&programIO); /* parse input file, name given as argument to executable*/
  
  if(canGenerateDFA(&programIO)){
	dfa = generate_dfa(&programIO);
	generate_output(programIO.lexfile, dfa);
  }

  return CleanupMemory(&programIO,&dfa); /* return success on memory cleanup success or warning otherwise */
}

void initIO(Io* programIO){
    programIO->c = '\0';
    init_base_buffer(&(programIO->inputBuffer));
	initLexer(&programIO->own_lexer);
    programIO->lexfile.defbuf = NULL;
    programIO->lexfile.defs = NULL;
    programIO->lexfile.tree = NULL;
    programIO->lexfile.fpos = NULL;
    programIO->lexfile.decs = NULL;
    programIO->lexfile.aux = NULL;
	
}
inline void initializeParserWithArgument(Io* programIO,char* arg){
	programIO->own_lexer.inputBuffer = *buffer_from_filename(arg);/* initialize buffer from filename given */	
}
inline int canGenerateDFA(Io* programIO){
  return regularExpressionTreeArrayExists(&programIO) && firstPositionSetExists(&programIO);
}	
inline int regularExpressionTreeArrayExists(Io* inIO){
	return inIO->lexfile.tree != NULL;
}
inline int firstPositionSetExists(Io* inIO){
	return inIO->lexfile.fpos != NULL;
}
int CleanupMemory(Io* programIO, struct _DFA** dfa){

    int count;
  /* release memory buffer */
  delete_buffer(&programIO->inputBuffer);
  /* release declarations portion of spec file */
  free(programIO->lexfile.decs);
  programIO->lexfile.decs = NULL;
  /* release included C code attached to each regular expression definition */
  for (count = 0; count < programIO->lexfile.num_defs; count++) {
	 if(programIO->lexfile.defbuf[count]){
		delete_buffer(programIO->lexfile.defbuf[count]);
		programIO->lexfile.defbuf[count] = NULL;
	 }
  }
  free(programIO->lexfile.defbuf);
  programIO->lexfile.defbuf = NULL;
  /* release parse tree */
  delete_ta(programIO->lexfile.tree);
  /* release firstpos sets */
  delete_vector(programIO->lexfile.fpos);
  /* release DFA table constructed */
  delete_dfa(*dfa);
  *dfa = NULL;
  programIO->lexfile.fpos = NULL;
  programIO->lexfile.tree = NULL;
/*  programIO->inputBuffer = NULL;*/
  return EXIT_SUCCESS;
}
#undef ARGUMENTS_NEEDED
#undef FILENAME_ARG

