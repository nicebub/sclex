#ifndef _MYVEC_H
#define _MYVEC_H

#include <stddef.h>
#include "log.h"
#define NEWVECERROR(in) LOG_ERROR("couldn't create new " #in " vector%s","\n");

typedef struct _base_vector base_vector;
typedef struct _base_vector_vtable base_vector_vtable;

struct _base_vector{
	base_vector_vtable * vtable;
	int size;
	int used;
	int id;
};

struct _base_vector_vtable{
	void (*delete_vector)(base_vector* vec);
	void (*add_to_vector)(void* to_add, base_vector* vec);
   #ifdef LOGGING
	void (*display_vector)(base_vector* vec);
   #endif // LOGGING
	int (*vector_used)(base_vector* vec);
	void ** (*get_by_index_in_vector)(base_vector* vec, int index);
	void (*set_by_index_in_vector)(base_vector* vec, int index,void* value);
	int (*vector_size)(base_vector* vec);
	void (*set_vector_used)(base_vector* vec,int used);
	void (*set_vector_size)(base_vector* vec,int size);
};

static base_vector_vtable vtable_base_vector;

base_vector* new_vector(int size);
base_vector* new_vector_with_init_sets(int vec_size, int data_size);

void delete_vector(base_vector* vec);
void add_to_vector(void* to_add, base_vector* vec);
#ifdef LOGGING
void display_vector(base_vector* vec);
#endif // LOGGING
int vector_used(base_vector* vec);
void ** get_by_index_in_vector(base_vector* vec, int index);
void set_by_index_in_vector(base_vector* vec, int index,void* value);
int vector_size(base_vector* vec);
void set_vector_used(base_vector* vec,int used);
void set_vector_size(base_vector* vec,int size);

base_vector* new_base_vector(int size);
base_vector* new_base_vector_with_init_sets(int vec_size, int data_size);
void base_delete_vector(base_vector* vec);
void base_add_to_vector(void* to_add, base_vector* vec);
#ifdef LOGGING
void base_display_vector(base_vector* vec);
#endif // LOGGING
int base_vector_used(base_vector* vec);
void ** base_get_by_index_in_vector(base_vector* vec, int index);
void base_set_by_index_in_vector(base_vector* vec, int index,void* value);
int base_vector_size(base_vector* vec);
void base_set_vector_used(base_vector* vec,int used);
void base_set_vector_size(base_vector* vec,int size);

#endif
