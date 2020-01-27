#include "intset.h"
#include <stdio.h>
static base_set_vtable int_set_vtable = {
 &int_delete_set,
 &int_add_to_set,
 &int_remove_from_set,
 &int_merge_sets,
 &int_copy_sets,
 &int_sets_are_same,
 &int_is_in_set,
 &int_msort_set,
 &int_msort_set_helper,
 &int_msmerge_sets,
 &int_display_set
};

int_set* new_int_set(int size){
	int_set* iset = malloc(sizeof(int_set));
	iset->super.vtable = &int_set_vtable;
    iset->s = malloc(sizeof(int)*size);
    iset->size = size;
	return iset;
}
void int_delete_set(int_set* set){
	if(set){
		if(set->s){
			free(set->s);
			set->s = NULL;
		}
		set->super.vtable = NULL;
		free(set);
		set = NULL;
	}
}
int int_is_in_set(int_set * set, int value){
	return 0;
}
int int_sets_are_same(int_set* set1, int_set* set2){
	return 0;
}
void int_add_to_set(int_set ** set, int value){
	
}
void int_remove_from_set(int_set ** set, int value){
	
}
int_set * int_merge_sets(int_set * set1, int_set* set2){
	return 0;
}
int_set * int_copy_sets(int_set * set){
	return 0;
}
int_set * int_msort_set(int_set* set){
	return 0;
}
int_set * int_msort_set_helper(int_set* set,int start,int finish){
	return 0;
}
int_set * int_msmerge_sets(int_set **left,int_set **right){
	return 0;
}
void int_display_set(int_set* set){
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
	(void*)set->super.vtable,(void*)set->s,set->size,set->used,set->uniq,set->id);
}
