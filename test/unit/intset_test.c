#include <stdio.h>
#include "intset.h"
#include "baseset.h"

#define is_num_in_set(set,num) 	if(is_in_set((set),(num))) \
		printf("%d n set\n",(num)); \
	else \
		printf("%d not in set\n",(num));

#define are_they_the_same(set1,set2) 	if(sets_are_same((set1),(set2))) \
		printf("sets " #set1 " and " #set2 " are same\n"); \
	else \
			printf("sets " #set1 " and " #set2 " are not the same\n");

int main(){
	int_set *set1, *set3, *set4, *set5, *set6;
	base_set *set2, **setptr;
	int num;
	
	setptr = NULL;
	set1 = set2 = set3 = set4 = set5 = set6 = NULL;
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
	num=38;
	is_num_in_set(set1,num);

	num=100;
	is_num_in_set(set1,num);

	remove_from_set(&set1,20);
    display_set(set1);
    remove_from_set(&set1,100);
	display_set(set1);
	num=20;
	is_num_in_set(set1,num);

	num=100;
	is_num_in_set(set1,num);

	num=1000;
	is_num_in_set(set1,num);

	are_they_the_same(set1,set1);

	are_they_the_same(set1,set2);

	set3 = new_int_set(2);
	add_to_set(&set3,38);
	add_to_set(&set3,40);
	add_to_set(&set3,60);
	add_to_set(&set3,600);
	add_to_set(&set3,790);
	add_to_set(&set3,1000);

	are_they_the_same(set1,set3);

	are_they_the_same(set3,set1);

	printf("adding element to set3\n");
	add_to_set(&set3,1001);
	are_they_the_same(set1,set3);
	are_they_the_same(set3,set1);

	printf("removing element from set3\n");
	remove_from_set(&set3,60);
	are_they_the_same(set3,set1);

	are_they_the_same(set3,set4);

	add_to_set(&set3,45);
	add_to_set(&set3, 5676);
	set4 = copy_sets(set3);
	display_set(set3);
	display_set(set4);
	
	are_they_the_same(set4,set3);
	printf("adding element to set4\n");
	add_to_set(&set4,8080);
	display_set(set3);
	display_set(set4);
	are_they_the_same(set4,set3);

	set5 = new_int_set(10);
	add_to_set(&set5,1);
	add_to_set(&set5,2);
	add_to_set(&set5,3);
	add_to_set(&set5,4);
	
	display_set(set5);
	
	set6 = merge_sets(set4,set5);
	display_set(set6);
	
	delete_set(set1);
	delete_set(set2);
	delete_set(set3);
	delete_set(set4);
    delete_set(set5);
    delete_set(set6);
	set1 =NULL;
	set2 = NULL;
	set3 = NULL;
	set4 = NULL;
	setptr=NULL;
	return 0;
}
