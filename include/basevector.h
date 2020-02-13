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
};

base_vector* new_vector(size_t size);


void delete_vector(base_vector* vec);
void add_to_vector(void* to_add, base_vector* vec);
void display_vector(base_vector* vec);

base_vector* new_base_vector(size_t size);
void base_delete_vector(base_vector* vec);
void base_add_to_vector(void* to_add, base_vector* vec);
void base_display_vector(base_vector* vec);



#endif