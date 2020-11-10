/**

The _lfile struct is symbolic for the lexer file that will
ultimately be the finished product from the generator. As we
parse the input stream and create a parse tree to represent the
regular expressions read, then we also create other data structures
and accumulate other data to make a final output source file.

*/
#ifndef MLFILE_H
#define MLFILE_H

#include "basebuffer.h"
#include "tree.h"
#include "baseset.h"
#include "intset.h"
#include "chrset.h"
#include "basevector.h"
#include "intvector.h"
#include "Lexer.h"
/** Structure Definition

    buffer **defbuf: Store a memory address to a pointer to a buffer used in buffering
		the input stream of a source file

    char ** defs: A character string array for storing all the definitions code for each
		regular expression definition found

    struct _ta *tree: The full parse tree after reading all the regular expression definitions
		through the input stream buffer

    struct _iseta *fpos: A pointer to an array of sets of integers representing the finalpos
	 	sets of each regular expression definition.

    char * decs: A character string that represents the actual regular expression read in

    char * aux: This will eventually be implemented as a character string array to be copied
		into the source code file output at the end.

    int num_defs:  The number of regular expression definitions we have found throughout the
		specification file


*/

typedef struct _lfile Output;
struct _lfile {
    Buffer **defbuf;
    char ** defs;
    struct _ta *tree;
    base_vector *fpos; /* int_vector* */
    char * decs;
    char * aux;
    int num_defs;
};

typedef struct _io Io;
struct _io {
	Lexer own_lexer;
	Output lexfile;
	Buffer inputBuffer;
	char c; /* current character in input */
};

void initIO(Io* inIO);
int ASTExists(Io* inIO);
/*int firstPositionSetExists(Io* inIO);*/
#endif
