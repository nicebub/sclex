#ifndef MEXPR_H
#define MEXPR_H

#include "basebuffer.h"
#include "tree.h"
#include "lex_error.h"
#include "retodfa.h"
#include "expror.h"
#include "charset.h"
#include "escape.h"
#include "lfile.h"
#include "expror.h"
#include "baseset.h"
#include "chrset.h"

struct _node* expr(base_set ** ta,Buffer* mbuf, char *c,struct _lfile* lfile); /* char_set** */
struct _node* apply_def(base_set** ta,Buffer* mbuf,char* c, struct _lfile* lfile); /* char_set** */

#endif
