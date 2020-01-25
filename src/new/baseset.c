#include <stdlib.h>
#include "../include/new/baseset.h"

static base_set_vtable vtable_base_set;

void init_base_set_vtable(){
	vtable_base_set.is_in_set = &base_is_in_set;
	vtable_base_set.add_to_set = &base_add_to_set;
	vtable_base_set.remove_from_set = &base_remove_from_set;
	vtable_base_set.merge_sets = &base_merge_sets;
	vtable_base_set.copy_sets = &base_copy_sets;
	vtable_base_set.sets_are_same = &base_sets_are_same;
	vtable_base_set.msort_set = &base_msort_set;
	vtable_base_set.msort_set_helper = &base_msort_set_helper;
	vtable_base_set.msmerge_sets = &base_msmerge_sets;
	vtable_base_set.display_set = &base_display_set;
}


base_set* create_set(int size, int type){
	base_set * set = malloc(sizeof(base_set));
	set->vtable = &vtable_base_set;
	set->s = NULL;
	return 0;
}
void delete_set(base_set* set, int type){
	set->vtable->delete_set(set,type);
}

int is_in_set(base_set * set, int value, int type){
	return set->vtable->is_in_set(set,value,type);
}
void add_to_set(base_set ** set, int value, int type){
	(*set)->vtable->add_to_set(set,value,type);
}
void remove_from_set(base_set ** set, int value, int type){
	(*set)->vtable->remove_from_set(set,value,type);
}
base_set * merge_sets(base_set * set1, base_set* set2, int type){
	return set1->vtable->merge_sets(set1,set2,type);
}
base_set * copy_sets(base_set * set, int type){
	return set->vtable->copy_sets(set,type);
}
base_set * sets_are_same(base_set* set1, base_set* set2, int type){
	return set1->vtable->sets_are_same(set1,set2,type);
}
base_set * msort_set(base_set* set){
	return set->vtable->msort_set(set);
}
base_set * msort_set_helper(base_set* set,int start,int finish){
	return set->vtable->msort_set_helper(set,start,finish);
}
base_set * msmerge_sets(base_set **left,base_set **right){
	return (*left)->vtable->msmerge_sets(left,right);
}
void display_set(base_set* set, int type){
	set->vtable->display_set(set,type);
}

base_set* base_create_set(int size, int type){
	return 0;
}

void base_delete_set(base_set* set, int type){
	set->vtable = NULL;
	free(set);
	set=NULL;
}	

int base_is_in_set(base_set * set, int value, int type){
	return 0;
}
void base_add_to_set(base_set ** set, int value, int type){
}
void base_remove_from_set(base_set ** set, int value, int type){
}
base_set * base_merge_sets(base_set * set1, base_set* set2, int type){
	return 0;
}
base_set * base_copy_sets(base_set * set, int type){
	return 0;
}
base_set * base_sets_are_same(base_set* set1, base_set* set2, int type){
	return 0;
}
base_set * base_msort_set(base_set* set){
	return 0;
}
base_set * base_msort_set_helper(base_set* set,int start,int finish){
	return 0;
}
base_set * base_msmerge_sets(base_set **left,base_set **right){
	return 0;
}
void base_display_set(base_set* set, int type){
}
