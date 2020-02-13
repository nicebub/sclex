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
 &int_display_set,
 &int_set_used,
 &int_get_value_by_index_set,
 &int_set_used
/* current implementation doesn't need these yet
 * &int_msort_set,
 * &int_msort_set_helper,
 * &int_msmerge_sets,
 */
};

base_set* new_int_set(size_t size){
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
	    free(set);
	    set = NULL;
		return NULL;
	}
    set->super.size = size;
    set->super.used = 0;
    set->super.uniq = 0;
    set->super.id = 0;
	return (base_set*)set;
}
void int_delete_set(base_set* set){
	if(set){
	    int_set* nset = (int_set*)set;
		if(nset->values){
			free(nset->values);
			nset->values = NULL;
		}
		nset->super.vtable = NULL;
		free(nset);
		nset = NULL;
	    set = NULL;
	}
}
int int_is_in_set(base_set * set, int value){
	size_t y;
    if(set){
	   for(y=0;y<set_used(set) && *(int*)get_value_by_index_set(set,y)<=value;y++){
		if(*(int*)get_value_by_index_set(set,y) == value)
			return 1;
	   }
    }
	return 0;
}
int int_sets_are_same(base_set* set1, base_set* set2){
	size_t g;
    int_set* nset1,*nset2;
    if(!set1 || !set2)
		return 0;
    nset1 = (int_set*)set1;
    nset2=(int_set*)set2;
	if(set_used(set1) != set_used(set2))
		return 0;
	for(g=0; g < set_used(set1);g++)
		if(nset1->values[g] != nset2->values[g])
			return 0;

	return 1;
}

#define INCREMENT_SIZE 10

void int_add_to_set(base_set ** set, int value){
	int_set *setptr, *tempset;
	size_t y;
	setptr = tempset= NULL;
	if(!set || !*set)
		return;

	setptr = (int_set*)*set;
	if(set_used(*set) == set_size(*set))
		tempset = (int_set*)new_int_set(set_size(*set)+INCREMENT_SIZE);
	else
		tempset = (int_set*)new_int_set(set_size(*set));
/*		return;*/
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}

	for(y=0;y<set_used(*set);y++){
		if(setptr->values[y] == value){
	    	int_delete_set((base_set*)tempset);
			tempset = NULL;
	    	return;
		}
		if(*(int*)get_value_by_index_set(*set,y)> value){
			size_t a;
	    	tempset->values[y] = value;
	    	for(a=y;a<set_used(*set);a++){
				tempset->values[a+1] = setptr->values[a];
			}
			tempset->super.used = setptr->super.used + 1;
	    	int_delete_set(*set);
		    *set = NULL;
		    setptr = NULL;
	    	*set = (base_set*)tempset;
	    	return;
		}
		tempset->values[y] = setptr->values[y];
 	}
	tempset->values[y] = value;
	tempset->super.used = set_used(*set) + 1;
	int_delete_set(*set);
	setptr = NULL;
	*set = (base_set*)tempset;
	return;
}
void int_remove_from_set(base_set ** set, int value){
	int_set *setptr, *tempset;
	size_t a;
	setptr =tempset=NULL;
	if(!set || !*set)
		return;
	setptr = (int_set*)*set;
	tempset = (int_set*)new_int_set(set_size(*set));
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}	
	for(a=0;a<set_used(*set);a++){
		if(setptr->values[a] == value){
			continue;
		}
		tempset->values[set_used((base_set*)tempset)] = setptr->values[a];
		tempset->super.used++;
	}
	int_delete_set(*set);
	setptr = NULL;
	*set = (base_set*)tempset;
	return;
}
base_set * int_merge_sets(base_set * set1, base_set* set2){
	size_t a;
    int_set *tempset;
    int_set* nset2;
    tempset = NULL;
    if(!set1 || !set2)
		return NULL;
	tempset = (int_set*)int_copy_sets(set1);
	if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	}
    nset2 = (int_set*) set2;
	for(a=0;a<set_used(set2);a++){
		int_add_to_set((base_set**)&tempset,nset2->values[a]);
	 }
	 return (base_set*)tempset;
}
base_set * int_copy_sets(base_set * set){
	 size_t a;
	int_set *tempset;
	int_set* nset;
	tempset = NULL;

    if(!set)
		return NULL;

	 tempset =(int_set*) new_int_set(set_size(set));
	 if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	 }
    nset = (int_set*)set;
	 for(a=0;a<set_used(set);a++)
		int_add_to_set((base_set**)&tempset,nset->values[a]);
	 tempset->super.uniq = nset->super.uniq;
	 return (base_set*)tempset;
}
void int_display_set(base_set* set){
    int_set* nset = (int_set*)set;
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
		(void*)nset->super.vtable,(void*)nset->values,set_size(set),set_used(set),
		nset->super.uniq,nset->super.id);
	if(set_used(set) >0){
		size_t r;
		for(r=0;r<set_used(set);r++)
			printf("%d ",*(int*)get_value_by_index_set(set,r));
		printf("\n");
	}
}

size_t int_set_used(base_set* set){
	int_set* nset = (int_set*)set;
	return base_set_used(&nset->super);
}

void* int_get_value_by_index_set(base_set* set, size_t index){
	int_set* nset = (int_set*)set;
	return &nset->values[index];
}
size_t int_set_size(base_set* set){
	int_set* nset = (int_set*)set;
	return base_set_size(&nset->super);
}
/* current implementation doesn't need these yet
 * base_set * int_msort_set(base_set* set){
 *	return 0;
 * }
 * base_set * int_msort_set_helper(base_set* set,int start,int finish){
 *	return 0;
 * }
 * base_set * int_msmerge_sets(base_set **left,base_set **right){
 *	return 0;
 * }
 */
