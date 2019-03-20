#ifndef MEXPRCAT_H
#define MEXPRCAT_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "expr.h"
#include "lfile.h"

struct _node* exprlist(struct _cset ** ta,buffer *mbuf, char* c,struct _lfile* lfile);


#endif
