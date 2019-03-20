#ifndef MLFILE_H
#define MLFILE_H

#include "buffer.h"
#include "tree.h"
#include "set.h"

struct _lfile {
    buffer **defbuf;
    char ** defs;
    struct _ta *tree;
    struct _iseta *fpos;
    char * decs;
    char * aux;
    int num_defs;
};


#endif
