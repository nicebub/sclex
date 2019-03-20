#ifndef MCHARSET_H
#define MCHARSET_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "escape.h"

struct _node* charset(struct _cset ** ta,buffer* mbuf, char*c);

#endif