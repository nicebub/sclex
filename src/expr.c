#include "../include/expr.h"
#include <string.h>
struct _node* expr(/*char** */base_set ** ta,buffer* mbuf, char *c, struct _lfile* lfile){
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;
    struct _node *temp4;
    char m;
    temp = temp2 = temp3 = temp4 = NULL;
    /*
	can be an (expr) OR [range] OR expr OR expr* OR expr+ OR expr? OR expr{a,b} OR expr|expr
	*/
    if((isalphanum(*c) || isprintable(*c)) && (*c != '\\') ){
	   m = *c;
	   *c = getchar(mbuf);
	   
	   temp = create_node(m);\
	   if(temp == NULL){
		  lex_error(12);
		  return NULL;
	   }
	   add_to_set(ta,temp->value);
    }
    else{
	   	switch(*c){
		    case '\\':
			   temp = escape_char(ta,mbuf,c);
			   if(temp == NULL){
				  lex_error(27);
				  return NULL;
			   }
			   add_to_set(ta,temp->value);
			   *c = getchar(mbuf);
			   break;
		  case '[':
			   *c = getchar(mbuf);
			   temp = charset(ta,mbuf,c);
			   if(*c == ']'){
			    	*c = getchar(mbuf);
			   	}
			   	else{
				    lex_error(13);
					printf("to finish a character class\n");
				    exit(-1);
	   			}
			   break;
		  case '(':
			   *c = getchar(mbuf);
			   while(is_ws(*c) ==0)
			    	*c = getchar(mbuf);
			   temp = expror(ta,mbuf,c,lfile);
			   while(is_ws(*c) ==0)
			    	*c = getchar(mbuf);
			   if(*c == ')'){
			    	*c = getchar(mbuf);
			   	}
			   else{
			    	lex_error(14);
			    	exit(-1);
			   	}
			   break;
		    case '{':
			   *c = getchar(mbuf);
			   temp = apply_def(ta,mbuf,c,lfile);
			   *c = getchar(mbuf);
			   if(*c == '}'){
				  *c = getchar(mbuf);
			   }
			   else{
				  lex_error(13);
				  printf("curly, to finish off a range\n");
				  exit(-1);
			   }
			   break;
    		}
    }
	   switch(*c){
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
			 *c = getchar(mbuf);
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
			 *c = getchar(mbuf);
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
			 *c = getchar(mbuf);
			 pos(&temp2,1);
			 pos(&temp2,0);
			 return temp2;
			 break;
		  case '{':
			 *c = getchar(mbuf);
			 *c = getchar(mbuf);
			 if(*c == ','){
					ungetchar(mbuf);
					ungetchar(mbuf);
					*c = getchar(mbuf);
					temp2 = create_node(*c);
					if(temp2 == NULL){
					    lex_error(18);
					    return NULL;
					}
					*c = getchar(mbuf);
				    	*c = getchar(mbuf);
					temp3 = create_node(*c);
					if(temp3 == NULL){
					    lex_error(18);
					    return NULL;
					}
					*c = getchar(mbuf);
					if(*c == '}'){
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
					    *c = getchar(mbuf);
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
 				ungetchar(mbuf);
 				ungetchar(mbuf);
 				ungetchar(mbuf);
 				*c = getchar(mbuf);
 				printf("back to char %c\n", *c);
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

struct _node* apply_def(/*char** */base_set** ta,buffer* mbuf,char* c, struct _lfile* lfile){
/*    struct _node* rnode;*/
    buffer * tempbuf;
    char str[200];
    int e;
    char v;
    tempbuf = NULL;
/*    rnode = NULL;*/
    for(e=0;*c != '}';e++){
	   str[e] = *c;
	   *c = getchar(mbuf);
    }
    str[e] = '\0';
    ungetchar(mbuf);
    ungetchar(mbuf);
    *c = getchar(mbuf);
    for(e=0;e<2*lfile->num_defs;e+=2){
	   if(strcmp(lfile->defs[e],str)==0){
		  tempbuf = lfile->defbuf[e/2];
		  break;
	   }
    }
    if(tempbuf != NULL){
	   v = getchar(tempbuf);
	   return expror(ta,tempbuf,&v,lfile);
    }
    return NULL;
}
