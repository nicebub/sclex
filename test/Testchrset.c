#include "unity.h"
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



#define SETSZ 5
char_set *set1;

void setUp(void){
	set1 = NULL;
	set1 = new_char_set(SETSZ);
}
void tearDown(void){
	char_delete_set(set1);
	set1 = NULL;
}
void test_inheritance_with_base_pointer(void){
	base_set *bset;
	bset = NULL;
	bset = new_char_set(0);
	TEST_ASSERT_NULL(bset);
	bset = new_char_set(1);
	delete_set(bset);
	bset = NULL;
}


void test_new_and_delete_char_set(void){

	tearDown();

	set1 = new_char_set(0);
	TEST_ASSERT_NULL(set1);

	setUp();
	TEST_ASSERT_NOT_NULL(set1);

	TEST_ASSERT_EQUAL(SETSZ,char_set_size(set1));
	TEST_ASSERT_EQUAL_PTR(NULL,!set1->super.vtable);
	TEST_ASSERT_EQUAL(0,char_set_used(set1));
	TEST_ASSERT_EQUAL(0, set1->super.id);
	TEST_ASSERT_EQUAL(0, set1->super.uniq);
	TEST_ASSERT_EQUAL_PTR(NULL,!set1->values);
	
	char_delete_set(NULL);
}
void test_display_char_set(void){

	char_display_set(NULL);
	char_display_set(set1);
}

void test_char_set_used(void){
	TEST_ASSERT_EQUAL(0,char_set_used(NULL));
	TEST_ASSERT_EQUAL(0,char_set_used(set1));

	char_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1,char_set_used(set1));

	char_add_to_set(&set1,'b');
	char_add_to_set(&set1,'c');
	TEST_ASSERT_EQUAL(3,char_set_used(set1));

	char_remove_from_set(&set1,'a');
	TEST_ASSERT_EQUAL(2,char_set_used(set1));

	char_remove_from_set(&set1,'c');
	char_remove_from_set(&set1,'b');
	TEST_ASSERT_EQUAL(0,char_set_used(set1));

}
void test_char_set_size(void){
	TEST_ASSERT_EQUAL(0,char_set_size(NULL));
	TEST_ASSERT_EQUAL(SETSZ,char_set_size(set1));

	char_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(SETSZ,char_set_size(set1));

	char_add_to_set(&set1,'b');
	char_add_to_set(&set1,'c');
	char_add_to_set(&set1,'d');
	char_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ,char_set_size(set1));

	char_remove_from_set(&set1,'a');
	TEST_ASSERT_EQUAL(SETSZ,char_set_size(set1));
	char_add_to_set(&set1,'r');
	char_add_to_set(&set1,'s');
	char_add_to_set(&set1,'t');
	char_add_to_set(&set1,'u');
	TEST_ASSERT_EQUAL(SETSZ+INCREMENT_SIZE,char_set_size(set1));

}
void test_char_get_value_by_index_set(void){
	TEST_ASSERT_NULL(char_get_value_by_index_set(NULL,25));

	char_add_to_set(&set1,'c');
	char_add_to_set(&set1,'d');
	char_add_to_set(&set1,'e');

	TEST_ASSERT_EQUAL_CHAR('c',*(char*)char_get_value_by_index_set(set1,0));
	TEST_ASSERT_EQUAL_CHAR('d',*(char*)char_get_value_by_index_set(set1,1));
	TEST_ASSERT_EQUAL_CHAR('e',*(char*)char_get_value_by_index_set(set1,2));

	TEST_ASSERT_NULL(char_get_value_by_index_set(NULL,-1));
	TEST_ASSERT_NULL(char_get_value_by_index_set(NULL,25));

}


void test_char_add_to_set(void){
	base_set *set2;
	set2 = NULL;
	char_add_to_set(NULL,'a');
	TEST_ASSERT_EQUAL(0, char_is_in_set(set1,'a'));
	
	char_add_to_set(&set2,'a');
	TEST_ASSERT_EQUAL(0, char_is_in_set(set2,'a'));

	char_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1, char_is_in_set(set1,'a'));
	
	char_add_to_set(&set1,'b');
	char_add_to_set(&set1,'c');
	char_add_to_set(&set1,'d');
	char_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ, char_set_size(set1));
	TEST_ASSERT_EQUAL(char_set_used(set1), char_set_size(set1));

	char_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ, char_set_size(set1));

	char_add_to_set(&set1,'f');
	TEST_ASSERT_NOT_EQUAL(SETSZ, char_set_size(set1));
	TEST_ASSERT_EQUAL(SETSZ +INCREMENT_SIZE, char_set_size(set1));
	TEST_ASSERT_NOT_EQUAL(char_set_used(set1), char_set_size(set1));
	
}

