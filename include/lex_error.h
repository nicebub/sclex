#ifndef MLEXER_H
#define MLEXER_H


/* Function Prototype
	
	void lex_error(int en);

Functionality: Print an error message depending on err number
	given as input

Parameter: an integer that represents which string in the 
	internal array represents the error to print

Results: Print an error message to stdout

*/
void lex_error(int en);

#define SCERR_OPEN 0
#define SCERR_DECL_UNDECLARED 1
#define SCERR_MUST_USE_SEPR 2
#define SCERR_SEPR_AFTER_TRANS 3
#define SCERR_MEM_FPOS 4
#define SCERR_MEM_SET 5
#define SCERR_MEM_TA_RES 6
#define SCERR_UNKNOWN 7
#define SCERR_MEM_HASH 8
#define SCERR_MEM_CCAT 9
#define SCERR_MEM_OR 10
#define SCERR_PARTIAL 11
#define SCERR_MEM_EXPRN 12
#define SCERR_EXPECT_RB 13
#define SCERR_EXPECT_RP 14
#define SCERR_MEM_STAR 15
#define SCERR_MEM_PLUS 16
#define SCERR_MEM_QUEST 17
#define SCERR_MEM_RANGE 18
#define SCERR_MEM_COMMA 19
#define SCERR_MEM_REPS 20
#define SCERR_MEM_CIN 21
#define SCERR_NO_WS_IN_CHARSET 22
#define SCERR_MEM_ALNUMP 23
#define SCERR_MEM_OR_IN_CHARSET 24
#define SCERR_MEM_CHARSET_CHAR 25
#define SCERR_NEED_ARGUMENT 26
#define SCERR_MEM_ESCAPE 27


#endif