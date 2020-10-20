#ifndef MDECS_H
#define MDECS_H

#include "basebuffer.h"
#include "funcs.h"
#include "lfile.h"

char* declarations(Buffer* mbuf, char*c,struct _lfile* file );
void read_definitions(Buffer* mbuf,char* c,struct _lfile * file);

#endif
