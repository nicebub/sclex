#include <string.h>
#include <stdbool.h>
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
#include "log.h"

RegularExpressionTreeNode* parseExpression(Parser* parser)
{
	/* char_set** */
   struct _node *            temp = NULL;
   struct _node *           temp2 = NULL;
   struct _node *           temp3 = NULL;
   struct _node *           temp4 = NULL;
   char                         m = '\0';
   bool                 need_exit = false;

    /*
	can be an (expr) OR [range] OR expr OR expr* OR expr+ OR expr? OR expr{a,b} OR expr|expr
	*/

   setIndividualTokens(&parser->lexer,1);
   if(NULL != matchToken(&parser->lexer,tokenForType(LPAREN)).lexeme)
   {
	   temp = parseExpressionOR(parser);
	   if(NULL == matchToken(&parser->lexer,tokenForType(RPAREN)).lexeme)
      {
		  lex_error(14);
        need_exit = true;
	   }
   }
   else if(NULL != matchToken(&parser->lexer,tokenForType(LBRACKET)).lexeme)
   {
	   temp = parseCharSet(&parser->parseTree->alphabet,parser);
	   if(NULL == matchToken(&parser->lexer,tokenForType(RBRACKET)).lexeme)
      {
         lex_error(13);
         LOG_ERROR("to finish a character class%s","\n");
         need_exit = true;
		}
   }
   else if(NULL != matchToken(&parser->lexer,tokenForType(LCURLY)).lexeme)
   {
	   temp = apply_def(parser);

	   if(NULL == matchToken(&parser->lexer,tokenForType(RCURLY)).lexeme)
      {
		  lex_error(13);
		  LOG_ERROR("curly, to finish off a range%s, instead found %s\n","}",parser->lexer.tokens.stack.top->lexeme);
        need_exit = true;
	   }
   }
   else if(NULL != matchToken(&parser->lexer,tokenForType(BSLASH)).lexeme)
   {
      LOG_0("TOP OF STACK <%s>", parser->lexer.tokens.stack.top->lexeme);
	   temp = parseEscapeChars(parser);
	   if(NULL == temp)
      {
		  lex_error(27);
	   }
      else
      {
   	   add_to_set(&parser->parseTree->alphabet,temp->value);
      }
   }
   else
   {
	   m = *getNextToken(&parser->lexer).lexeme;
	   temp = create_node(m);
	   if(NULL == temp)
      {
		   lex_error(12);
	   }
      else
      {
         add_to_set(&parser->parseTree->alphabet,temp->value);
      }
   }
   setIndividualTokens(&parser->lexer,0);
   if(true == need_exit)
   {
      exit(-1);
   }

 /*   else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}*/
/*    if((isalphanum(parser->lexer.current_char) || isprintable(parser->lexer.current_char)) && (parser->lexer.current_char != '\\') ){
	   m = parser->lexer.current_char;
	   getNextChar(&parser->lexer);
	   temp = create_node(m);\
	   if(!temp){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(&parser->parseTree->alphabet,temp->value);
    }*/
/*    else{
	   	switch(parser->lexer.current_char){
		    case '\\':
			   temp = parseEscapeChars(parser);
			   if(!temp){
				  lex_error(27);
				  return NULL;
			   }
			   add_to_set(&parser->parseTree->alphabet,temp->value);
			   getNextChar(&parser->lexer);
			   break;
		  case '[':
			   getNextChar(&parser->lexer);
			   temp = parseCharSet(&parser->parseTree->alphabet,parser);
			   if(parser->lexer.current_char == ']'){
				  getNextChar(&parser->lexer);
			   	}
			   	else{
				    lex_error(13);
					printf("to finish a character class\n");
				    exit(-1);
	   			}
			   break;
		  case '(':
			   getNextChar(&parser->lexer);
			   pass_ws(&parser->lexer);
			   temp = parseExpressionOR(parser);
			   pass_ws(&parser->lexer);
			   if(parser->lexer.current_char == ')'){
				  getNextChar(&parser->lexer);
			   }
			   else{
			    	lex_error(14);
			    	exit(-1);
			   	}
			   break;
		    case '{':
			   getNextChar(&parser->lexer);
			   temp = apply_def(parser);
			   getNextChar(&parser->lexer);
			   if(parser->lexer.current_char == '}'){
				  getNextChar(&parser->lexer);
			   }
			   else{
				  lex_error(13);
				  printf("curly, to finish off a range\n");
				  exit(-1);
			   }
			   break;
    		}
    }*/
	   switch(parser->lexer.current_char)
      {
		  case '\n':
			 firstpos(&temp);
			 lastpos(&temp);
			 return temp;
			 break;
		  case '*':
			 temp2 = create_node((char)STAR);
			 if(NULL == temp2)
          {
				lex_error(15);
				return NULL;
			 }
			 temp2->left = temp;
			 getNextChar(&parser->lexer);
			 firstpos(&temp2);
			 lastpos(&temp2);
			 return temp2;
			 break;
		  case '+':
			 temp2 = create_node((char)PLUS);
			 if(NULL == temp2)
          {
				lex_error(16);
				return NULL;
			 }
			 temp2->left = temp;
			 getNextChar(&parser->lexer);
			 firstpos(&temp2);
			 lastpos(&temp2);
			 return temp2;
			 break;
		  case '?':
			 temp2 = create_node((char)QUEST);
			 if(NULL == temp2)
          {
				lex_error(17);
				return NULL;
			 }
			 temp2->left = temp;
			 getNextChar(&parser->lexer);
			 firstpos(&temp2);
			 lastpos(&temp2);
			 return temp2;
			 break;
		  case '{':
			 getNextChar(&parser->lexer);
			 getNextChar(&parser->lexer);
			 if(parser->lexer.current_char == ',')
          {
				ungetchar(parser->lexer.inputBuffer);
				ungetchar(parser->lexer.inputBuffer);
					getNextChar(&parser->lexer);
					temp2 = create_node(parser->lexer.current_char);
					if(NULL == temp2)
               {
					    lex_error(18);
					    return NULL;
					}
					getNextChar(&parser->lexer);
					getNextChar(&parser->lexer);
					temp3 = create_node(parser->lexer.current_char);
					if(NULL == temp3)
               {
					    lex_error(18);
					    return NULL;
					}
					getNextChar(&parser->lexer);
					if(parser->lexer.current_char == '}')
               {
					   temp4 = create_node((char)COMMA);
					    if(NULL == temp4)
                   {
						   lex_error(19);
						   return NULL;
					    }
					    temp4->left = temp2;
					    temp4->right = temp3;
					    temp3 = create_node((char)REPS);
					    if(NULL ==  temp4)
                   {
						   lex_error(20);
						   return NULL;
					    }
					    temp3->left = temp;
					    temp3->right = temp4;
					    getNextChar(&parser->lexer);
					    firstpos(&temp3);
					    lastpos(&temp3);
					    return temp3;
					    break;
					}
					else
               {
					    lex_error(19);
					    exit(-1);
					}
			 }
			 else
          {
 				 /* found another expression definition?? */
 				LOG_ERROR("shouldn't be here in scyak.l perhaps%s","\n");
				ungetchar(parser->lexer.inputBuffer);
				ungetchar(parser->lexer.inputBuffer);
				ungetchar(parser->lexer.inputBuffer);
				getNextChar(&parser->lexer);
 				LOG_ERROR("back to char %c\n", parser->lexer.current_char);
    			 firstpos(&temp);
    			 lastpos(&temp);
    			 return temp;
    			 break;
				
 /*				lex_error(13);*/
 /*				exit(-1);*/
			 }
	   }
    firstpos(&temp);
    lastpos(&temp);
    return temp;
}

