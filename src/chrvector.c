#include "basevector.h"
#include "chrvector.h"
#include <stdio.h>
#include "baseset.h"
#include "chrset.h"

static base_vector_vtable char_vector_vtable = {
 &char_delete_vector,
 &char_add_to_vector,
 &char_display_vector,
 &char_vector_used,
 &char_get_by_index_in_vector,
 &char_set_by_index_in_vector,
 &char_vector_size,
 &char_set_vector_used,
 &char_set_vector_size
};

base_vector* new_char_vector(int size){
	int i;
	char_vector* vec = malloc(sizeof(char_vector));
	if(!vec){
		NEWVECERROR(vec);
		return NULL;
	}
	vec->values = NULL;
	vec->values = malloc(sizeof(char_set*)*size);
	if(!vec->values){
		NEWVECERROR(vec->values);
		free(vec);
		vec = NULL;
		return NULL;
	}
	for(i=0;i<size;i++)
		vec->values[i] = NULL;
	vec->super.vtable = &char_vector_vtable;
    set_vector_size((base_vector*)vec,size);
    set_vector_used((base_vector*)vec,0);
    vec->super.id = 0;
	return (base_vector*)vec;
}


void char_delete_vector(/*char* */base_vector* vec){
	if(vec){
	    char_vector* nvec = (char_vector*)vec;
		int i;
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

void char_add_to_vector(void* data, base_vector* vec){
	if(data && vec){
	    char_vector* nvec = (char_vector*)vec;
		if(vector_used(vec) >= vector_size(vec))
			return;
		nvec->values[vector_used(vec)] = copy_sets(data);
		set_vector_used(vec,vector_used(vec)+1);
	}
}

void char_display_vector(base_vector* vec){
	int i;
	if(vec){
		for(i=0;i<vector_used(vec);i++)
			display_set(*get_by_index_in_vector(vec,i));
	}
}

int char_vector_used(base_vector* vec){
    char_vector* nvec = (char_vector*)vec;
	return base_vector_used(&nvec->super);
}

/*char_set** */void ** char_get_by_index_in_vector(base_vector* vec, int index){
	char_vector* nvec = (char_vector*)vec;
	return (void**)&nvec->values[index];
}

void char_set_by_index_in_vector(base_vector* vec, int index,void* value){
	if(vec && value){
		char_vector* nvec = (char_vector*)vec;
		char_set* nvalue = (char_set*) value;
		nvec->values[index] = value;		
	}
}

int char_vector_size(base_vector* vec){
    char_vector* nvec = (char_vector*)vec;
	return base_vector_size(&nvec->super);
}
void char_set_vector_used(base_vector* vec, int used){
	char_vector* nvec = (char_vector*)vec;
	base_set_vector_used(&nvec->super,used);
}
void char_set_vector_size(base_vector* vec, int size){
	char_vector* nvec = (char_vector*)vec;
	base_set_vector_size(&nvec->super,size);
}
