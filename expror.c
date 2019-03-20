#include "expror.h"

struct _node* expror(struct _cset ** ta,buffer *mbuf, char* c, struct _lfile* lfile){
    /*
	1 or more expressions OR'ed expr|expr|expr
	*/
    struct _node* temp;
    struct _node* temp2;
    struct _node* temp3;

    temp = temp2 = temp3 = NULL;
    
    if(*c != '\n' && *c != ')' && *c != '\0' && *c != EOF ){
	   temp = exprlist(ta,mbuf,c,lfile);
	   pos(&temp,1);
	   pos(&temp,0);
	   if(is_ws(*c)==0){
		  while(is_ws(*c)==0)
			 *c = getchar(mbuf);
		  return temp;
	   }
    }
    if(*c == '|'){
	   *c = getchar(mbuf);
    }
    while(*c != '\n' && *c != ')' && *c != '\0' && *c != EOF ){
	   temp2 = exprlist(ta,mbuf,c,lfile);
	   temp3 = create_node((char)OR);
	   if(temp3 == NULL){
		  lex_error(10);
		  return NULL;
	   }
	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
	   pos(&temp,1);
	   pos(&temp,0);
	   if(is_ws(*c)==0){
		  while(is_ws(*c)==0)
			 *c = getchar(mbuf);
		  return temp;
	   }
	   if(*c == '|'){
		  *c = getchar(mbuf);
	   }
    }
    return temp;

}
