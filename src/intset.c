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
 &int_display_set
/* current implementation doesn't need these yet
 * &int_msort_set,
 * &int_msort_set_helper,
 * &int_msmerge_sets,
 */
};

int_set* new_int_set(size_t size){
	int_set* set = malloc(sizeof(int_set));
	if(!set){
		NEWSETERROR(set);
		return NULL;
	}
	set->values = NULL;
	set->super.vtable = &int_set_vtable;
    set->values = malloc(sizeof(int)*size);
	if(!set->values){
		NEWSETERROR(values);
		return NULL;
	}
    set->super.size = size;
    set->super.used = 0;
    set->super.uniq = 0;
    set->super.id = 0;
	return set;
}
void int_delete_set(int_set* set){
	if(set){
		if(set->values){
			free(set->values);
			set->values = NULL;
		}
		set->super.vtable = NULL;
		free(set);
		set = NULL;
	}
}
int int_is_in_set(int_set * set, int value){
	size_t y;
	if(!set)
		return 0;
	 for(y=0;y<set->super.used && set->values[y]<=value;y++){
		if(set->values[y] == value)
			return 1;
	}
	return 0;
}
int int_sets_are_same(int_set* set1, int_set* set2){
	size_t g;
    if(!set1 || !set2)
		return 0;
	if(set1->super.used != set2->super.used)
		return 0;

	for(g=0; g < set1->super.used;g++)
		if(set1->values[g] != set2->values[g])
			return 0;

	return 1;
}

#define INCREMENT_SIZE 10

void int_add_to_set(int_set ** set, int value){
	int_set *setptr, *tempset;
	size_t y;
	setptr = tempset= NULL;
	if(!set || !*set)
		return;

	setptr = *set;
	if(setptr->super.used == setptr->super.size)
		tempset = new_int_set(setptr->super.size+INCREMENT_SIZE);
	else
		tempset = new_int_set(setptr->super.size);
/*		return;*/
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}

	for(y=0;y<setptr->super.used;y++){
		if(setptr->values[y] == value){
	    	int_delete_set(tempset);
			tempset = NULL;
	    	return;
		}
		if(setptr->values[y] > value){
			size_t a;
	    	tempset->values[y] = value;
	    	for(a=y;a<setptr->super.used;a++){
				tempset->values[a+1] = setptr->values[a];
			}
			tempset->super.used = setptr->super.used + 1;
	    	int_delete_set(setptr);
	    	setptr = NULL;
	    	*set = tempset;
	    	return;
		}
		tempset->values[y] = setptr->values[y];
 	}
	tempset->values[y] = value;
	tempset->super.used = setptr->super.used + 1;
	int_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
void int_remove_from_set(int_set ** set, int value){
	int_set *setptr, *tempset;
	size_t a;
	setptr =tempset=NULL;
	if(!set || !*set)
		return;
	setptr = *set;
	tempset = new_int_set(setptr->super.size);
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}	
	for(a=0;a<setptr->super.used;a++){
		if(setptr->values[a] == value){
			continue;
		}
		tempset->values[tempset->super.used] = setptr->values[a];
		tempset->super.used++;
	}
	int_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
int_set * int_merge_sets(int_set * set1, int_set* set2){
	size_t a;
    int_set *tempset;
    tempset = NULL;
    if(!set1 || !set2)
		return NULL;
	tempset = int_copy_sets(set1);
	if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	}	
	for(a=0;a<set2->super.used;a++){
		int_add_to_set(&tempset,set2->values[a]);
	 }
	 return tempset;
}
int_set * int_copy_sets(int_set * set){
	 size_t a;
	int_set *tempset;
	tempset = NULL;

    if(!set)
		return NULL;

	 tempset = new_int_set(set->super.size);

	 if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	 }
	 for(a=0;a<set->super.used;a++)
		int_add_to_set(&tempset,set->values[a]);
	 tempset->super.uniq = set->super.uniq;
	 return tempset;
}
void int_display_set(int_set* set){
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
		(void*)set->super.vtable,(void*)set->values,set->super.size,set->super.used,
		set->super.uniq,set->super.id);
	if(set->super.used >0){
		size_t r;
		for(r=0;r<set->super.used;r++)
			printf("%d ",set->values[r]);
		printf("\n");
	}
}
/* current implementation doesn't need these yet
 * int_set * int_msort_set(int_set* set){
 *	return 0;
 * }
 * int_set * int_msort_set_helper(int_set* set,int start,int finish){
 *	return 0;
 * }
 * int_set * int_msmerge_sets(int_set **left,int_set **right){
 *	return 0;
 * }
 */