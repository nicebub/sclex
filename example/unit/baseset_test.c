#include "baseset.h"
#include <stdio.h>
int main(){
	base_set *set1, *set2, *set3, *set4;
/*	init_base_set_vtable();*/ /* needed to set vtable up for rest of runtime */
	set1 = new_set(10);
	display_set(set1);
	add_to_set(&set1,40); /* doesn't do anything */
	add_to_set(&set1,41); /* doesn't do anything */
	add_to_set(&set1,42); /* doesn't do anything */
	add_to_set(&set1,45); /* doesn't do anything */
	remove_from_set(&set1,44); /* doesn't do anything */
	set2 = new_set(3);
	set3 = merge_sets(set1,set2); /* return NULL so no vtable setup either */
	set4 = new_set(67);
	set3 = copy_sets(set2); /* returns NULL so no vtable setup */
	printf("sets_are_same %d\n",sets_are_same(set2,set4)); /* doesn't do anything */
	printf("is_in_set: %d\n",is_in_set(set1,40)); /* doesn't do anything */


	display_set(set1);
	display_set(set2);
	display_set(set4);
	delete_set(set1);
	delete_set(set2);
/*	delete_set(set3);*/ /* don't delete set3 as it never received memory */
	delete_set(set4);
	set1=set2=set3=set4=NULL;
	return 0;
}
