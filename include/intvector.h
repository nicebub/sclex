#ifndef _INTVEC_H
#define _INTVEC_H

#include "basevector.h"
#include "intset.h"

typedef struct _int_vector int_vector;

struct _int_vector {
	base_vector super;
	int_set ** values;
};

static base_vector_vtable int_vector_vtable;

base_vector* new_int_vector(int size);
base_vector* new_int_vector_with_init_sets(int vec_size, int data_size);

void int_delete_vector(base_vector* vector);	
void int_add_to_vector(void* data,base_vector * vector);
void int_display_vector(base_vector* vector);
int int_vector_used(base_vector* vec);
/*int_set** */void** int_get_by_index_in_vector(base_vector* vec, int index);
void int_set_by_index_in_vector(base_vector* vec, int index,void* value);
int int_vector_size(base_vector* vec);
void int_set_vector_used(base_vector* vec, int used);
void int_set_vector_size(base_vector* vec, int size);

#endif