void test_char_is_in_set(void){
	tearDown();
	set1 = new_char_set(1);
	TEST_ASSERT_EQUAL(-1, is_in_set(NULL,'a'));
	TEST_ASSERT_EQUAL(0, char_is_in_set(NULL,'a'));
	TEST_ASSERT_EQUAL(0, char_is_in_set(set1,'a'));
	char_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1, char_is_in_set(set1,'a'));
	TEST_ASSERT_EQUAL(0, char_is_in_set(set1,'b'));
}

void test_char_sets_are_same(void){
	char_set *set2;
	set2 = new_char_set(2);
	char_add_to_set(&set1, 'a');
	char_add_to_set(&set2, 'a');
	TEST_ASSERT_EQUAL(0,char_sets_are_same(NULL,set2));
	TEST_ASSERT_EQUAL(0,char_sets_are_same(NULL,NULL));
	TEST_ASSERT_EQUAL(0,char_sets_are_same(set2,NULL));
	TEST_ASSERT_EQUAL(1,char_sets_are_same(set1,set2));

	char_add_to_set(&set2, 'b');
	TEST_ASSERT_NOT_EQUAL(1,char_sets_are_same(set1,set2));

	char_add_to_set(&set1, 'b');
	TEST_ASSERT_EQUAL(1,char_sets_are_same(set1,set2));

	TEST_ASSERT_EQUAL(1,char_sets_are_same(set2,set1));

	char_add_to_set(&set1, 'c');
	char_add_to_set(&set2, 'd');
	TEST_ASSERT_NOT_EQUAL(1,char_sets_are_same(set2,set1));
	char_delete_set(set2);
	set2 = NULL;
}

void test_char_remove_from_set(void){
	char_set *set2;
	set2 = NULL;
	char_add_to_set(&set1,'b');
	char_add_to_set(&set1,'c');
	TEST_ASSERT_EQUAL(2,char_set_used(set1));

	char_remove_from_set(NULL,'c');
	char_remove_from_set(&set2,'c');
	
	char_remove_from_set(&set1,'d');
	TEST_ASSERT_EQUAL(2,char_set_used(set1));

	char_remove_from_set(&set1,'c');
	TEST_ASSERT_EQUAL(1,char_set_used(set1));

}
void test_char_copy_sets(void){
	char_set *set2;
	set2 = NULL;
	TEST_ASSERT_NULL(char_copy_sets(NULL));
	char_add_to_set(&set1,'c');
	char_add_to_set(&set1,'b');
	set2 = char_copy_sets(set1);
	TEST_ASSERT_NOT_NULL(set2);
	
	TEST_ASSERT_TRUE(char_sets_are_same(set1,set2));

	char_add_to_set(&set2,'r');
	TEST_ASSERT_FALSE(char_sets_are_same(set1,set2));
	char_delete_set(set2);
	set2 = NULL;
}

void test_char_merge_sets(void){
	char_set* set2, *set3;
	set2 = set3 =NULL;
	TEST_ASSERT_NULL(char_merge_sets(NULL,set1));
	TEST_ASSERT_NULL(char_merge_sets(NULL,NULL));
	TEST_ASSERT_NULL(char_merge_sets(set1,NULL));

	set2 = new_char_set(1);

	char_add_to_set(&set1, 'a');

	char_add_to_set(&set2, 'a');
	char_add_to_set(&set2, 'd');

	set3 = char_merge_sets(set1,set2);
	TEST_ASSERT_EQUAL(2,char_set_used(set3));
	
	TEST_ASSERT_EQUAL_CHAR('a',*(char*)char_get_value_by_index_set(set3,0));
	TEST_ASSERT_EQUAL_CHAR('d',*(char*)char_get_value_by_index_set(set3,1));
	char_delete_set(set3);

	char_add_to_set(&set2, 'c');
	char_add_to_set(&set1, 'b');

	set3 = char_merge_sets(set1,set2);
	TEST_ASSERT_EQUAL(4,char_set_used(set3));
	TEST_ASSERT_EQUAL_CHAR('a',*(char*)char_get_value_by_index_set(set3,0));
	TEST_ASSERT_EQUAL_CHAR('b',*(char*)char_get_value_by_index_set(set3,1));
	TEST_ASSERT_EQUAL_CHAR('c',*(char*)char_get_value_by_index_set(set3,2));
	TEST_ASSERT_EQUAL_CHAR('d',*(char*)char_get_value_by_index_set(set3,3));

	char_add_to_set(&set2,'t');
	
	TEST_ASSERT_EQUAL(2,char_set_used(set1));
	TEST_ASSERT_EQUAL(4,char_set_used(set2));
	TEST_ASSERT_EQUAL(4,char_set_used(set3));
	
	TEST_ASSERT_FALSE(char_sets_are_same(set2,set3));
	
	char_delete_set(set2);
	char_delete_set(set3);
	set2 = NULL;
	set3 = NULL;
	
}
