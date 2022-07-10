#include "basevector.h"
#include "chrvector.h"
#include <stdio.h>
#include "baseset.h"
#include "chrset.h"

static base_vector_vtable char_vector_vtable = {
 &char_delete_vector,
 &char_add_to_vector,
 #ifdef LOGGING
 &char_display_vector,
 #endif // LOGGING
 &char_vector_used,
 &char_get_by_index_in_vector,
 &char_set_by_index_in_vector,
 &char_vector_size,
 &char_set_vector_used,
 &char_set_vector_size
};

base_vector* new_char_vector(int size){
	int i;
	char_vector* vec;
	if(size <= 0){
		NEWVECERROR(vec);
		return NULL;
	}
	vec  = malloc(sizeof(char_vector));
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
    base_set_vector_size((base_vector*)vec,size);
    base_set_vector_used((base_vector*)vec,0);
    vec->super.id = 0;
	return (base_vector*)vec;
}

base_vector* new_char_vector_with_init_sets(int vec_size, int data_size){
	base_vector * vec;
	int r;
	vec = new_char_vector(vec_size);
	if(!vec){
		if(!vec){
			NEWVECERROR(vec);
			return NULL;
		}
	}
	if(data_size <= 0){
		NEWVECERROR(vec);
		char_delete_vector(vec);
		return NULL;
	}
    for(r=0;r<vec_size;r++){
		char_set_by_index_in_vector(vec,r,NULL);
		char_set_by_index_in_vector(vec,r,new_char_set(data_size));
/*	   *get_by_index_in_vector(file->fpos,r) = new_int_set(vector_size(file->fpos));*/
	   if(*(char_vector**)char_get_by_index_in_vector(vec,r) == NULL){
		  NEWVECERROR(5);
		  char_delete_vector(vec);
		  vec = NULL;
		  return NULL;
	   }
   }
   char_set_vector_used(vec,0);
   return vec;
}
void char_delete_vector(/*char* */base_vector* vec){
	if(vec){
	    char_vector* nvec = (char_vector*)vec;
		int i;
		for(i=0;i<base_vector_used(vec);i++){
			char_delete_set(*(base_set**)char_get_by_index_in_vector(vec,i));
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
		if(base_vector_used(vec) >= base_vector_size(vec))
			return;
		nvec->values[base_vector_used(vec)] = char_copy_sets(data);
		base_set_vector_used(vec,base_vector_used(vec)+1);
	}
}

#ifdef LOGGING
void char_display_vector(base_vector* vec)
{
	int i;
	if(vec){
		for(i=0;i<base_vector_used(vec);i++)
			char_display_set(*char_get_by_index_in_vector(vec,i));
	}
}
#endif //LOGGING
int char_vector_used(base_vector* vec){
    char_vector* nvec;
	if(!vec) return 0;
	nvec = (char_vector*)vec;
	return base_vector_used(&nvec->super);
}

/*char_set** */void ** char_get_by_index_in_vector(base_vector* vec, int index){
	char_vector* nvec;
	if(!vec || index < 0 || index >= base_vector_size(vec))
		return NULL;
	nvec = (char_vector*)vec;
	return (void**)&nvec->values[index];
}

void char_set_by_index_in_vector(base_vector* vec, int index,void* value){
	if(vec && index >=0 && index < base_vector_size(vec)){
		char_vector* nvec = (char_vector*)vec;
/*		char_set* nvalue = (char_set*) value;*/
	    if(value && nvec->values[index] == NULL)
		  base_set_vector_used(vec,base_vector_used(vec)+1);
		nvec->values[index] = char_copy_sets(value);
	}
}

int char_vector_size(base_vector* vec){
    char_vector* nvec;
	if(!vec) return 0;
	nvec = (char_vector*)vec;
	return base_vector_size(&nvec->super);
}
void char_set_vector_used(base_vector* vec, int used){
    char_vector* nvec;
	if(!vec || used < 0 || used > base_vector_size(vec)) return;
	nvec = (char_vector*)vec;
	base_set_vector_used(&nvec->super,used);
}
void char_set_vector_size(base_vector* vec, int size){
    char_vector* nvec;
	if(!vec || size < 0 || size > base_vector_size(vec)) return;
	nvec = (char_vector*)vec;
	base_set_vector_size(&nvec->super,size);
}
