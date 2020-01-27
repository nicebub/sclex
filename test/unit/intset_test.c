#include <stdio.h>
#include "intset.h"
#include "baseset.h"
int main(){
	int_set *set1;
	base_set *set2, **setptr;
	int num;
	set1 = new_int_set(4);

	display_set(set1);
	setptr = &set1;

	set2 = new_base_set(10);

	display_set(*setptr);
	display_set(set2);

	add_to_set(&set1,40);
	display_set(set1);

	add_to_set(&set1,38);
	display_set(set1);

	add_to_set(&set1,100);
	add_to_set(&set1,60);
	add_to_set(&set1,790);

	display_set(set1);	

	display_set(*setptr);

	add_to_set(&set1,600);
	add_to_set(&set1,60);
	add_to_set(&set1,790);

	add_to_set(&set1,1000);
	display_set(set1);
	num=100;
	if(is_in_set(set1,num))
		printf("%d n set\n",num);
	else
		printf("%d not in set\n",num);
	remove_from_set(&set1,20);
    display_set(set1);
    remove_from_set(&set1,100);
	display_set(set1);
	num=20;
	if(is_in_set(set1,num))
		printf("%d n set\n",num);
	else
		printf("%d not in set\n",num);
	num=100;
	if(is_in_set(set1,num))
		printf("%d n set\n",num);
	else
		printf("%d not in set\n",num);
	
	delete_set(set1);
	delete_set(set2);

	set1 =NULL;
	set2 = NULL;
	setptr=NULL;
	return 0;
}
