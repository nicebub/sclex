#ifndef MDECS_H
#define MDECS_H

#include "buffer.h"
#include "funcs.h"
#include "lfile.h"

char* declarations(buffer* mbuf, char*c,struct _lfile* file );
void read_definitions(buffer* mbuf,char* c,struct _lfile * file);

#endif
