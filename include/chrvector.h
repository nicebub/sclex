#ifndef _CHRVEC_H
#define _CHRVEC_H

#include "basevector.h"
#include "chrset.h"

typedef struct _char_vector char_vector;

struct _char_vector {
	base_vector super;
	base_set ** values; /*char_set** */
};

static base_vector_vtable char_vector_vtable;

base_vector* new_char_vector(int size);
base_vector* new_char_vector_with_init_sets(int vec_size, int data_size);

void char_delete_vector(base_vector* vector);
void char_add_to_vector(void* data,base_vector * vector);
#ifdef LOGGING
void char_display_vector(base_vector* vector);
#endif //LOGGING
int char_vector_used(base_vector* vec);
/*char_set** */void** char_get_by_index_in_vector(base_vector* vec, int index);
void char_set_by_index_in_vector(base_vector* vec, int index,void* value);
int char_vector_size(base_vector* vec);
void char_set_vector_used(base_vector* vec, int used);
void char_set_vector_size(base_vector* vec, int size);
#endif
