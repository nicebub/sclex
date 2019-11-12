#ifndef MGEN_H
#define MGEN_H

#include "dfa.h"
#include "lfile.h"

void generate_output(struct _lfile, struct _DFA*);

extern void lex_error(int en);
#endif
