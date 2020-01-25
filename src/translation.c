/**
	This file included the code of the parser that translates
	the definitions, portion of the specification file. It reads the input
	stream through the buffer and creates a parse tree of all the regular 
	expressions it finds until the end of the definitions section.
*/
#include "../include/translation.h"

/**  

	struct _ta* translations(buffer* mbuf, char*c, struct _lfile *file)

Functionality: The function of the parser that recognizes and translates
	into an entire parse tree for the whole definitions part of the spec-
	ifications file. 

Parameters: buffer* mbuf: an initialiazed buffer
			char * c: the current input character
			struct _lfile* file: a pointer to an _lfile structure used
				to hold various data structures shared around the program

Returns: A pointer to a tree structure that for one holds the entire parse
	tree of all the regular expressions, combined. 

Results: The input stream is parsed for definitions and code and the parse
	tree is constructed, the source code is read and held to be associated
	later, and it is finally returned in a struct _ta.
*/
struct _ta* translations(buffer* mbuf, char*c, struct _lfile *file){
	/* call the rexexpset() function that parses the input for more than
		one regular expression definition any their associated code sections
	*/
    file->tree = regexpset(mbuf,c,file);
	/* create the initial firpos set for a set amount of  regular expressions */
    file->fpos = create_iseta(SETSIZE);
	/* if memory error or something else thing print an error to standard
		output and return NULL */
    if(file->fpos == NULL){
	   lex_error(4);
	   return NULL;
    }
	/* initialize each regular expressions' firstpos set or print an error and
		return NULL if issues arise */
	{
		int r;
    for(r=0;r<file->fpos->size;r++){
	   file->fpos->iset[r] = create_iset(file->fpos->size);
	   if(file->fpos->iset[r] == NULL){
		  lex_error(5);
		  return NULL;
	   }
    }
}
	/* still initializing more of the firstpos sets */
{
	int r;
    for(r=file->fpos->size;r<SETSIZE;r++)
	   file->fpos->iset[r] = NULL;
}
    file->fpos->used = file->fpos->size;
	/* Currently just some debugging information and construction statistics */
    printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");
	{
		int h;
    for(h=0;h<file->tree->used;h++){
		  printf("REGEX\n");
		  display_tree(file->tree->t[h]);
		  printf("\n");
    }
}
    printf("\n");

	/* create the entire followpos set on the entire tree of regular expressions */
    followpos(&file->fpos,&file->tree->atop);

    printf("\n");
    printf("ITS ALPHABET\n");
    display_set(file->tree->alphabet,1);
    printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");

	/* return the entire constructed parse tree structure or potentially NULL if 
		we found some error along the way */
    return file->tree;

}
