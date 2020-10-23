#include <string.h>
#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
RegularExpressionTreeNode* parseExpression(base_set ** set,Io* programIO){ /* char_set** */
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;
    struct _node *temp4;
    char m;
    temp = temp2 = temp3 = temp4 = NULL;
    /*
	can be an (expr) OR [range] OR expr OR expr* OR expr+ OR expr? OR expr{a,b} OR expr|expr
	*/
    if((isalphanum(programIO->own_lexer.current_char) || isprintable(programIO->own_lexer.current_char)) && (programIO->own_lexer.current_char != '\\') ){
	   m = programIO->own_lexer.current_char;
	   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
	   
	   temp = create_node(m);\
	   if(temp == NULL){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(set,temp->value);
    }
    else{
	   	switch(programIO->own_lexer.current_char){
		    case '\\':
			   temp = parseEscapeChars(set,programIO);
			   if(temp == NULL){
				  lex_error(27);
				  return NULL;
			   }
			   add_to_set(set,temp->value);
			   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   break;
		  case '[':
			   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   temp = parseCharSet(set,programIO);
			   if(programIO->own_lexer.current_char == ']'){
			    	programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   	}
			   	else{
				    lex_error(13);
					printf("to finish a character class\n");
				    exit(-1);
	   			}
			   break;
		  case '(':
			   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   while(is_ws(programIO->own_lexer.current_char) ==0)
			    	programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   temp = parseExpressionOR(set,programIO);
			   while(is_ws(programIO->own_lexer.current_char) ==0)
			    	programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   if(programIO->own_lexer.current_char == ')'){
			    	programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   	}
			   else{
			    	lex_error(14);
			    	exit(-1);
			   	}
			   break;
		    case '{':
			   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   temp = apply_def(set,programIO);
			   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   if(programIO->own_lexer.current_char == '}'){
				  programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			   }
			   else{
				  lex_error(13);
				  printf("curly, to finish off a range\n");
				  exit(-1);
			   }
			   break;
    		}
    }
	   switch(programIO->own_lexer.current_char){
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
			 programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
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
			 programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
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
			 programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			 pos(&temp2,1);
			 pos(&temp2,0);
			 return temp2;
			 break;
		  case '{':
			 programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			 programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
			 if(programIO->own_lexer.current_char == ','){
					ungetchar(&programIO->own_lexer.inputBuffer);
					ungetchar(&programIO->own_lexer.inputBuffer);
					programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
					temp2 = create_node(programIO->own_lexer.current_char);
					if(temp2 == NULL){
					    lex_error(18);
					    return NULL;
					}
					programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
				    	programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
					temp3 = create_node(programIO->own_lexer.current_char);
					if(temp3 == NULL){
					    lex_error(18);
					    return NULL;
					}
					programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
					if(programIO->own_lexer.current_char == '}'){
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
					    programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
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
 				ungetchar(&programIO->own_lexer.inputBuffer);
 				ungetchar(&programIO->own_lexer.inputBuffer);
 				ungetchar(&programIO->own_lexer.inputBuffer);
 				programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
 				printf("back to char %c\n", programIO->own_lexer.current_char);
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

RegularExpressionTreeNode* apply_def(base_set** set,Io* programIO){ /* char_set** */
/*    struct _node* rnode;*/
    Buffer * tempbuf;
    char str[200];
    int e;
    char v;
    tempbuf = NULL;
/*    rnode = NULL;*/
    for(e=0;programIO->own_lexer.current_char != '}';e++){
	   str[e] = programIO->own_lexer.current_char;
	   programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
    }
    str[e] = '\0';
    ungetchar(&programIO->own_lexer.inputBuffer);
    ungetchar(&programIO->own_lexer.inputBuffer);
    programIO->own_lexer.current_char = getchar(&programIO->own_lexer.inputBuffer);
    for(e=0;e<2*programIO->lexfile.num_defs;e+=2){
	   if(strcmp(programIO->lexfile.defs[e],str)==0){
		  tempbuf = programIO->lexfile.defbuf[e/2];
		  break;
	   }
    }
    if(tempbuf != NULL){
	   v = getchar(tempbuf);
	   return parseExpressionOR(set,programIO);
    }
    return NULL;
}
