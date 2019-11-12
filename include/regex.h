#ifndef MREGEX_H
#define MREGEX_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"
#include "expror.h"
#include "lfile.h"

struct _node* regexp(struct _ta ** ta,buffer* mbuf, char *c, struct _lfile* lfile);
struct _node* fullexpr(struct _cset ** ta,buffer *mbuf,char* c, struct _lfile* lfile);

#endif
