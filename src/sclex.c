#include "sclex.h"
#include "Parser.h"
#include "lex_error.h"
#include "gen.h"
#include "log.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static inline int regularExpressionTreeArrayExists(Parser* parser);
static inline int firstPositionSetExists(Parser* parser);
static inline bool canGenerateDFA(Parser* parser);
static void initIO(Io* programIO);

int main(int argc, const char **argv)
{
   Io*    programIO = NULL;
   Parser*   parser = NULL;
   struct _DFA *dfa = NULL;  /* DFA structure pointer to point to DFA record created with this lexer */
   int          ret = EXIT_FAILURE;

   if (ARGUMENTS_NEEDED == argc)
   {
      /* Expecting 1 argument plus the executable name only */
      programIO = malloc(sizeof(*programIO));
      if( NULL != programIO)
      {
         initIO(programIO);

         parser = malloc(sizeof(*parser));
         if (NULL != parser)
         {
            initParserWithFilename(parser,(char*)argv[FILENAME_ARG]);
            parseInputFile(parser); /* parse input file, name given as argument to executable*/

            if(true == canGenerateDFA(parser))
            {
               dfa = generate_dfa(parser);
               generate_output(parser, dfa);

               ret = EXIT_SUCCESS;
            }

            /*  CleanupMemory(&programIO,&dfa); */
            free(parser);
            parser = NULL; 
         }
         else
         {
            LOG_ERROR("malloc failed%s","");
         }

         /* cleanup */
         free(programIO);
         programIO = NULL;
      }
      else
      {
         perror(NULL);
         LOG_ERROR("malloc failed");
      }
   }
   else
   {
      lex_error(SCERR_NEED_ARGUMENT);
   }

   return ret;
}

void initIO(Io* programIO)
{
   if(NULL != programIO)
   {
      memset(programIO,0,sizeof(*programIO));

      init_base_buffer(&(programIO->inputBuffer));
      initLexer(&programIO->own_lexer);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
}
static inline bool canGenerateDFA(Parser* parser)
{
   bool ret = false;
   if(NULL != parser)
   {
      ret = regularExpressionTreeArrayExists(parser) && firstPositionSetExists(parser); 
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }

    return ret;
}

static inline int regularExpressionTreeArrayExists(Parser* parser)
{
   int ret = -1;

   if (NULL != parser)
   {
      ret = (parser->parseTree != NULL);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
	return ret;
}
static inline int firstPositionSetExists(Parser* parser)
{
   int ret = -1;

   if (NULL != parser)
   {
      ret = (parser->fpos != NULL);
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
	return ret;
}
int CleanupMemory(Io* programIO, struct _DFA** dfa)
{
    int count = 0;
    int ret = -1;

   if (NULL != programIO)
   {
      /* release memory buffer */
      delete_buffer(&programIO->inputBuffer);
      /* release declarations portion of spec file */
      free(programIO->lexfile.decs);
      programIO->lexfile.decs = NULL;
      /* release included C code attached to each regular expression definition */
      if (NULL != programIO->lexfile.defbuf)
      {
         for (count = 0; count < programIO->lexfile.num_defs; count++)
         {
	         if(NULL != programIO->lexfile.defbuf[count])
            {
               delete_buffer(programIO->lexfile.defbuf[count]);
               programIO->lexfile.defbuf[count] = NULL;
	         }
         }

         free(programIO->lexfile.defbuf);
         programIO->lexfile.defbuf = NULL;
      }

     /* release parse tree */
      delete_ta(programIO->lexfile.tree);
      programIO->lexfile.tree = NULL;

      /* release firstpos sets */
      delete_vector(programIO->lexfile.fpos);
      programIO->lexfile.fpos = NULL;

   }

   if(NULL != dfa && *dfa != NULL)
   {
      delete_dfa(*dfa);
      *dfa = NULL;
   }

   ret = EXIT_SUCCESS;

   return ret;
}
#undef ARGUMENTS_NEEDED
#undef FILENAME_ARG

