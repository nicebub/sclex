/**
	This file included the code of the parser that translates
	the definitions, portion of the specification file. It reads the input
	stream through the buffer and creates a parse tree of all the regular 
	expressions it finds until the end of the definitions section.
*/
#include "../include/translation.h"
#include "basevector.h"
#include "intvector.h"
#include "chrvector.h"

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
    file->fpos = new_int_vector(SETSIZE);
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
    for(r=0;r<vector_size(file->fpos);r++){
	   *get_by_index_in_vector(file->fpos,r) = new_int_set(vector_size(file->fpos));
	   if(*(int_vector**)get_by_index_in_vector(file->fpos,r) == NULL){
		  lex_error(5);
		  return NULL;
	   }
    }
}
	/* still initializing more of the firstpos sets */
{
	int r;
    for(r=vector_size(file->fpos);r<SETSIZE;r++)
	   *(int_vector**)get_by_index_in_vector(file->fpos,r) = NULL;
}
    set_vector_used(file->fpos,vector_size(file->fpos));
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
    display_set(file->tree->alphabet);
    printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");

	/* return the entire constructed parse tree structure or potentially NULL if 
		we found some error along the way */
    return file->tree;

}
