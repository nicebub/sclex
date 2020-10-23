#include <string.h>
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
RegularExpressionTreeNode* parseExpression(base_set ** set,Parser* parser){ /* char_set** */
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;
    struct _node *temp4;
    char m;
    temp = temp2 = temp3 = temp4 = NULL;
    /*
	can be an (expr) OR [range] OR expr OR expr* OR expr+ OR expr? OR expr{a,b} OR expr|expr
	*/
    if((isalphanum(parser->lexer.current_char) || isprintable(parser->lexer.current_char)) && (parser->lexer.current_char != '\\') ){
	   m = parser->lexer.current_char;
	   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	   
	   temp = create_node(m);\
	   if(temp == NULL){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(set,temp->value);
    }
    else{
	   	switch(parser->lexer.current_char){
		    case '\\':
			   temp = parseEscapeChars(set,parser);
			   if(temp == NULL){
				  lex_error(27);
				  return NULL;
			   }
			   add_to_set(set,temp->value);
			   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   break;
		  case '[':
			   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   temp = parseCharSet(set,parser);
			   if(parser->lexer.current_char == ']'){
			    	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   	}
			   	else{
				    lex_error(13);
					printf("to finish a character class\n");
				    exit(-1);
	   			}
			   break;
		  case '(':
			   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   while(is_ws(parser->lexer.current_char) ==0)
			    	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   temp = parseExpressionOR(set,parser);
			   while(is_ws(parser->lexer.current_char) ==0)
			    	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   if(parser->lexer.current_char == ')'){
			    	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   	}
			   else{
			    	lex_error(14);
			    	exit(-1);
			   	}
			   break;
		    case '{':
			   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   temp = apply_def(set,parser);
			   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			   if(parser->lexer.current_char == '}'){
				  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
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
			 pos(&temp,1);
			 pos(&temp,0);
			 return temp;
			 break;
		  case '*':
			 temp2 = create_node((char)STAR);
			 if(temp2 == NULL){
				lex_error(15);
				return NULL;
			 }
			 temp2->left = temp;
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 pos(&temp2,1);
			 pos(&temp2,0);
			 return temp2;
			 break;
		  case '+':
			 temp2 = create_node((char)PLUS);
			 if(temp2 == NULL){
				lex_error(16);
				return NULL;
			 }
			 temp2->left = temp;
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 pos(&temp2,1);
			 pos(&temp2,0);
			 return temp2;
			 break;
		  case '?':
			 temp2 = create_node((char)QUEST);
			 if(temp2 == NULL){
				lex_error(17);
				return NULL;
			 }
			 temp2->left = temp;
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 pos(&temp2,1);
			 pos(&temp2,0);
			 return temp2;
			 break;
		  case '{':
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 if(parser->lexer.current_char == ','){
					ungetchar(&parser->lexer.inputBuffer);
					ungetchar(&parser->lexer.inputBuffer);
					parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					temp2 = create_node(parser->lexer.current_char);
					if(temp2 == NULL){
					    lex_error(18);
					    return NULL;
					}
					parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
				    	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					temp3 = create_node(parser->lexer.current_char);
					if(temp3 == NULL){
					    lex_error(18);
					    return NULL;
					}
					parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					if(parser->lexer.current_char == '}'){
					   temp4 = create_node((char)COMMA);
					    if(temp4 == NULL){
						   lex_error(19);
						   return NULL;
					    }
					    temp4->left = temp2;
					    temp4->right = temp3;
					    temp3 = create_node((char)REPS);
					    if(temp4 == NULL){
						   lex_error(20);
						   return NULL;
					    }
					    temp3->left = temp;
					    temp3->right = temp4;
					    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					    pos(&temp3,1);
					    pos(&temp3,0);
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
 				parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
 				printf("back to char %c\n", parser->lexer.current_char);
    			 pos(&temp,1);
    			 pos(&temp,0);
    			 return temp;
    			 break;
				
 /*				lex_error(13);*/
 /*				exit(-1);*/
			 }
	   }
    pos(&temp,1);
    pos(&temp,0);
    return temp;
}

RegularExpressionTreeNode* apply_def(base_set** set,Parser* parser){ /* char_set** */
/*    struct _node* rnode;*/
    Buffer * tempbuf;
    char str[200];
    int e;
    char v;
    tempbuf = NULL;
/*    rnode = NULL;*/
    for(e=0;parser->lexer.current_char != '}';e++){
	   str[e] = parser->lexer.current_char;
	   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
    }
    str[e] = '\0';
    ungetchar(&parser->lexer.inputBuffer);
    ungetchar(&parser->lexer.inputBuffer);
    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
    for(e=0;e<2*parser->num_defs;e+=2){
	   if(strcmp(parser->defs[e],str)==0){
		  tempbuf = parser->defbuf[e/2];
		  break;
	   }
    }
    if(tempbuf != NULL){
	   v = getchar(tempbuf);
	   return parseExpressionOR(set,parser);
    }
    return NULL;
}
