#include "charset.h"

struct _node* charset(struct _cset ** ta,buffer *mbuf, char *c){
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;
  //  char string[50];
    int a;
    a =0;
    temp = temp2 = temp3 = NULL;
    if(isalphanum(*c)|| isprintable(*c)){
	   temp = create_node(*c);
	   if(temp == NULL){
		  lex_error(21);
		  return NULL;
	   }
	   *c= getchar(mbuf);
	   if(is_ws(*c) ==0){
		  if(*c != ' '){
			 lex_error(22);
			 delete_root(temp);
			 temp = NULL;
			 return NULL;
		  }
	   }
	   if(*c == '-'){
		  *c = getchar(mbuf);
		  if(isalphanum(*c) || isprintable(*c)){
			 temp2 = create_node(*c);
			 if(temp2 == NULL){
				delete_root(temp);
				temp = NULL;
				lex_error(23);
				return NULL;
			 }
			 temp3 = create_node((char)OR);
			 if(temp3 == NULL){
				delete_root(temp);
				temp = NULL;
				delete_root(temp2);
				temp2 = NULL;
				lex_error(10);
				return NULL;
			 }
			 temp3->left = temp;
			 temp3->right = temp2;
			 add_to_cset(ta,temp->value);
			 add_to_cset(ta,temp2->value);
			 char start = temp->value +1;
			 char end = temp2->value;
			 for(char m=start;m<end;m++){
				add_to_cset(ta,m);
				temp = create_node(m);
				if(temp == NULL){
				    lex_error(21);
				    return NULL;
				}
				temp2 = create_node((char)OR);
				if(temp2 == NULL){
				    delete_root(temp);
				    temp = NULL;
				    lex_error(10);
				    return NULL;
				}
				temp2->left = temp3;
				temp2->right = temp;
				temp3 = temp2;

			 }
			 *c = getchar(mbuf);
			 pos(&temp3,1);
			 pos(&temp3,0);
			 return temp3;
		  }
		  return NULL;
	   }
	   else{
		  ungetchar(mbuf);
		  ungetchar(mbuf);
		  *c = getchar(mbuf);
		  delete_root(temp);
		  temp = NULL;
		  if(*c == '\\'){
			 
			 temp = escape_char(ta,mbuf,c);
			 if(temp == NULL){
				lex_error(27);
				return NULL;
			 }
		//	 *c = getchar(mbuf);
		  }
		  else{
			 temp = create_node(*c);
			 if(temp == NULL){
				lex_error(21);
				return NULL;
			 }
		  }
		  add_to_cset(ta,temp->value);
		  *c= getchar(mbuf);
		  while(isalphanum(*c) || isprintable(*c) || *c =='\\'){
		//	 string[a]=*c;
			 a++;
			 if(isalphanum(*c) || isprintable(*c)|| isescape(*c)){
				temp2 = create_node((char)OR);
				if(temp2 == NULL){
				    lex_error(24);
				    return NULL;
				}
				temp2->left = temp;
				if(*c == '\\'){
				    
				    temp = escape_char(ta,mbuf,c);
				    if(temp == NULL){
					   delete_root(temp2);
					   temp2 = NULL;
					   lex_error(27);
					   return NULL;
				    }
//				    *c = getchar(mbuf);
				}
				else{
				    temp = create_node(*c);
				    if(temp == NULL){
					   delete_root(temp2);
					   temp2 = NULL;
					   lex_error(21);
					   return NULL;
				    }
				}
				add_to_cset(ta,temp->value);
				temp2->right = temp;
				temp = temp2;
			 }
			 *c= getchar(mbuf);

		  }
		  temp3 = create_node((char)CHARSET);
		  if(temp3 == NULL){
			 lex_error(25);
			 return NULL;
		  }
		  temp3->left = temp;
	//	  string[a] = '\0';
//		  ungetchar(mbuf);
//		  *c = getchar(mbuf);
		  pos(&temp3,1);
		  pos(&temp3,0);

		  return temp3;
	   }
    }
    return NULL;
}
