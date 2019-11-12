/** 
	This file houses the part of the parser that recognizes character
classes and constructs the part of the parse tree from the input stream
then it returns the structure to be incorporate with the rest of the 
parse tree.

*/
#include "../include/charset.h"

/* Function Prototype

	struct _node* charset(struct _cset ** ta,buffer *mbuf, char *c)

Functionality: Charset is the part of the predictive parser that
	recognizes and puts into the parse tree, character sets [a-z]|[tbt@m;]

Parameters: a memory address of a character set pointer _cset** ta
			an initialized buffer pointer buffer* mbuf
			the current input character pointer char* c

Returns: returns a tree structure of nodes to be added to the parse
	tree

Results: a parse tree of nodes is constructed to represent the character
	classes/sets found in the input stream

*/
struct _node* charset(struct _cset ** ta,buffer *mbuf, char *c){
	/* a few temporary node pointers declared for later */
    struct _node *temp;
    struct _node *temp2;
    struct _node *temp3;


    int a;
    a =0;
    temp = temp2 = temp3 = NULL;
	/* either the current character meets our requirements for starting a
		character set or it doesn't and we return NULL */
    if(isalphanum(*c)|| isprintable(*c)){
	   temp = create_node(*c);
	   /* couldn't create node so print error and return NULL */
	   if(temp == NULL){
		  lex_error(21);
		  return NULL;
	   }
	   /* get 1st character in set */
	   *c= getchar(mbuf);
	   /* can't be whitespace */
	   if(is_ws(*c) ==0){
		  if(*c != ' '){
			 lex_error(22);
			 delete_root(temp);
			 temp = NULL;
			 return NULL;
		  }
	   }
	   /* if the next character is a minus then assume we have a character
	   	set like a-z, b-r T-W, 1-6, etc.
	   */
	   if(*c == '-'){
		  *c = getchar(mbuf);
		  if(isalphanum(*c) || isprintable(*c)){
			 temp2 = create_node(*c);
			 /* any problems creating the node then print an error and return
			 	NULL with some memory cleanup */
			 if(temp2 == NULL){
				delete_root(temp);
				temp = NULL;
				lex_error(23);
				return NULL;
			 }
			 /* add an implied OR node for every character in the class */
			 temp3 = create_node((char)OR);
			 /* problems with creating? return after printing an error */
			 if(temp3 == NULL){
				delete_root(temp);
				temp = NULL;
				delete_root(temp2);
				temp2 = NULL;
				lex_error(10);
				return NULL;
			 }
			 /*
			 OR nodes children set up with terminal nodes created 
			 */
			 temp3->left = temp;
			 temp3->right = temp2;
			 /* add to the alphabet set the first and last letters of the class */
			 add_to_cset(ta,temp->value);
			 add_to_cset(ta,temp2->value);
			 /* loop through the set and do the same for all the other characters
			 	found in in the character range */
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
			 /* 
			 	now get the firstpos and lastpos of the new part of the
			 	parse tree created and add that to the nodes of the tree.
			 	return this part of the parse tree.
			 */
			 pos(&temp3,1);
			 pos(&temp3,0);
			 return temp3;
		  }
		  return NULL;
	   }
	   /* we didn't find a minus sign which means this isn't a character class range like
	   	a-b but more like a list of characters in sequence with another */
	   else{
		   /* put back the first 2 characters read, reset the buffer and node
		   	 memory used to determine the state of the character set */
		  ungetchar(mbuf);
		  ungetchar(mbuf);
		  *c = getchar(mbuf);
		  delete_root(temp);
		  temp = NULL;
		  /* if we found a backslash then call the parser
		  	function esacpe_char to further progress the input. If what comes
		  	back from that function is NULL then print an error and return NULL
		   */
		  if(*c == '\\'){
			 
			 temp = escape_char(ta,mbuf,c);
			 if(temp == NULL){
				lex_error(27);
				return NULL;
			 }
		  }
		  /* we didn't find a backslash escaped character */
		  else{
			 temp = create_node(*c);
			 if(temp == NULL){
				lex_error(21);
				return NULL;
			 }
		  }
		  /* add first character to alphabet */
		  add_to_cset(ta,temp->value);
		  *c= getchar(mbuf);
		  /* now loop through the rest of the character set until we are through 
		  */
		  while(isalphanum(*c) || isprintable(*c) || *c =='\\'){
			 a++;
			 if(isalphanum(*c) || isprintable(*c)|| isescape(*c)){
				temp2 = create_node((char)OR);
				if(temp2 == NULL){
				    lex_error(24);
				    return NULL;
				}
				temp2->left = temp;
				/* again we may have found another esacpe character */
				if(*c == '\\'){
				    
				    temp = escape_char(ta,mbuf,c);
				    if(temp == NULL){
					   delete_root(temp2);
					   temp2 = NULL;
					   lex_error(27);
					   return NULL;
				    }
				}
				/* we didn't find an escape character but a normal one */
				else{
				    temp = create_node(*c);
				    if(temp == NULL){
					   delete_root(temp2);
					   temp2 = NULL;
					   lex_error(21);
					   return NULL;
				    }
				}
				/* add this character the the alphabet set */
				add_to_cset(ta,temp->value);
				temp2->right = temp;
				temp = temp2;
			 }
			 *c= getchar(mbuf);

		  }
		  /* create the CHARSET token in the parse tree and connect
		  the rest of the tree constructed earlier to be later returned */
		  temp3 = create_node((char)CHARSET);
		  if(temp3 == NULL){
			 lex_error(25);
			 return NULL;
		  }
		  temp3->left = temp;
		  /* construct the firstpos and lastpos sets of the new part of the parse 
		  	tree and set the values in the nodes of the tree */
		  pos(&temp3,1);
		  pos(&temp3,0);

		  return temp3;
	   }
    }
	/* all else fails, we had a problem return NULL */
    return NULL;
}
