/**
 This file includes a few short functions used to determine whether input
characters are of a particular set or not. Sets include, whitespace, escape
character sequences, alapha-numerics, and screen printables.
*/
#include "funcs.h"


/**

	int isalphanum(char c)

Functionality: Determines whether a character is an alpha-
	numberic one or not

Parameters: an input character char c

Returns: 1 if is alpha-num or 0 otherwise

Results: an integer 0 or 1 representing true or false is
	returned
*/
 int isalphanum(char c){
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){
	   return 1;
    }
    return 0;
}
/** Function Prototype

	int isprintable(char c)

Functionality: Determines whether the character is a
	printable one to a terminal screen.

Parameters: an inputer character char c

Returns: 1 if is a printable character, 0 otherwise

Results: returns an integer 0 or 1

*/
 int isprintable(char c){
	 /* A string or character array of printable characters used
	 to match against the input
	 */
    const static char *str = "!@#$%^&\\=-_\'\";:,<.>/`~*|?+ 	";
	/* a temporary pointer used to hold an address to point to a
	particular character in the above 'str' array during the loop
	process */
    const char * t;

    t = str;
	/* loop through the characters in the character string 'str'
	and check against the input character. If one matches then
	its printable and return a 1.
	*/
    while(*t != '\0'){
	   if(*t == c)
		  return 1;
	   t++;
    }
    return 0;
}

/** Function Prototype

	int is_ws(char c)

Functionality: Determine whether the input character is
	a whitespace character or not

Parameters: an input character char c

Returns: 1 if is whitespace, 0 otherwise

Results: an integer of either 1 or 0 is a return value

*/
 int is_ws(char c){
    if(c == ' ' || c == '\t' || c == '\r' || c == '\f')
	   return 0;
    return 1;
}

/** Function Prototype

	int isescape(char c)

Functionality: Determines whether a characer is an escape
	character or not

Parameters: an input character

Returns: 1 if is an escape, 0 otherwise

Results: Integer 1 or 0 returned

*/
 int isescape(char c){
	 /* switch statement for future use */
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
