#include "chrset.h"
#include <stdio.h>


static base_set_vtable char_set_vtable = {
 &char_delete_set,
 &char_add_to_set,
 &char_remove_from_set,
 &char_merge_sets,
 &char_copy_sets,
 &char_sets_are_same,
 &char_is_in_set,
 &char_display_set,
 &char_set_used,
 &char_get_value_by_index_set,
 &char_set_size
/* current implementation doesn't need these yet
 * &char_msort_set,
 * &char_msort_set_helper,
 * &char_msmerge_sets,
 */
};

base_set* new_char_set(int size){
	char_set* set = malloc(sizeof(char_set));
	if(!set){
		NEWSETERROR(set);
		return NULL;
	}
	set->values = NULL;
	set->super.vtable = &char_set_vtable;
    set->values = malloc(sizeof(char)*size);
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
void char_delete_set(base_set* set){
	if(set){
	    char_set* nset = (char_set*)set;
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
int char_is_in_set(base_set * set, int value){
	int y;
    if(set){
	   for(y=0;y<set_used(set) && *(char*)get_value_by_index_set(set,y)<=value;y++){
		if(*(char*)get_value_by_index_set(set,y) == value)
			return 1;
	   }
    }
	return 0;
}
int char_sets_are_same(base_set* set1, base_set* set2){
	int g;
    char_set* nset1,*nset2;
    if(!set1 || !set2)
		return 0;
    nset1 = (char_set*)set1;
    nset2=(char_set*)set2;
	if(set_used(set1) != set_used(set2))
		return 0;
	for(g=0; g < set_used(set1);g++)
		if(nset1->values[g] != nset2->values[g])
			return 0;

	return 1;
}

#define INCREMENT_SIZE 10

void char_add_to_set(base_set ** set, int value){
	char_set *setptr, *tempset;
	int y;
	setptr = tempset= NULL;
	if(!set || !*set)
		return;

	setptr = (char_set*)*set;
	if(set_used(*set) == set_size(*set))
		tempset = (char_set*)new_char_set(set_size(*set)+INCREMENT_SIZE);
	else
		tempset = (char_set*)new_char_set(set_size(*set));
/*		return;*/
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}

	for(y=0;y<set_used(*set);y++){
		if(setptr->values[y] == value){
	    	char_delete_set((base_set*)tempset);
			tempset = NULL;
	    	return;
		}
		if(*(char*)get_value_by_index_set(*set,y)> value){
			int a;
	    	tempset->values[y] = (char)value;
	    	for(a=y;a<set_used(*set);a++){
				tempset->values[a+1] = setptr->values[a];
			}
			tempset->super.used = setptr->super.used + 1;
	    	char_delete_set(*set);
		    *set = NULL;
		    setptr = NULL;
	    	*set = (base_set*)tempset;
	    	return;
		}
		tempset->values[y] = setptr->values[y];
 	}
	tempset->values[y] = (char)value;
	tempset->super.used = set_used(*set) + 1;
	char_delete_set(*set);
	setptr = NULL;
	*set = (base_set*)tempset;
	return;
}
void char_remove_from_set(base_set ** set, int value){
	char_set *setptr, *tempset;
	int a;
	setptr =tempset=NULL;
	if(!set || !*set)
		return;
	setptr = (char_set*)*set;
	tempset = (char_set*)new_char_set(set_size(*set));
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
	char_delete_set(*set);
	setptr = NULL;
	*set = (base_set*)tempset;
	return;
}
base_set * char_merge_sets(base_set * set1, base_set* set2){
	int a;
    char_set *tempset;
    char_set* nset2;
    tempset = NULL;
    if(!set1 || !set2)
		return NULL;
	tempset = (char_set*)char_copy_sets(set1);
	if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	}
    nset2 = (char_set*) set2;
	for(a=0;a<set_used(set2);a++){
		char_add_to_set((base_set**)&tempset,nset2->values[a]);
	 }
	 return (base_set*)tempset;
}
base_set * char_copy_sets(base_set * set){
	 int a;
	char_set *tempset;
	char_set* nset;
	tempset = NULL;

    if(!set)
		return NULL;

	 tempset =(char_set*) new_char_set(set_size(set));
	 if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	 }
    nset = (char_set*)set;
	 for(a=0;a<set_used(set);a++)
		char_add_to_set((base_set**)&tempset,nset->values[a]);
	 tempset->super.uniq = nset->super.uniq;
	 return (base_set*)tempset;
}
void char_display_set(base_set* set){
    char_set* nset = (char_set*)set;
    printf("vtable:%p set:%p size: %d used: %d uniq: %d id: %d\n", 
		(void*)nset->super.vtable,(void*)nset->values,set_size(set),set_used(set),
		nset->super.uniq,nset->super.id);
	if(set_used(set) >0){
		int r;
		for(r=0;r<set_used(set);r++)
			printf("%c ",*(char*)get_value_by_index_set(set,r));
		printf("\n");
	}
}

int char_set_used(base_set* set){
	char_set* nset = (char_set*)set;
	return base_set_used(&nset->super);
}

void* char_get_value_by_index_set(base_set* set, int index){
	char_set* nset = (char_set*)set;
	return &nset->values[index];
}
int char_set_size(base_set* set){
	char_set* nset = (char_set*)set;
	return base_set_size(&nset->super);
}
/* current implementation doesn't need these yet
 * base_set * char_msort_set(base_set* set){
 *	return 0;
 * }
 * base_set * char_msort_set_helper(base_set* set,int start,int finish){
 *	return 0;
 * }
 * base_set * char_msmerge_sets(base_set **left,base_set **right){
 *	return 0;
 * }
 */
