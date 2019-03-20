#ifndef MTYPE_H
#define MTYPE_H
#include <stdlib.h>
#include <string.h>

#define TINIT_SIZE 16
#define TRSIZE_AMT 10


struct _type {
    char * name;
    int value;
    struct _type *components;
};

struct _tsys {
    // array of available types
    struct _type ** type;
    int size;
    int used;
};

#endif
