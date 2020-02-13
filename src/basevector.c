#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "basevector.h"

static base_vector_vtable vtable_base_vector= {
	&base_delete_vector,
	&base_add_to_vector,
	&base_display_vector,
	&base_vector_used,
	&base_get_by_index_in_vector,
	&base_vector_size,
	&base_set_vector_used,
	&base_set_vector_size
};

base_vector* new_vector(size_t size){
	return new_base_vector(size);
}

void delete_vector(base_vector* vec){
    if(vec)
	   vec->vtable->delete_vector(vec);
}

void add_to_vector(void* to_add, base_vector* vec){
	if(vec)
	    vec->vtable->add_to_vector(to_add,vec);
}

void display_vector(base_vector* vec){
	if(vec)
	    vec->vtable->display_vector(vec);
}

size_t vector_used(base_vector* vec){
	if(vec)
	    return vec->vtable->vector_used(vec);
    return 0;
}

void ** get_by_index_in_vector(base_vector* vec, size_t index){
	if(vec)
	    return vec->vtable->get_by_index_in_vector(vec,index);
    return NULL;
}
size_t vector_size(base_vector* vec){
	if(vec)
	    return vec->vtable->vector_size(vec);
    return 0;
}
void set_vector_used(base_vector* vec,size_t used){
	if(vec)
	    vec->vtable->set_vector_used(vec,used);
}
void set_vector_size(base_vector* vec,size_t size){
    if(vec)
	   vec->vtable->set_vector_size(vec,size);
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
    if(vec && to_add)
	   return;
    return;
}

void base_display_vector(base_vector* vec){
    if(vec)
	printf("vtable: %p size: %ld used: %ld id: %ld\n",(void*)vec->vtable,
		vec->size,vec->used,vec->id);
}

size_t base_vector_used(base_vector* vec){
    if(vec)
	return vec->used;
    return 0;
}
void ** base_get_by_index_in_vector(base_vector* vec, size_t index){
    if(vec)
	return NULL;
    return NULL;
}
size_t base_vector_size(base_vector* vec){
    if(vec)
	return vec->size;
    return 0;
}
void base_set_vector_used(base_vector* vec,size_t used){
    if(vec)
	   vec->used = used;
}
void base_set_vector_size(base_vector* vec,size_t size){
    if(vec)
	   vec->size = size;
}
