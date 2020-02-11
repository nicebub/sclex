#include <stdio.h>
#include "basevector.h"
#include "intvector.h"
#include "baseset.h"
#include "intset.h"

static base_vector_vtable int_vector_vtable = {
 &int_delete_vector,
 &int_add_to_vector,
 &int_display_vector
};

int_vector* new_int_vector(size_t size){
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
    vec->super.size = size;
    vec->super.used = 0;
    vec->super.id = 0;
	return vec;	
}


void int_delete_vector(int_vector* vec){
	if(vec){
		int i;
		for(i=0;i<vec->super.used;i++){
			delete_set(vec->values[i]);
			vec->values[i] = NULL;
		}
		vec->super.vtable = NULL;
		free(vec);
		vec = NULL;
	}
}

void int_add_to_vector(int_set * data, int_vector* vec){
	if(data && vec){
		if(vec->super.used >= vec->super.size)
			return;
		vec->values[vec->super.used] = copy_sets(data);
		vec->super.used++;
	}
}

void int_display_vector(int_vector* vec){
	int i;
	if(vec){
		for(i=0;i<vec->super.used;i++)
			display_set(vec->values[i]);
	}
}