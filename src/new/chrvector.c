#include "basevector.h"
#include "chrvector.h"
#include <stdio.h>
#include "baseset.h"
#include "chrset.h"

static base_vector_vtable char_vector_vtable = {
 &char_delete_vector,
 &char_add_to_vector,
 &char_display_vector
};

char_vector* new_char_vector(size_t size){
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
    vec->super.size = size;
    vec->super.used = 0;
    vec->super.id = 0;
	return vec;	

}


void char_delete_vector(char_vector* vec){
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

void char_add_to_vector(char_set* data, char_vector* vec){
	if(data && vec){
		if(vec->super.used >= vec->super.size)
			return;
		vec->values[vec->super.used] = copy_sets(data);
		vec->super.used++;
	}
}

void char_display_vector(char_vector* vec){
	int i;
	if(vec){
		for(i=0;i<vec->super.used;i++)
			display_set(vec->values[i]);
	}
}
