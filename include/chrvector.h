#ifndef _CHRVEC_H
#define _CHRVEC_H

#include "basevector.h"
#include "chrset.h"

typedef struct _char_vector char_vector;

struct _char_vector {
	base_vector super;
	base_set ** values; /*char_set** */
};

base_vector* new_char_vector(size_t size);

void char_delete_vector(base_vector* vector);
void char_add_to_vector(void* data,base_vector * vector);
void char_display_vector(base_vector* vector);
size_t char_vector_used(base_vector* vec);
/*char_set** */void** char_get_by_index_in_vector(base_vector* vec, size_t index);
size_t char_vector_size(base_vector* vec);
void char_set_vector_used(base_vector* vec, size_t used);
void char_set_vector_size(base_vector* vec, size_t size);
#endif
