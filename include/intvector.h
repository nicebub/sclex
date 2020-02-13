#ifndef _INTVEC_H
#define _INTVEC_H

#include "basevector.h"
#include "intset.h"

typedef struct _int_vector int_vector;

struct _int_vector {
	base_vector super;
	int_set ** values;
};

base_vector* new_int_vector(size_t size);

void int_delete_vector(base_vector* vector);	
void int_add_to_vector(void* data,base_vector * vector);
void int_display_vector(base_vector* vector);
size_t int_vector_used(base_vector* vec);
/*int_set** */void** int_get_by_index_in_vector(base_vector* vec, size_t index);
size_t int_vector_size(base_vector* vec);
void int_set_vector_used(base_vector* vec, size_t used);
void int_set_vector_size(base_vector* vec, size_t size);

#endif
