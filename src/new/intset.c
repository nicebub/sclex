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
	int_set* iset = malloc(sizeof(int_set));
	if(!iset){
		NEWSETERROR(iset);
		return NULL;
	}
	iset->values = NULL;
	iset->super.vtable = &int_set_vtable;
    iset->values = malloc(sizeof(int)*size);
	if(!iset->values){
		NEWSETERROR(values);
		return NULL;
	}
    iset->size = size;
    iset->used = 0;
    iset->uniq = 0;
    iset->id = 0;
	return iset;
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
	int y;
	if(!set)
		return 0;
	 for(y=0;y<set->used && set->values[y]<=value;y++){
		if(set->values[y] == value)
			return 1;
	}
	return 0;
}
int int_sets_are_same(int_set* set1, int_set* set2){
	int g;
    if(!set1 || !set2)
		return 0;
	if(set1->used != set2->used)
		return 0;

	for(g=0; g < set1->used;g++)
		if(set1->values[g] != set2->values[g])
			return 0;

	return 1;
}

#define INCREMENT_SIZE 10

void int_add_to_set(int_set ** set, int value){
	int_set *setptr, *tempset;
	int y;
	setptr = tempset= NULL;
	if(!set || !*set)
		return;

	setptr = *set;
	if(setptr->used == setptr->size)
		tempset = new_int_set(setptr->size+INCREMENT_SIZE);
	else
		tempset = new_int_set(setptr->size);
/*		return;*/
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}

	for(y=0;y<setptr->used;y++){
		if(setptr->values[y] == value){
	    	int_delete_set(tempset);
			tempset = NULL;
	    	return;
		}
		if(setptr->values[y] > value){
			int a;
	    	tempset->values[y] = value;
	    	for(a=y;a<setptr->used;a++){
				tempset->values[a+1] = setptr->values[a];
			}
			tempset->used = setptr->used + 1;
	    	int_delete_set(setptr);
	    	setptr = NULL;
	    	*set = tempset;
	    	return;
		}
		tempset->values[y] = setptr->values[y];
 	}
	tempset->values[y] = value;
	tempset->used = setptr->used + 1;
	int_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
void int_remove_from_set(int_set ** set, int value){
	int_set *setptr, *tempset;
	int a;
	setptr =tempset=NULL;
	if(!set || !*set)
		return;
	setptr = *set;
	tempset = new_int_set(setptr->size);
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}	
	for(a=0;a<setptr->used;a++){
		if(setptr->values[a] == value){
			continue;
		}
		tempset->values[tempset->used] = setptr->values[a];
		tempset->used++;
	}
	int_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
int_set * int_merge_sets(int_set * set1, int_set* set2){
	int a;
    int_set *tempset;
    tempset = NULL;
    if(!set1 || !set2)
		return NULL;
	tempset = int_copy_sets(set1);
	if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	}	
	for(a=0;a<set2->used;a++){
		int_add_to_set(&tempset,set2->values[a]);
	 }
	 return tempset;
}
int_set * int_copy_sets(int_set * set){
	 int a;
	int_set *tempset;
	tempset = NULL;

    if(!set)
		return NULL;

	 tempset = new_int_set(set->size);

	 if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	 }
	 for(a=0;a<set->used;a++)
		int_add_to_set(&tempset,set->values[a]);
	 tempset->uniq = set->uniq;
	 return tempset;
}
void int_display_set(int_set* set){
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
	(void*)set->super.vtable,(void*)set->values,set->size,set->used,set->uniq,set->id);
	if(set->used >0){
		int r;
		for(r=0;r<set->used;r++)
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