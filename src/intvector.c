#include <stdio.h>
#include "basevector.h"
#include "intvector.h"
#include "baseset.h"
#include "intset.h"

static base_vector_vtable int_vector_vtable = {
   &int_delete_vector,
   &int_add_to_vector,
  #ifdef LOGGING
   &int_display_vector,
  #endif // LOGGING
   &int_vector_used,
   &int_get_by_index_in_vector,
   &int_set_by_index_in_vector,
   &int_vector_size,
   &int_set_vector_used,
   &int_set_vector_size
};

base_vector* new_int_vector(int size){
	int i;
	int_vector* vec;
	if(size <= 0){
		NEWVECERROR(vec);
		return NULL;
	}
	vec = malloc(sizeof(int_vector));
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
    base_set_vector_size((base_vector*)vec,size);
    base_set_vector_used((base_vector*)vec,0);
    vec->super.id = 0;
	return (base_vector*)vec;
}

base_vector* new_int_vector_with_init_sets(int vec_size, int data_size){
	base_vector * vec;
	int r;
	vec = new_int_vector(vec_size);
		if(!vec){
			NEWVECERROR(vec);
			return NULL;
		}
		if(data_size <= 0){
		NEWVECERROR(vec);
		int_delete_vector(vec);
		return NULL;
	}
    for(r=0;r<vec_size;r++){
		int_set_by_index_in_vector(vec,r,NULL);
		int_set_by_index_in_vector(vec,r,new_int_set(data_size));
/*	   *get_by_index_in_vector(file->fpos,r) = new_int_set(vector_size(file->fpos));*/
	   if(*(int_vector**)int_get_by_index_in_vector(vec,r) == NULL){
		  NEWVECERROR(5);
		  int_delete_vector(vec);
		  vec = NULL;
		  return NULL;
	   }
   }
   int_set_vector_used(vec,0);
   return vec;
}

void int_delete_vector(/*int* */base_vector* vec){
	if(vec){
	    int_vector* nvec = (int_vector*)vec;
		int i;
		for(i=0;i<base_vector_used(vec);i++){
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
		if(base_vector_used(vec) >= base_vector_size(vec))
			return;
		nvec->values[base_vector_used(vec)] = (int_set*)copy_sets(data);
		base_set_vector_used(vec,base_vector_used(vec)+1);
	}
}

#ifdef LOGGING
void int_display_vector(base_vector* vec)
{
	int i;
	if(vec){
		for(i=0;i<base_vector_used(vec);i++)
			display_set(*get_by_index_in_vector(vec,i));
	}
}
#endif // LOGGING
int int_vector_used(base_vector* vec){
    int_vector* nvec;
	if(!vec) return 0;
	nvec = (int_vector*)vec;
	return base_vector_used(&nvec->super);
}

/*int_set** */void ** int_get_by_index_in_vector(base_vector* vec, int index){
	int_vector* nvec;
	if(!vec || index < 0 || index >= base_vector_size(vec))
		return NULL;
	nvec = (int_vector*)vec;
	return (void**)&nvec->values[index];
}

void int_set_by_index_in_vector(base_vector* vec, int index,void* value){
	if(vec && value && index >= 0 && index < base_vector_size(vec)){
		int_vector* nvec = (int_vector*)vec;
/*		int_set* nvalue = (int_set*) value;*/
	    if(value && nvec->values[index] == NULL)
		  base_set_vector_used(vec,base_vector_used(vec)+1);
		nvec->values[index] = (int_set*)int_copy_sets(value);
	}
}

int int_vector_size(base_vector* vec){
    int_vector* nvec;
	if(!vec) return 0;
	nvec = (int_vector*)vec;
	return base_vector_size(&nvec->super);
}
void int_set_vector_used(base_vector* vec, int used){
	int_vector* nvec;
	if(!vec || used < 0 || used > base_vector_size(vec)) return;
	nvec = (int_vector*)vec;
	base_set_vector_used(&nvec->super,used);
}
void int_set_vector_size(base_vector* vec, int size){
	int_vector* nvec;
	if(!vec || size < 0 || size > base_vector_size(vec)) return;
	nvec = (int_vector*)vec;
	base_set_vector_size(&nvec->super,size);
}
