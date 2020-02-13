#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "basevector.h"

static base_vector_vtable vtable_base_vector= {
	&base_delete_vector,
	&base_add_to_vector,
	&base_display_vector
};

base_vector* new_vector(size_t size){
	return new_base_vector(size);
}

void delete_vector(base_vector* vec){
	vec->vtable->delete_vector(vec);
}

void add_to_vector(void* to_add, base_vector* vec){
	vec->vtable->add_to_vector(to_add,vec);
}

void display_vector(base_vector* vec){
	vec->vtable->display_vector(vec);
}

base_vector* new_base_vector(size_t size){
	base_vector* vec = malloc(sizeof(base_vector));
	if(!vec){
		NEWVECERROR(vec);
		return NULL;
	}
	vec->vtable = &vtable_base_vector;
	vec->size = size;
	vec->used = 0;
	vec->id = 0;
	return vec;
}
void base_delete_vector(base_vector* vec){
	if(vec){
		vec->vtable = NULL;
		free(vec);
		vec = NULL;
	}
}
void base_add_to_vector(void* to_add, base_vector* vec){
}

void base_display_vector(base_vector* vec){
	printf("vtable: %p size: %ld used: %ld id: %ld\n",(void*)vec->vtable,
		vec->size,vec->used,vec->id);
}