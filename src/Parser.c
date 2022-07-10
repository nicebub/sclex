#include <string.h>
#include "Parser.h"
#include "Lexer.h"
#include "lex_error.h"

#ifdef __STRICT_ANSI__
#define inline
#endif


void initParser(Parser* parser)
{
   memset(parser,0,sizeof(*parser));
	initLexer(&parser->lexer);
}

void swapBuffer(Parser* parser, Buffer* buffer)
{
    parser->lexer.inputBuffer = buffer;
    getNextChar(&parser->lexer);
}

extern inline int initParserWithFilename(Parser* parser,char* arg)
{
   Buffer* buf = NULL;
   int     ret = EXIT_FAILURE;

   if(NULL != parser && NULL != arg)
   {
      initParser(parser);

      buf = buffer_from_filename(arg);/* initialize buffer from filename given */
      if(!buf)
      {
         perror("\033[0;31merror\033[0m");
      }
      else
      {
         LOG_0("we made it here");
         parser->lexer.inputBuffer = buf;
         parser->fileBuffer = buf;

         /* have to prime the lexer */
         getNextChar(&parser->lexer);

         ret = EXIT_SUCCESS;
      }
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }

   return ret;
}

RegularExpressionTreeArray* parseInputFile(Parser* parser)
{
   if(NULL == parser)
   {
      return NULL;
   }
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
/*	if(!matchedNextToken(&parser->lexer,OPEN_STARTER).lexeme){*/
	if(!matchToken(&parser->lexer,tokenForType(OPEN_STARTER)).lexeme)
   {
      LOG_0("found token <%s>\n",parser->lexer.tokens.stack.top->lexeme);
		/*fail*/
		lex_error(SCERR_DECL_UNDECLARED);
		return NULL;
	}
	parser->decs = parseDeclarations(parser);

	if(!matchToken(&parser->lexer,tokenForType(CLOSE_STARTER)).lexeme)
   {
		/*fail*/
		lex_error(SCERR_NO_CLOSE_SECTION);
		return NULL;
	}
/*    pass_ws(&parser->lexer);*/
	parseDefinitions(parser);
	
	if(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme)
   {
		/* fail */
		lex_error(SCERR_MUST_USE_SEPR);
		return NULL;
	}
    parser->parseTree = parseTranslations(parser);

	if(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme)
   {
		/* fail */
		lex_error(SCERR_SEPR_AFTER_TRANS);
		return NULL;
		
	}
	/* optional aux */
	aux(parser);
	
	return NULL;
}

char* aux(Parser* parser)
{
   const char * ret = NULL;
   if(NULL != parser)
   {
      ret = "SUCCESS";
   }
	return (char*)ret;
}

