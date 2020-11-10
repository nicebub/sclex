#ifndef MGEN_H
#define MGEN_H

#include "Parser.h"
#include "dfa.h"
/*#include "lfile.h"*/

typedef enum _PARAGRAPH {
	BUFFER_PAR,
	DECL_PAR,
	ALPH_SZ_PAR,
	STATE_SZ_PAR,
	ACCEPT_STATE_SZ_PAR,
	NUM_REGEX_PAR,
	ALPH_PAR,
	MOVEMENT_PAR,
	ACCEPT_STATE_PAR,
	ACCEPT_TABLE_PAR,
	USER_CODE_PAR
}  paragraph_id;

void generate_output(Parser* parser, struct _DFA*);

extern void lex_error(int en);
#endif
