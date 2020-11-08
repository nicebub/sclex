#include <string.h>
#include "Parser.h"
#include "Lexer.h"

#define NUM_DEFINITIONS 50
#define NAMELENGTH 25
#define EXPRESSIONLENGTH 300

char* parseDeclarations(Parser* parser){
	char* declarations;
	declarations = NULL;
	declarations = readRawStringUntilToken(&parser->lexer, tokenForType(CLOSE_STARTER));
	pushBackLastToken(&parser->lexer,tokenForType(CLOSE_STARTER));
	return declarations;
}
Definition* definitionExists(Parser* parser,LexerToken name){
	int counter;
	for(counter=0;counter<parser->num_defs;counter++)
		if(strcmp(name.lexeme,parser->definitionList[counter].name.lexeme)==0)
			return &parser->definitionList[counter];
	return NULL;
}
void parseDefinitions(Parser* parser){
	LexerToken name;
/*    int counter;*/
	setupdefinitionList(parser);

	while(!matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme){
		initNextDefinition(parser);
		name = matchToken(&parser->lexer,tokenForType(IDENTIFIER));
		if(definitionExists(parser,name)){
   			 printf("definition already exists or name already taken\n");
				 while(!isNewline(&parser->lexer))
					 getNextChar(&parser->lexer);
		}
		else{
		    pass_ws(&parser->lexer);
			parseDefinitionValue(parser,name);
		}
	}
    pushBackLastToken(&parser->lexer,tokenForType(SECTION_STARTER));
/*    parser->definitionBuffer = malloc(sizeof(Buffer*)*parser->num_defs);*/
/*    for(counter=0;counter<parser->num_defs;counter++)
	   parser->definitionBuffer[counter] = buffer_from_string(parser->definitionList[counter].expression);*/
/*
	   parser->defbuf = malloc(sizeof(Buffer*)*parser->num_defs);
  {
	  int y;
	  for(y=0;y<parser->num_defs;y++)
	 	 parser->defbuf[y] = buffer_from_string(parser->defs[(2*y)+1]);
  }
  */
}
void setupdefinitionList(Parser* parser){
	int counter;
/*	int numDefinitions=0;*/
	parser->definitionList = malloc(sizeof(Definition)*NUM_DEFINITIONS);
	for(counter=0;counter<NUM_DEFINITIONS;counter++){
		parser->definitionList[counter].name = tokenForType(IDENTIFIER);
		parser->definitionList[counter].expression = NULL;
	    parser->definitionList[counter].buffer = NULL;
	}
}
void initNextDefinition(Parser* parser){
	int counter;
	parser->definitionList[parser->num_defs].name.lexeme = malloc(sizeof(char)*NAMELENGTH);
	parser->definitionList[parser->num_defs].expression = malloc(sizeof(char)*EXPRESSIONLENGTH);
	for(counter=0;counter<NAMELENGTH-2;counter++)
			parser->definitionList[parser->num_defs].name.lexeme[counter] = ' ';
	parser->definitionList[parser->num_defs].name.lexeme[NAMELENGTH-1] = '\0';
	for(counter=0;counter<EXPRESSIONLENGTH-2;counter++)
			parser->definitionList[parser->num_defs].expression[counter] = ' ';
	parser->definitionList[parser->num_defs].expression[NAMELENGTH-1] = '\0';
}
void parseDefinitionValue(Parser* parser, LexerToken name){
	char accummulatedString[EXPRESSIONLENGTH];
	LexerToken tempToken;
	LexerToken match;
	char* currentLocation;
	currentLocation = &accummulatedString[0];
    parser->lexer.passWS = 0;
	do{
		if(matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme){
			pushBackLastToken(&parser->lexer,tokenForType(SECTION_STARTER));
			parser->lexer.passWS = 1;
			return;
		}
		else if(matchToken(&parser->lexer,tokenForType(LCURLY)).lexeme){
			if((match = matchToken(&parser->lexer,tokenForType(NUMBER))).lexeme){
			}
			else if((match = matchToken(&parser->lexer,tokenForType(IDENTIFIER))).lexeme) {
				Definition* def;
				def = NULL;
			    if((def=definitionExists(parser,match))){
				    *currentLocation = '(';
				    currentLocation++;
				    strncpy(currentLocation,def->expression,strlen(def->expression));
				    currentLocation += strlen(def->expression);
				    *currentLocation = ')';
				    currentLocation++;
				    getNextChar(&parser->lexer);				    
			    }
			}
		}
		else{
			/*keep storing string for later. */
			tempToken = getNextToken(&parser->lexer);
			/*add token to buffer to store*/
			strncpy(currentLocation,tempToken.lexeme,strlen(tempToken.lexeme));
			currentLocation += strlen(tempToken.lexeme);
		}
	}while(!isNewline(&parser->lexer));
    *currentLocation = '\0';
	 parser->definitionList[parser->num_defs].name = name;
	 strncpy(parser->definitionList[parser->num_defs].expression,accummulatedString,strlen((const char*)&accummulatedString)+1);
    parser->definitionList[parser->num_defs].buffer = buffer_from_string(parser->definitionList[parser->num_defs].expression);
	 parser->num_defs++;
    parser->lexer.passWS = 1;
 }
#undef NUM_DEFINITIONS
#undef NAMELENGTH
#undef EXPRESSIONLENGTH
