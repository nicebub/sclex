#include <stdio.h>
#include "basevector.h"
#include "intvector.h"
#include "baseset.h"
#include "intset.h"

static base_vector_vtable int_vector_vtable = {
 &int_delete_vector,
 &int_add_to_vector,
 &int_display_vector,
 &int_vector_used,
 &int_get_by_index_in_vector,
 &int_vector_size,
    &int_set_vector_used,
    &int_set_vector_size
};

base_vector* new_int_vector(size_t size){
	int i;
	int_vector* vec = malloc(sizeof(int_vector));
	if(!vec){
		NEWVECERROR(vec);
		return NULL;
	}
	vec->values = NULL;
	vec->values = malloc(sizeof(int_set*)*size);
	if(!vec->values){
		NEWVECERROR(vec->values);
		free(vec);
		vec = NULL;
		return NULL;
	}
	for(i=0;i<size;i++)
		vec->values[i] = NULL;
	vec->super.vtable = &int_vector_vtable;
    set_vector_size((base_vector*)vec,size);
    set_vector_used((base_vector*)vec,0);
    vec->super.id = 0;
	return (base_vector*)vec;
}


void int_delete_vector(/*int* */base_vector* vec){
	if(vec){
	    int_vector* nvec = (int_vector*)vec;
		size_t i;
		for(i=0;i<vector_used(vec);i++){
			delete_set(*(base_set**)get_by_index_in_vector(vec,i));
			nvec->values[i] = NULL;
		}
		nvec->super.vtable = NULL;
		free(nvec);
		nvec = NULL;
	     vec = NULL;
	}
}

void int_add_to_vector(void* data, base_vector* vec){
	if(data && vec){
	    int_vector* nvec = (int_vector*)vec;
		if(vector_used(vec) >= vector_size(vec))
			return;
		nvec->values[vector_used(vec)] = copy_sets(data);
		set_vector_used(vec,vector_used(vec)+1);
	}
}

void int_display_vector(base_vector* vec){
	size_t i;
	if(vec){
		for(i=0;i<vector_used(vec);i++)
			display_set(get_by_index_in_vector(vec,i));
	}
}

size_t int_vector_used(base_vector* vec){
    int_vector* nvec = (int_vector*)vec;
	return base_vector_used(&nvec->super);
}

/*int_set** */void ** int_get_by_index_in_vector(base_vector* vec, size_t index){
	int_vector* nvec = (int_vector*)vec;
	return (void**)&nvec->values[index];
}
size_t int_vector_size(base_vector* vec){
    int_vector* nvec = (int_vector*)vec;
	return base_vector_size(&nvec->super);
}
void int_set_vector_used(base_vector* vec, size_t used){
	int_vector* nvec = (int_vector*)vec;
	base_set_vector_used(&nvec->super,used);
}
void int_set_vector_size(base_vector* vec, size_t size){
	int_vector* nvec = (int_vector*)vec;
	base_set_vector_size(&nvec->super,size);
}