RegularExpressionTreeNode* apply_def(Parser* parser)
{
   /* char_set** */
   /*    struct _node* rnode;*/
   RegularExpressionTreeNode* tempNode = NULL;
   LexerToken                tempToken = {0};
   Definition *         tempDefinition = NULL;
/*    rnode = NULL;*/
   LOG_0("appying definition\n");

   setIndividualTokens(&parser->lexer,0);
   tempToken = matchToken(&parser->lexer,tokenForType(IDENTIFIER));
   LOG_0("temptoken lexem <%s>\n", tempToken.lexeme);
   if((tempDefinition = definitionExists(parser,tempToken)))
   {
	   parser->fileBuffer = parser->lexer.inputBuffer;
	   pushBackChar(&parser->lexer);
	   swapBuffer(parser,tempDefinition->buffer);
	   tempNode = parseExpressionOR(parser);
	   swapBuffer(parser,parser->fileBuffer);
	   return tempNode;
   }
/*    for(e=0;parser->lexer.current_char != '}';e++){
	   str[e] = parser->lexer.current_char;
	   getNextChar(&parser->lexer);
    }
    str[e] = '\0';
    pushBackChar(&parser->lexer);
    pushBackChar(&parser->lexer);*/
/*    ungetchar(&parser->lexer.inputBuffer);
    ungetchar(&parser->lexer.inputBuffer);*/
/*    getNextChar(&parser->lexer);*/
/*    for(e=0;e<2*parser->num_defs;e+=2){
	   if(strcmp(parser->defs[e],str)==0){
		  tempbuf = parser->definitionBuffer[e/2];
		  break;
	   }
    }*/
/*    if(tempbuf != NULL){*/
/*	   v = getchar(tempbuf);*/\
/*	   swapBuffer(parser,tempbuf);
	   tempNode = parseExpressionOR(parser);
	   swapBuffer(parser,parser->fileBuffer);
	   return tempNode;
    }*/
   return NULL;
}
