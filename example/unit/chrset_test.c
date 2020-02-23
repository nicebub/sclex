#include <stdio.h>
#include "chrset.h"
#include "baseset.h"

#define is_num_in_set(set,num) 	if(is_in_set((set),(num))) \
		printf("%c is in set\n",(num)); \
	else \
		printf("%c not in set\n",(num));

#define are_they_the_same(set1,set2) 	if(sets_are_same((set1),(set2))) \
		printf("sets " #set1 " and " #set2 " are same\n"); \
	else \
			printf("sets " #set1 " and " #set2 " are not the same\n");

int main(){
	char_set *set1, *set3, *set4, *set5, *set6;
	base_set *set2, **setptr;
	char num;
	
	setptr = NULL;
	set1 = set2 = set3 = set4 = set5 = set6 = NULL;
	set1 = new_char_set(4);

	display_set(set1);
	setptr = &set1;

	set2 = new_base_set(10);

	display_set(*setptr);
	display_set(set2);

	add_to_set(&set1,'a');
	display_set(set1);

	add_to_set(&set1,'b');
	display_set(set1);

	add_to_set(&set1,'c');
	add_to_set(&set1,'d');
	add_to_set(&set1,'e');

	display_set(set1);	

	display_set(*setptr);

	add_to_set(&set1,'e');
	add_to_set(&set1,'h');
	add_to_set(&set1,'f');

	add_to_set(&set1,'z');
	display_set(set1);
	num='a';
	is_num_in_set(set1,num);

	num='c';
	is_num_in_set(set1,num);

	remove_from_set(&set1,'l');
    display_set(set1);
    remove_from_set(&set1,'z');
	display_set(set1);
	num='g';
	is_num_in_set(set1,num);

	num='f';
	is_num_in_set(set1,num);

	num='z';
	is_num_in_set(set1,num);

	are_they_the_same(set1,set1);

	are_they_the_same(set1,set2);

	set3 = new_char_set(2);
	add_to_set(&set3,'a');
	add_to_set(&set3,'b');
	add_to_set(&set3,'e');
	add_to_set(&set3,'d');
	add_to_set(&set3,'h');
	add_to_set(&set3,'z');

	are_they_the_same(set1,set3);

	are_they_the_same(set3,set1);

	printf("adding element to set3\n");
	add_to_set(&set3,'x');
	are_they_the_same(set1,set3);
	are_they_the_same(set3,set1);

	printf("removing element from set3\n");
	remove_from_set(&set3,'e');
	are_they_the_same(set3,set1);

	are_they_the_same(set3,set4);

	add_to_set(&set3,'r');
	add_to_set(&set3, 's');
	set4 = copy_sets(set3);
	display_set(set3);
	display_set(set4);
	
	are_they_the_same(set4,set3);
	printf("adding element to set4\n");
	add_to_set(&set4,'t');
	display_set(set3);
	display_set(set4);
	are_they_the_same(set4,set3);

	set5 = new_char_set(10);
	add_to_set(&set5,'q');
	add_to_set(&set5,'m');
	add_to_set(&set5,'o');
	add_to_set(&set5,'p');
	
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
