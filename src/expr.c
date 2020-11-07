#include <string.h>
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
RegularExpressionTreeNode* parseExpression(Parser* parser){ /* char_set** */
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;
    struct _node *temp4;
    char m;
    temp = temp2 = temp3 = temp4 = NULL;
    /*
	can be an (expr) OR [range] OR expr OR expr* OR expr+ OR expr? OR expr{a,b} OR expr|expr
	*/
    if(matchToken(&parser->lexer,tokenForType(LPAREN)).lexeme){
	   temp = parseExpressionOR(parser);
	   if(!matchToken(&parser->lexer,tokenForType(RPAREN)).lexeme){
		  lex_error(14);
		  exit(-1);
	   }
    }
    else if(matchToken(&parser->lexer,tokenForType(LBRACKET)).lexeme){
	   temp = parseCharSet(&parser->parseTree->alphabet,parser);
	   if(!matchToken(&parser->lexer,tokenForType(RBRACKET)).lexeme){
		    lex_error(13);
			printf("to finish a character class\n");
		    exit(-1);
		}
    }
    else if(matchToken(&parser->lexer,tokenForType(LCURLY)).lexeme){
	   temp = apply_def(parser);
	   if(!matchToken(&parser->lexer,tokenForType(RCURLY)).lexeme){
		  lex_error(13);
		  printf("curly, to finish off a range\n");
		  exit(-1);
	   }
    }
    else if(matchToken(&parser->lexer,tokenForType(BSLASH)).lexeme){
	   temp = parseEscapeChars(parser);
	   if(!temp){
		  lex_error(27);
		  return NULL;
	   }
	   add_to_set(&parser->parseTree->alphabet,temp->value);
    }
    else{
	   setIndividualTokens(&parser->lexer,1);
	   m = *getNextToken(&parser->lexer).lexeme;
	   temp = create_node(m);\
	   if(!temp){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(&parser->parseTree->alphabet,temp->value);

    }
    
 /*   else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}
    else if(matchToken(&parser->lexer,tokenForType()).lexeme){}*/
    if((isalphanum(parser->lexer.current_char) || isprintable(parser->lexer.current_char)) && (parser->lexer.current_char != '\\') ){
	   m = parser->lexer.current_char;
	   getNextChar(&parser->lexer);
	   temp = create_node(m);\
	   if(!temp){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(&parser->parseTree->alphabet,temp->value);
    }
    else{
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
    }
	   switch(parser->lexer.current_char){
		  case '\n':
			 firstpos(&temp);
			 lastpos(&temp);
			 return temp;
			 break;
		  case '*':
			 temp2 = create_node((char)STAR);
			 if(!temp2){
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
			 if(!temp2){
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
			 if(!temp2){
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
			 if(parser->lexer.current_char == ','){
					ungetchar(&parser->lexer.inputBuffer);
					ungetchar(&parser->lexer.inputBuffer);
					getNextChar(&parser->lexer);
					temp2 = create_node(parser->lexer.current_char);
					if(!temp2){
					    lex_error(18);
					    return NULL;
					}
					getNextChar(&parser->lexer);
					getNextChar(&parser->lexer);
					temp3 = create_node(parser->lexer.current_char);
					if(!temp3){
					    lex_error(18);
					    return NULL;
					}
					getNextChar(&parser->lexer);
					if(parser->lexer.current_char == '}'){
					   temp4 = create_node((char)COMMA);
					    if(!temp4){
						   lex_error(19);
						   return NULL;
					    }
					    temp4->left = temp2;
					    temp4->right = temp3;
					    temp3 = create_node((char)REPS);
					    if(!temp4){
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
					else{
					    lex_error(19);
					    exit(-1);

					}
			 }
			 else{
 				 /* found another expression definition?? */
 				printf("shouldn't be here in scyak.l perhaps\n");
 				ungetchar(&parser->lexer.inputBuffer);
 				ungetchar(&parser->lexer.inputBuffer);
 				ungetchar(&parser->lexer.inputBuffer);
				getNextChar(&parser->lexer);
 				printf("back to char %c\n", parser->lexer.current_char);
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

RegularExpressionTreeNode* apply_def(Parser* parser){ /* char_set** */
/*    struct _node* rnode;*/
    Buffer * tempbuf;
    char str[200];
    int e;
    char v;
    tempbuf = NULL;
/*    rnode = NULL;*/
    for(e=0;parser->lexer.current_char != '}';e++){
	   str[e] = parser->lexer.current_char;
	   getNextChar(&parser->lexer);
    }
    str[e] = '\0';
    pushBackChar(&parser->lexer);
    pushBackChar(&parser->lexer);
/*    ungetchar(&parser->lexer.inputBuffer);
    ungetchar(&parser->lexer.inputBuffer);*/
    getNextChar(&parser->lexer);
    for(e=0;e<2*parser->num_defs;e+=2){
	   if(strcmp(parser->defs[e],str)==0){
		  tempbuf = parser->definitionBuffer[e/2];
		  break;
	   }
    }
    if(tempbuf != NULL){
	   v = getchar(tempbuf);
	   return parseExpressionOR(parser);
    }
    return NULL;
}
