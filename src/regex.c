#include "../include/regex.h"
#include <string.h>
struct _node* regexp(struct _ta ** ta,buffer * mbuf, char *c, struct _lfile* lfile){
    struct _node * temp;
    temp = NULL;
    /*
	represents a regular expression on one line
	*/
    temp = fullexpr(&(*ta)->alphabet,mbuf,c,lfile);

    if(*c == '{'){
	   char sbuf[8000];
	   int scount =0;
	   int extrafrontbrackets = 0;
	   sbuf[0] = '{';
	   scount++;
	   while((*c = getchar(mbuf))!= EOF && *c !='\0'){
		  if(*c == '}'){
			 if(extrafrontbrackets != 0){
				extrafrontbrackets--;
				sbuf[scount] = *c;
				scount++;
				/* *c = getchar(mbuf); */
			 }
			 else{
				sbuf[scount] = '}';
				scount++;
				sbuf[scount]='\0';
				(*ta)->action_array[(*ta)->used] = malloc(sizeof(char)*strlen(sbuf)+1);
				strcpy((*ta)->action_array[(*ta)->used],sbuf);
				*c = getchar(mbuf);
				while(is_ws(*c) == 0)
				    *c = getchar(mbuf);
				if(*c == '\n' || *c == EOF || *c == '\0')
				    return temp;
				else{
				    printf("error expecting a newline character but found %c\n",*c);
				    exit(-1);
				}
			 }
		  }
		  else{
			 if(*c == '{'){
				extrafrontbrackets++;
			 }
			 sbuf[scount] = *c;
			 scount++;

		  }
	   }
	   return temp;
    }
    else{
	   lex_error(11);
	   printf("error expecting a '{' character but found %c\n",*c);
	   exit(-1);
    }
}

struct _node* fullexpr(struct _cset ** ta,buffer *mbuf, char *c, struct _lfile* lfile){
/*
 represents a full expression on a line minus the newline character
 (expr) OR expr.op OR expr|expr OR [range] OR exprlist

 */
    return expror(ta,mbuf, c,lfile);
 }
