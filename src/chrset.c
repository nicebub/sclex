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
 &char_display_set
/* current implementation doesn't need these yet
 * &char_msort_set,
 * &char_msort_set_helper,
 * &char_msmerge_sets,
 */
};

char_set* new_char_set(size_t size){
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
		return NULL;
	}
    set->super.size = size;
    set->super.used = 0;
    set->super.uniq = 0;
    set->super.id = 0;
	return set;
}
void char_delete_set(char_set* set){
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
int char_is_in_set(char_set * set, char value){
	size_t y;
	if(!set)
		return 0;
	 for(y=0;y<set->super.used && set->values[y]<=value;y++){
		if(set->values[y] == value)
			return 1;
	}
	return 0;
}
int char_sets_are_same(char_set* set1, char_set* set2){
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

void char_add_to_set(char_set ** set, char value){
	char_set *setptr, *tempset;
	size_t y;
	setptr = tempset= NULL;
	if(!set || !*set)
		return;

	setptr = *set;
	if(setptr->super.used == setptr->super.size)
		tempset = new_char_set(setptr->super.size+INCREMENT_SIZE);
	else
		tempset = new_char_set(setptr->super.size);
/*		return;*/
	if(!tempset){
		NEWSETERROR(tempset);
		return;
	}

	for(y=0;y<setptr->super.used;y++){
		if(setptr->values[y] == value){
	    	char_delete_set(tempset);
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
	    	char_delete_set(setptr);
	    	setptr = NULL;
	    	*set = tempset;
	    	return;
		}
		tempset->values[y] = setptr->values[y];
 	}
	tempset->values[y] = value;
	tempset->super.used = setptr->super.used + 1;
	char_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
void char_remove_from_set(char_set ** set, char value){
	char_set *setptr, *tempset;
	size_t a;
	setptr =tempset=NULL;
	if(!set || !*set)
		return;
	setptr = *set;
	tempset = new_char_set(setptr->super.size);
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
	char_delete_set(setptr);
	setptr = NULL;
	*set = tempset;
	return;
}
char_set * char_merge_sets(char_set * set1, char_set* set2){
	size_t a;
    char_set *tempset;
    tempset = NULL;
    if(!set1 || !set2)
		return NULL;
	tempset = char_copy_sets(set1);
	if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	}	
	for(a=0;a<set2->super.used;a++){
		char_add_to_set(&tempset,set2->values[a]);
	 }
	 return tempset;
}
char_set * char_copy_sets(char_set * set){
	 size_t a;
	char_set *tempset;
	tempset = NULL;

    if(!set)
		return NULL;

	 tempset = new_char_set(set->super.size);

	 if(!tempset){
		NEWSETERROR(tempset);
		return NULL;
	 }
	 for(a=0;a<set->super.used;a++)
		char_add_to_set(&tempset,set->values[a]);
	 tempset->super.uniq = set->super.uniq;
	 return tempset;
}
void char_display_set(char_set* set){
	printf("vtable:%p set:%p size: %ld used: %ld uniq: %ld id: %ld\n", 
		(void*)set->super.vtable,(void*)set->values,set->super.size,set->super.used,
		set->super.uniq,set->super.id);
	if(set->super.used >0){
		size_t r;
		for(r=0;r<set->super.used;r++)
			printf("%c ",set->values[r]);
		printf("\n");
	}
}
/* current implementation doesn't need these yet
 * char_set * char_msort_set(char_set* set){
 *	return 0;
 * }
 * char_set * char_msort_set_helper(char_set* set,int start,int finish){
 *	return 0;
 * }
 * char_set * char_msmerge_sets(char_set **left,char_set **right){
 *	return 0;
 * }
 */