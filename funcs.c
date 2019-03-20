#include "funcs.h"

 int isalphanum(char c){
//    printf("running isalphanum on %c\n",c);
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){
//	   printf("found an alphanum\n");
	   return 1;
    }
//    printf("not alphanum\n");
    return 0;
}
 int isprintable(char c){
//    printf("running isprintable on %c\n",c);
    const static char *str = "!@#$%^&\\=-_\'\";:,<.>/`~*|?+ 	";
    const char * t;
    t = str;
    while(*t != '\0'){
	   if(*t == c)
		  return 1;
	   t++;
    }
    return 0;
}

 int is_ws(char c){
    if(c == ' ' || c == '\t' || c == '\r' || c == '\f')
	   return 0;
    return 1;
}

 int isescape(char c){
    switch(c){
	   case '\n':
	   case '\t':
	   case '{':
	   case '}':
	   case '(':
	   case ')':
	   case '[':
	   case ']':
	   case '\\':
	   case '\'':
	   case '"':
	   case '%':
	   case '*':
	   case '+':
	   case '?':
	   case '/':
	   case '.':
		  return 1;
	   default:
		  return 0;
    }
}
