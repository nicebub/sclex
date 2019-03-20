#include "exprcat.h"

struct _node* exprlist(struct _cset ** ta,buffer * mbuf, char* c, struct _lfile* lfile){
    /*
	1 or more expressions concatenated expr.expr.expr
	*/
    struct _node* temp;
    struct _node* temp2;
    struct _node* temp3;
    temp = temp2 = temp3 = NULL;
    if(*c != '\n' && *c != ')' && *c != '|' && *c != '\0' && *c != EOF ){
	   temp = expr(ta,mbuf,c,lfile);
	   pos(&temp,1);
	   pos(&temp,0);
	   if(is_ws(*c) == 0)
		  return temp;
    }
    while(*c != '\n' && *c != ')' && *c != '|' && *c != '\0' && *c != EOF ){
	   temp2 = expr(ta,mbuf,c,lfile);
	   temp3 = create_node((char)CONCAT);
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }
	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
	   temp3 = NULL;
	   pos(&temp,1);
	   pos(&temp,0);
	   if(is_ws(*c) == 0)
		 return temp;
    }
    return temp;
}
