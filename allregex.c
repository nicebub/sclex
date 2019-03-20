#include "allregex.h"

struct _ta* regexpset(buffer* mbuf, char* c, struct _lfile* lfile){
    struct _node * temp;
    struct _node * temp2;
    struct _node * temp3;
    struct _node * temp4;
    struct _ta * ta;
    int ct;
    ta = NULL;
    temp = temp2 = temp3 = temp4 = NULL;
    ct =0;
    ta = create_ta(512);
    if(ta == NULL){
	   lex_error(6);
	   return NULL;
    }
    if(*c != EOF  && *c != '%' && (*c = getchar(mbuf))!= EOF){
	   temp = regexp(&ta,mbuf,c,lfile);
	   if(temp == NULL){
		  lex_error(7);
		  return NULL;
	   }
	   temp2 = create_node('#');
	   if(temp2 == NULL){
		  lex_error(8);
		  return NULL;
	   }
	   temp3 = create_node((char)CONCAT);
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }
	   temp3->left = temp;
	   temp3->right = temp2;
	   temp = temp3;
    }
    pos(&temp,1);
    pos(&temp,0);
    ta->t[ct] = temp;
    ta->used++;
    ta->atop = temp;
    ta->finalpos[ta->num_re] =temp2->uniq;
    ta->num_re++;
    ct++;
    
    while((is_ws(*c) ==0) || *c == '\n')
	   *c = getchar(mbuf);

    if(*c == '%')
	  return ta;

    while(*c != EOF && *c != '%'){
	   temp2 = regexp(&ta,mbuf,c,lfile);
	   if(temp2 == NULL){
		  *c = getchar(mbuf);
		  continue;
	   }
	   temp3 = create_node((char)CONCAT);
	   if(temp3 == NULL){
		  lex_error(9);
		  return NULL;
	   }
	   temp4 = create_node('#');
	   if(temp4 == NULL){
		  lex_error(8);
		  return NULL;
	   }

	   temp3->left = temp2;
	   temp3->right = temp4;
	   pos(&temp3,1);
	   pos(&temp3,0);
	   ta->t[ct] = temp3;
	   ta->used++;
	   ta->finalpos[ta->num_re] = temp4->uniq;
	   ct++;
	   ta->num_re++;
	   temp4 = create_node((char)OR);
	   if(temp4 == NULL){
		  lex_error(10);
		  return NULL;
	   }
	   temp4->left = temp;
	   temp4->right = temp3;
	   pos(&temp4,1);
	   pos(&temp4,0);
	   temp = temp4;
	   ta->atop = temp;

	   while((is_ws(*c) ==0) || *c == '\n')
		  *c = getchar(mbuf);

	   if(*c == '%'){
		  return ta;
	   }
    }
    return ta;
}
