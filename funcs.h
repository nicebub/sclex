#ifndef MFUNCS_H
#define MFUNCS_H


/** Function Prototype

	int isalphanum(char c);

Functionality: Determines whether a character is an alpha-
	numberic one or not

Parameters: an input character

Returns: 1 if is alpha-num or 0 otherwise

Results: an integer 0 or 1 representing true or false is
	returned
*/
int isalphanum(char c);
/** Function Prototype

	int isescape(char c);

Functionality: Determines whether a characer is an escape
	character or not

Parameters: an input character

Returns: 1 if is an escape, 0 otherwise

Results: Integer 1 or 0 returned

*/
int isescape(char c);
/** Function Prototype

	int isprintable(char c);

Functionality: Determines whether the character is a
	printable one to a terminal screen.

Parameters: an inputer character

Returns: 1 if is a printable character, 0 otherwise

Results: returns an integer 0 or 1

*/
int isprintable(char c);
/** Function Prototype

	int is_ws(char c);

Functionality: Determine whether the input character is
	a whitespace character or not

Parameters: an input character

Returns: 1 if is whitespace, 0 otherwise

Results: an integer of either 1 or 0 is a return value

*/
int is_ws(char c);


#endif
