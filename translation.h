#ifndef MTRANSLAT_H
#define MTRANSLAT_H

#include "buffer.h"
#include "set.h"
#include "tree.h"
#include "lfile.h"
#include "allregex.h"
#include "lex_error.h"
#include "retodfa.h"

struct _ta* translations(buffer* mbuf, char*c, struct _lfile *);



#endif