#include <stdio.h>
#include <stdlib.h>

extern int sclex(FILE* infile);

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
	FILE * infile;
	if( argc < 2){
		printf("Please provide a filename to scan\n");
		exit(-1);
	}
	if((infile = fopen(argv[1],"r"))){
		printf("Calling sclex from main app\n");
		while(1){
			int result = sclex(infile);
		    if(result != -1 && result != EOF)
			   	printf("found token %s with lexeme .....\n", token_strings[result]);
		    else
			   printf("found end of string or file, ending\n");
//			char x[100];
//			scanf("%s",x);
			if(result == -1 || result == EOF)
				break;
	}
		fclose(infile);
		return 0;
		
	}
	else{
		printf("couldn't open file %s\n", argv[1]);
		exit(-1);
	}
}
