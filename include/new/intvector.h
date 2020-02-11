#ifndef _INTVEC_H
#define _INTVEC_H

#include "basevector.h"
#include "intset.h"

typedef struct _int_vector int_vector;

struct _int_vector {
	base_vector super;
	int ** values;
};

int_vector* new_int_vector(size_t size);

void int_delete_vector(int_vector* vector);	
void int_add_to_vector(int_set* data,int_vector * vector);
void int_display_vector(int_vector* vector);

#endif