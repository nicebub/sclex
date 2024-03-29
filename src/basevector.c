#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "basevector.h"
#include "log.h"

#ifdef __STRICT_ANSI__
#define inline
#endif

static base_vector_vtable vtable_base_vector= {
	&base_delete_vector,
	&base_add_to_vector,
   #ifdef LOGGING
	&base_display_vector,
   #endif // LOGGING
	&base_vector_used,
	&base_get_by_index_in_vector,
	&base_set_by_index_in_vector,
	&base_vector_size,
	&base_set_vector_used,
	&base_set_vector_size
};

base_vector* new_vector(int size){
	return new_base_vector(size);
}
base_vector* new_vector_with_init_sets(int vec_size, int data_size){
	return new_base_vector_with_init_sets(vec_size,data_size);
}

void delete_vector(base_vector* vec){
    if(vec)
	   vec->vtable->delete_vector(vec);
}

void add_to_vector(void* to_add, base_vector* vec){
	if(vec)
	    vec->vtable->add_to_vector(to_add,vec);
}
#ifdef LOGGING
extern inline void display_vector(base_vector* vec)
{
	if(vec)
	    vec->vtable->display_vector(vec);
}
#endif // LOGGING
extern inline int vector_used(base_vector* vec){
	if(vec)
	    return vec->vtable->vector_used(vec);
    return 0;
}

extern inline void ** get_by_index_in_vector(base_vector* vec, int index){
	if(vec)
	    return vec->vtable->get_by_index_in_vector(vec,index);
    return NULL;
}

extern inline void set_by_index_in_vector(base_vector* vec, int index,void* value){
	if(vec && value){
		vec->vtable->set_by_index_in_vector(vec,index,value);
	}
}

extern inline int vector_size(base_vector* vec){
	if(vec)
	    return vec->vtable->vector_size(vec);
    return 0;
}
extern inline void set_vector_used(base_vector* vec,int used){
	if(vec)
	    vec->vtable->set_vector_used(vec,used);
}
extern inline void set_vector_size(base_vector* vec,int size){
    if(vec)
	   vec->vtable->set_vector_size(vec,size);
}

base_vector* new_base_vector_with_init_sets(int vec_size, int data_size){
	return new_base_vector(vec_size);
}

base_vector* new_base_vector(int size){
	base_vector* vec;
	if(size <= 0){
		NEWVECERROR(vec);
		return NULL;
	}
	vec = malloc(sizeof(base_vector));
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
extern inline void base_add_to_vector(void* to_add, base_vector* vec){
    if(vec && to_add)
	   return;
    return;
}

extern inline void base_display_vector(base_vector* vec)
{
    if(vec)
	   LOG_0("vtable: %p size: %d used: %d id: %d\n",(void*)vec->vtable,
		vec->size,vec->used,vec->id);
}

extern inline int base_vector_used(base_vector* vec){
    if(vec)
	return vec->used;
    return 0;
}
extern inline void ** base_get_by_index_in_vector(base_vector* vec, int index){
    if(vec)
		;
    return NULL;
}
extern inline void base_set_by_index_in_vector(base_vector* vec, int index,void* value){
	if(vec && value)
		;
}


extern inline int base_vector_size(base_vector* vec){
    if(vec)
	return vec->size;
    return 0;
}
extern inline void base_set_vector_used(base_vector* vec,int used){
    if(vec)
	   vec->used = used;
}
extern inline void base_set_vector_size(base_vector* vec,int size){
    if(vec)
	   vec->size = size;
}
