#include "escape.h"

struct _node* escape_char(struct _cset **ta,buffer* mbuf,char* c){
    struct _node* temp;
  //  char string[50];
    temp = NULL;
    *c = getchar(mbuf);
    switch(*c){
	   case 'n':
		  temp = create_node('\n');
		  return temp;
	   case 't':
		  temp = create_node('\t');
		  return temp;
	   case '\\':
	   case '\'':
	   case '"':
	   case '%':
	   case '*':
	   case '+':
	   case '?':
	   case '{':
	   case '}':
	   case '[':
	   case ']':
	   case '(':
	   case ')':
	   case '/':
	   case '.':
		  temp = create_node(*c);
		  return temp;
	   default:
		  printf("doesn't support that kind of escape character\n");
		  return NULL;
    }
    
}
