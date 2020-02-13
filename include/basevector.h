#ifndef _MYVEC_H
#define _MYVEC_H

#include <stddef.h>

#define NEWVECERROR(in) printf("couldn't create new " #in " vector\n");

typedef struct _base_vector base_vector;
typedef struct _base_vector_vtable base_vector_vtable;

struct _base_vector{
	base_vector_vtable * vtable;
	size_t size;
	size_t used;
	size_t id;
};

struct _base_vector_vtable{
	void (*delete_vector)(base_vector* vec);
	void (*add_to_vector)(void* to_add, base_vector* vec);
	void (*display_vector)(base_vector* vec);
	size_t (*vector_used)(base_vector* vec);
	void ** (*get_by_index_in_vector)(base_vector* vec, size_t index);
	size_t (*vector_size)(base_vector* vec);
	void (*set_vector_used)(base_vector* vec,size_t used);
	void (*set_vector_size)(base_vector* vec,size_t size);
};

base_vector* new_vector(size_t size);


void delete_vector(base_vector* vec);
void add_to_vector(void* to_add, base_vector* vec);
void display_vector(base_vector* vec);
size_t vector_used(base_vector* vec);
void ** get_by_index_in_vector(base_vector* vec, size_t index);
size_t vector_size(base_vector* vec);
void set_vector_used(base_vector* vec,size_t used);
void set_vector_size(base_vector* vec,size_t size);

base_vector* new_base_vector(size_t size);
void base_delete_vector(base_vector* vec);
void base_add_to_vector(void* to_add, base_vector* vec);
void base_display_vector(base_vector* vec);
size_t base_vector_used(base_vector* vec);
void ** base_get_by_index_in_vector(base_vector* vec, size_t index);
size_t base_vector_size(base_vector* vec);
void base_set_vector_used(base_vector* vec,size_t used);
void base_set_vector_size(base_vector* vec,size_t size);

#endif
