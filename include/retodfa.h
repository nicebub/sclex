#ifndef RETODFA_H
#define RETODFA_H

#include "tree.h"
#include "funcs.h"
#include "set.h"

#define firstpos(h) pos(h,1)
#define lastpos(h)  pos(h,0)

struct _set {
    struct _hash *	hash;
};

int nullable(struct _node **);
struct _iset* pos(struct _node **,int);
struct _iset* followpos(struct _iseta**,struct _node **);
char gcfprint(char c);

#endif
