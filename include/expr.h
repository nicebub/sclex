#ifndef MEXPR_H
#define MEXPR_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "expror.h"
#include "charset.h"
#include "escape.h"
#include "lfile.h"
#include "expror.h"

struct _node* expr(struct _cset ** ta,buffer* mbuf, char *c,struct _lfile* lfile);
struct _node* apply_def(struct _cset** ta,buffer* mbuf,char* c, struct _lfile* lfile);

#endif
