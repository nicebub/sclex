#include <stdlib.h>
#include <stdio.h>
#include "baseset.h"

static base_set_vtable vtable_base_set={
	 &base_delete_set,
	 &base_add_to_set,
	 &base_remove_from_set,
	 &base_merge_sets,
	 &base_copy_sets,
	 &base_sets_are_same,
	 &base_is_in_set,
	 &base_display_set,
	 &base_set_used,
	 &base_get_value_by_index_set,
	 &base_set_size
		 /* current implementation doesn't need these yet
		  * &base_msort_set,
		  * &base_msort_set_helper,
		  * &base_msmerge_sets,
		  */
};

void init_base_set_vtable(){
	vtable_base_set.is_in_set = &base_is_in_set;
	vtable_base_set.add_to_set = &base_add_to_set;
	vtable_base_set.remove_from_set = &base_remove_from_set;
	vtable_base_set.merge_sets = &base_merge_sets;
	vtable_base_set.copy_sets = &base_copy_sets;
	vtable_base_set.sets_are_same = &base_sets_are_same;
	vtable_base_set.display_set = &base_display_set;
	vtable_base_set.delete_set = &base_delete_set;

	/* current implementation doesn't need these yet
	 * vtable_base_set.msort_set_helper = &base_msort_set_helper;
	 * vtable_base_set.msmerge_sets = &base_msmerge_sets;
	 * vtable_base_set.msort_set = &base_msort_set;
	 */
}


base_set* new_set(size_t size){
	return new_base_set(size);
}

void delete_set(base_set* set){
    if(set)
	   set->vtable->delete_set(set);
}

int is_in_set(base_set * set, int value){
	if(set)
	    return set->vtable->is_in_set(set,value);
    return -1;
}
void add_to_set(base_set ** set, int value){
	if(set && *set)
	    (*set)->vtable->add_to_set(set,value);
}
void remove_from_set(base_set ** set, int value){
	if(set && *set)
	(*set)->vtable->remove_from_set(set,value);
}
base_set * merge_sets(base_set * set1, base_set* set2){
	if(set1 && set2)
	    return set1->vtable->merge_sets(set1,set2);
    return NULL;
}
base_set * copy_sets(base_set * set){
	if(set)
	    return set->vtable->copy_sets(set);
    return NULL;
}
int sets_are_same(base_set* set1, base_set* set2){
	if(set1 && set2)
	    return set1->vtable->sets_are_same(set1,set2);
    return -1;
}
void display_set(base_set* set){
    if(set)
	   set->vtable->display_set(set);
}

size_t set_used(base_set* set){
    if(set)
	   return set->vtable->set_used(set);
    return 0;
}
void* get_value_by_index_set(base_set* set, size_t index){
    if(set)
	   return set->vtable->get_value_by_index_set(set,index);
    return NULL;
}
size_t set_size(base_set* set){
	if(set)
	    return set->vtable->set_size(set);
    return 0;
}

/* current implementation doesn't need these yet
 * base_set * msort_set(base_set* set){
 *	return set->vtable->msort_set(set);
 * }
 * base_set * msort_set_helper(base_set* set,int start,int finish){
 *	return set->vtable->msort_set_helper(set,start,finish);
 * }
 * base_set * msmerge_sets(base_set **left,base_set **right){
 *	return (*left)->vtable->msmerge_sets(left,right);
 * }
 */

base_set* new_base_set(size_t size){
	base_set * set = malloc(sizeof(base_set));
	if(!set){
		NEWSETERROR(set);
		return NULL;
	}	
	set->vtable = &vtable_base_set;
	set->size=size;
	set->used=0;
	set->uniq=0;
	set->id=0;
	return set;
}

void base_delete_set(base_set* set){
	if(set){
		set->vtable = NULL;
		free(set);
		set=NULL;
	}
}	

int base_is_in_set(base_set * set, int value){
	return 0;
}
void base_add_to_set(base_set ** set, int value){
}
void base_remove_from_set(base_set ** set, int value){
}
base_set * base_merge_sets(base_set * set1, base_set* set2){
	return 0;
}
base_set * base_copy_sets(base_set * set){
	return 0;
}
int base_sets_are_same(base_set* set1, base_set* set2){
	return 0;
}
void base_display_set(base_set* set){
	printf("vtable:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
	(void*)set->vtable, set->size,set->used,set->uniq,set->id);
}
size_t base_set_used(base_set* set){
	return set->used;
}
void* base_get_value_by_index_set(base_set* set, size_t index){
	return NULL;
}
size_t base_set_size(base_set* set){
	return set->size;
}
/*
void char_display_set(char_set* set){
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
	(void*)set->super.vtable,(void*)set->values,set->size,set->used,set->uniq,set->id);
	if(set->used >0){
		size_t r;
		for(r=0;r<set->used;r++)
			printf("%c ",set->values[r]);
		printf("\n");
	}
}*/
/* current implementation doesn't need these yet
 * base_set * base_msort_set(base_set* set){
 * 	return 0;
 * }
 * base_set * base_msort_set_helper(base_set* set,int start,int finish){
 *	return 0;
 * }
 * base_set * base_msmerge_sets(base_set **left,base_set **right){
 * 	return 0;
 * }
 */
