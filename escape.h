#ifndef MESCAP_H
#define MESCAP_H

#include "buffer.h"
#include "tree.h"
#include "lex_error.h"


struct _node* escape_char(struct _cset **ta,buffer* mbuf,char* c);

#endif