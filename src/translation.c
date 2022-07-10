/**
	This file included the code of the parser that translates
	the definitions, portion of the specification file. It reads the input
	stream through the buffer and creates a parse tree of all the regular 
	expressions it finds until the end of the definitions section.
*/
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
/*
#include "basevector.h"
#include "intvector.h"
#include "chrvector.h"
*/
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
RegularExpressionTreeArray* parseTranslations(Parser* parser)
{
   RegularExpressionTreeArray* ret = NULL;
   int counter = 0;
	/* call the rexexpset() function that parses the input for more than
		one regular expression definition any their associated code sections
	*/
   if (NULL != parser)
   {
      parseRegularExpressionSet(parser);
   	/* create the initial firpos set for a set amount of  regular expressions */
      parser->fpos = new_int_vector_with_init_sets(SETSIZE,SETSIZE);
   	/* if memory error or something else thing print an error to standard
	   	output and return NULL */
      if(NULL != parser->fpos)
      {
         /* still initializing more of the firstpos sets */
         for(counter=vector_size(parser->fpos);counter<SETSIZE;counter++)
         {
      	/*   printf("setting extra to NULL\n");*/
      	   *(int_vector**)get_by_index_in_vector(parser->fpos,counter) = NULL;
         }
      /*    printf("checking fpos vector used and size: used: %d size: %d\n",vector_used(file->fpos),vector_size(file->fpos));*/
         set_vector_used(parser->fpos,vector_size(parser->fpos));
      /*	printf("checking fpos vector used and size: used: %d size: %d\n",vector_used(file->fpos),vector_size(file->fpos));*/
      	/* Currently just some debugging information and construction statistics */
        #ifdef DEBUG
          printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");
      	{
      		int h;
          for(h=0;h<parser->parseTree->used;h++)
          {
      		  printf("REGEX\n");
      		  display_tree(parser->parseTree->t[h]);
      		  printf("\n");
          }
      }
          printf("\n");
        #endif
      	/* create the entire followpos set on the entire tree of regular expressions */
         followpos(&parser->fpos,&parser->parseTree->atop);
        #ifdef DEBUG
          printf("\n");
          printf("ITS ALPHABET\n");
          display_set(parser->parseTree->alphabet);
          printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");
      
      	/* return the entire constructed parse tree structure or potentially NULL if 
      		we found some error along the way */
        #endif
         ret = parser->parseTree;
      }
      else
      {
	     lex_error(4);
      }
   }
   return ret;
}
   