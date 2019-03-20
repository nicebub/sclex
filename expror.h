#ifndef MEXPROR_H
#define MEXPROR_H

#include "buffer.h"
#include "tree.h"
#include "retodfa.h"
#include "lex_error.h"
#include "exprcat.h"
#include "lfile.h"

struct _node* expror(struct _cset ** ta,buffer *mbuf, char* c, struct _lfile* lfile);

#endif
