#include "../include/sclex_driver.h"
#ifdef __STRICT_ANSI__
#define inline
#endif

#define ARGUMENTS_NEEDED 2
#define FILENAME_ARG 1

struct AST* parseInputFile(Io* programIO);
void MemoryCleanup(Io* programIO, struct _DFA** dfa);
char* aux(Io* programIO);

void initIO(Io* programIO){
    programIO->c = '\0';
    init_base_buffer(&(programIO->inputBuffer));
    programIO->lexfile.defbuf = NULL;
    programIO->lexfile.defs = NULL;
    programIO->lexfile.tree = NULL;
    programIO->lexfile.fpos = NULL;
    programIO->lexfile.decs = NULL;
    programIO->lexfile.aux = NULL;
	
}
inline int ASTExists(Io* inIO){
	return inIO->lexfile.tree != NULL;
}
inline int firstPositionSetExists(Io* inIO){
	return inIO->lexfile.fpos != NULL;
}

int main(int argc, const char **argv) {
	static Io programIO;
  struct _DFA *dfa;		/* DFA structure pointer to point to DFA record created with this lexer */
  dfa = NULL;			/* Initialize Variables */
  initIO(&programIO);

  if (argc != ARGUMENTS_NEEDED) { /* Expecting 1 argument plus the executable name only */
    lex_error(SCERR_NEED_ARGUMENT);
    exit(EXIT_FAILURE);
  }
  
  programIO.inputBuffer = *buffer_from_filename(argv[FILENAME_ARG]);/* initialize buffer from filename given */

  parseInputFile(&programIO); /* parse input file, name given as argument to executable*/
  
  if(ASTExists(&programIO) && firstPositionSetExists(&programIO)){
	dfa = generate_dfa(&programIO);
	generate_output(&programIO, dfa);
  }

  MemoryCleanup(&programIO,&dfa);
  return EXIT_SUCCESS;
}
#undef ARGUMENTS_NEEDED
#undef FILENAME_ARG
inline void pass_ws(IO* programIO){
    while ((is_ws(programIO->c) || programIO->c == '\n')
      programIO->c = getchar(programIO->inputBuffer);	
}
/*#define pass_ws()                                                              \
  while ((is_ws(*current_char)) || *current_char == '\n')                 \
    *current_char = getchar(inputBuffer);*/
#define check_for(sign, error)                                                 \
  pass_ws(programIO);															\
  if (programIO->c != sign) {                                                 \
    lex_error(error);                                                          \
    return NULL;                                                               \
  }

  struct AST* parseInputFile(/*with io*/Io* programIO){
  /* If not at and of file already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
  if (programIO->c != EOF){
	  programIO->c = getchar(programIO->inputBuffer);
	  if(programIO->c != EOF) {
		  check_for('%', SCERR_DECL_UNDECLARED);
    	  programIO->c = getchar(programIO->inputBuffer);
    	  check_for('{', SCERR_DECL_UNDECLARED);
    /* Parse the declarations section of the spec file and store
               the short-hand declarations to use later
    */
    	  programIO->lexfile->decs = declarations(programIO);
    /* Look for delimiters or exit with an error */
/*		  pass_ws();*/
		  check_for('%', SCERR_MUST_USE_SEPR);
		  programIO->c = getchar(programIO->inputBuffer);
		  check_for('%', SCERR_MUST_USE_SEPR);
		  programIO->c = getchar(programIO->inputBuffer);
		  pass_ws();
		  programIO->c = ungetchar(programIO->inputBuffer);

    /* Parse the regular expressions and return the parse tree
               created of all the regular expressions combined
    */
    programIO->lexfile->tree = translations(programIO);

    /* Look for delimiters or exit with an error */
/*    pass_ws();*/
    check_for('%', SCERR_SEPR_AFTER_TRANS);
    programIO->c = getchar(programIO->inputBuffer);
    check_for('%', SCERR_SEPR_AFTER_TRANS);
  }}
  return NULL;
}
/*#undef pass_ws*/
#undef check_for

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
/*
        void cleanup_lex(buffer** mbuf,struct _lfile* lexfile,struct _DFA**
dfa){

Functionality: Clean up and release all memory used and closing and releasing
        all files that were opened and pointers attained
*/
/*void cleanup_lex(buffer **mbuf, struct _lfile *lexfile, struct _DFA **dfa) {*/
void MemoryCleanup(Io* programIO, struct _DFA** dfa){

    int y;
  /* release memory buffer */
  delete_buffer(programIO->inputBuffer);
  /* release declarations portion of spec file */
  free(programIO->lexfile->decs);
  programIO->lexfile->decs = NULL;
  /* release included C code attached to each regular expression definition */
  for (y = 0; y < programIO->lexfile->num_defs; y++) {
	 if(programIO->lexfile->defbuf[y]){
		delete_buffer(programIO->lexfile->defbuf[y]);
		programIO->lexfile->defbuf[y] = NULL;
	 }
  }
  free(programIO->lexfile->defbuf);
  programIO->lexfile->defbuf = NULL;
  /* release parse tree */
  delete_ta(programIO->lexfile->tree);
  /* release firstpos sets */
  delete_vector(programIO->lexfile->fpos);
  /* release DFA table constructed */
  delete_dfa(*dfa);
  *dfa = NULL;
  programIO->lexfile->fpos = NULL;
  programIO->lexfile->tree = NULL;
  programIO->inputBuffer = NULL;
}
