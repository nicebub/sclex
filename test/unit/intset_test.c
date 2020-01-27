#include "intset.h"
#include "baseset.h"
int main(){
	int_set *set1;
	base_set *set2, *setptr;
	set1 = new_int_set(10);
	display_set(set1);
	setptr = set1;
	set2 = new_base_set(10);
	display_set(setptr);
	display_set(set2);

	delete_set(set1);
	delete_set(set2);
	set1 =NULL;
	set2 = NULL;
	setptr=NULL;
	return 0;
}