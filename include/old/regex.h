#ifndef MREGEX_H
#define MREGEX_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "expror.h"
#include "lfile.h"
#include "baseset.h"
#include "chrset.h"

struct _node* regexp(struct _ta ** ta,Buffer* mbuf, char *c, struct _lfile* lfile);
struct _node* fullexpr(base_set ** ta,Buffer *mbuf,char* c, struct _lfile* lfile);
/* base_set ** ta is a char_set ** */
#endif
