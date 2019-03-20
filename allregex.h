#ifndef MALLREGEX_H
#define MALLREGEX_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "regex.h"
#include "lfile.h"

struct _ta* regexpset(buffer* mbuf,char * c, struct _lfile* lfile);


#endif
