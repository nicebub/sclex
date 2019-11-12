/**

This file is an example 'Wrapper' function that acts as a main
executable and calls the lexer generated from previous example

The program will assume the first argument is a file name to a file that
exists or it will generate an error and finish. Otherwise the file is opened,
buffered, and sent to the lexer to see if what is written in the file is recognized
as part of the language described from the regular expressions that the lexer
represents.

*/
#include <stdio.h>
#include <stdlib.h>
/* A declaration to the lexer generated in an earlier example */
extern int sclex(FILE* infile);
extern FILE* scin;
/* Tokens name Array for printin later on as they are found g*/
const char *token_strings[] ={
    "IDENT",
    "INTEGER",
    "EQUALS",
    "SEMICOLON",
    "SYMBOL",
    "RELATION",
    "STRING",
    "LPAREN",
    "RPAREN",
    "LCBRA",
    "RCBRA",
    "LBRA",
    "RBRA",
    "COMMA",
    "LESS",
    "GREAT",
    "EQAL",
    "PLUS",
    "MINS",
    "FORW",
    "STAR",
 "GRE",
 "LTE",
 "NEQ",
 "EQUIV",
 "ADDRESS",
 "ELIP"


};

int main(int argc, const char ** argv){
	/* FILE pointer used to open the file name of argument number 1 */
	FILE * infile=NULL;
	/* or error if not given, print an error and exit with -1 */
//	if( argc < 2){
//		printf("Please provide a filename to scan\n");
//		exit(-1);
//	}
	/* we opened the file for reading and we want to process it and tokenized it
		we print what we find
	*/
	if(argc >= 2){
		if((infile = fopen(argv[1],"r"))== NULL){
			printf("couldn't open file %s\n", argv[1]);
			exit(-1);			
		}
		scin = infile;
	}
		printf("Calling sclex from main app\n");
		while(1){
			/* result will hold the token found and returned each iteration
			or an error or End of FIle
			 */
			int result = sclex(infile);
			/* we found a token we know of so print a message on standard output
			*/
		    if(result != -1 && result != EOF)
			   	printf("found token %s with lexeme .....\n", token_strings[result]);
			/* we didn't so end */
		    else
			   printf("found end of string or file, ending\n");
			/* we may end or continue reading for tokens depending on last returned answer
			*/
			if(result == -1 || result == EOF)
				break;
	}
	/* cleanup and finish program */
		if(infile){
			fclose(infile);
			infile = NULL;
		}
		return 0;
		
	/* the file couldn't be opened for reading for some reason so print an error
		and exit with -1
	*/
}
