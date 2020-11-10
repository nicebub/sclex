#include "Parser.h"
#include "Lexer.h"
#include "lex_error.h"

#ifdef __STRICT_ANSI__
#define inline
#endif


void initParser(Parser* parser){
	initLexer(&parser->lexer);
/*	initTokenStream(&parser->tokens);*/
	parser->parseTree=NULL;
	parser->defs=NULL;
	parser->decs=NULL;
    parser->fpos = NULL;
    parser->definitionList = NULL;
/*    parser->definitionBuffer = NULL;*/
	parser->aux=NULL;
	parser->num_defs=0;
    parser->fileBuffer = NULL;
	
}

void swapBuffer(Parser* parser, Buffer* buffer){
    parser->lexer.inputBuffer = buffer;
    getNextChar(&parser->lexer);
}

inline void initParserWithFilename(Parser* parser,char* arg){
    Buffer* buf;
	initParser(parser);
	buf = buffer_from_filename(arg);/* initialize buffer from filename given */
	if(!buf){
		perror("\033[0;31merror\033[0m");
		exit(EXIT_FAILURE);
	}
    parser->lexer.inputBuffer = buf;
    parser->fileBuffer = buf;
    getNextChar(&parser->lexer);
}

RegularExpressionTreeArray* parseInputFile(Parser* parser){
  /* If not at End Of File already, look for spec file section delimiters.
          if they aren't there then return an error and exit
  */
/*	if(!matchedNextToken(&parser->lexer,OPEN_STARTER).lexeme){*/
	if(!matchToken(&parser->lexer,tokenForType(OPEN_STARTER)).lexeme){
		/*fail*/
		lex_error(SCERR_DECL_UNDECLARED);
		return NULL;
	}
	parser->decs = parseDeclarations(parser);

	if(!matchToken(&parser->lexer,tokenForType(CLOSE_STARTER)).lexeme){
		/*fail*/
		lex_error(SCERR_MUST_USE_SEPR);
		return NULL;
	}
/*    pass_ws(&parser->lexer);*/
	parseDefinitions(parser);
	
	if(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme){
		/* fail */
		lex_error(SCERR_MUST_USE_SEPR);
		return NULL;
	}
    parser->parseTree = parseTranslations(parser);

	if(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme){
		/* fail */
		lex_error(SCERR_SEPR_AFTER_TRANS);
		return NULL;
		
	}
	/* optional aux */
	aux(parser);
	
	return NULL;
}

char* aux(Parser* parser){
	return NULL;
}

