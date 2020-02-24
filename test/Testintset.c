#include "unity.h"
#include <stdio.h>
#include "intset.h"
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
int_set *set1;

void setUp(void){
	set1 = NULL;
	set1 = new_int_set(SETSZ);
}
void tearDown(void){
	int_delete_set(set1);
	set1 = NULL;
}
void test_inheritance_with_base_pointer(void){
	base_set *bset;
	bset = NULL;
	bset = new_int_set(0);
	TEST_ASSERT_NULL(bset);
	bset = new_int_set(1);
	int_delete_set(bset);
	bset = NULL;
}


void test_new_and_delete_int_set(void){

	tearDown();

	set1 = new_int_set(0);
	TEST_ASSERT_NULL(set1);

	setUp();
	TEST_ASSERT_NOT_NULL(set1);

	TEST_ASSERT_EQUAL(SETSZ,int_set_size(set1));
	TEST_ASSERT_EQUAL_PTR(NULL,!set1->super.vtable);
	TEST_ASSERT_EQUAL(0,int_set_used(set1));
	TEST_ASSERT_EQUAL(0, set1->super.id);
	TEST_ASSERT_EQUAL(0, set1->super.uniq);
	TEST_ASSERT_EQUAL_PTR(NULL,!set1->values);
	
	int_delete_set(NULL);
}
void test_display_int_set(void){

	int_display_set(NULL);
	int_display_set(set1);
}

void test_int_set_used(void){
	TEST_ASSERT_EQUAL(0,int_set_used(NULL));
	TEST_ASSERT_EQUAL(0,int_set_used(set1));

	int_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1,int_set_used(set1));

	int_add_to_set(&set1,'b');
	int_add_to_set(&set1,'c');
	TEST_ASSERT_EQUAL(3,int_set_used(set1));

	int_remove_from_set(&set1,'a');
	TEST_ASSERT_EQUAL(2,int_set_used(set1));

	int_remove_from_set(&set1,'c');
	int_remove_from_set(&set1,'b');
	TEST_ASSERT_EQUAL(0,int_set_used(set1));

}
void test_int_set_size(void){
	TEST_ASSERT_EQUAL(0,int_set_size(NULL));
	TEST_ASSERT_EQUAL(SETSZ,int_set_size(set1));

	int_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(SETSZ,int_set_size(set1));

	int_add_to_set(&set1,'b');
	int_add_to_set(&set1,'c');
	int_add_to_set(&set1,'d');
	int_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ,int_set_size(set1));

	int_remove_from_set(&set1,'a');
	TEST_ASSERT_EQUAL(SETSZ,int_set_size(set1));
	int_add_to_set(&set1,'r');
	int_add_to_set(&set1,'s');
	int_add_to_set(&set1,'t');
	int_add_to_set(&set1,'u');
	TEST_ASSERT_EQUAL(SETSZ+INCREMENT_SIZE,int_set_size(set1));

}
void test_int_get_value_by_index_set(void){
	TEST_ASSERT_NULL(int_get_value_by_index_set(NULL,25));

	int_add_to_set(&set1,'c');
	int_add_to_set(&set1,'d');
	int_add_to_set(&set1,'e');

	TEST_ASSERT_EQUAL('c',*(int*)int_get_value_by_index_set(set1,0));
	TEST_ASSERT_EQUAL('d',*(int*)int_get_value_by_index_set(set1,1));
	TEST_ASSERT_EQUAL('e',*(int*)int_get_value_by_index_set(set1,2));

	TEST_ASSERT_NULL(int_get_value_by_index_set(NULL,-1));
	TEST_ASSERT_NULL(int_get_value_by_index_set(NULL,25));

}


void test_int_add_to_set(void){
	base_set *set2;
	set2 = NULL;
	int_add_to_set(NULL,'a');
	TEST_ASSERT_EQUAL(0, int_is_in_set(set1,'a'));
	
	int_add_to_set(&set2,'a');
	TEST_ASSERT_EQUAL(0, int_is_in_set(set2,'a'));

	int_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1, int_is_in_set(set1,'a'));
	
	int_add_to_set(&set1,'b');
	int_add_to_set(&set1,'c');
	int_add_to_set(&set1,'d');
	int_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ, int_set_size(set1));
	TEST_ASSERT_EQUAL(int_set_used(set1), int_set_size(set1));

	int_add_to_set(&set1,'e');
	TEST_ASSERT_EQUAL(SETSZ, int_set_size(set1));

	int_add_to_set(&set1,'f');
	TEST_ASSERT_NOT_EQUAL(SETSZ, int_set_size(set1));
	TEST_ASSERT_EQUAL(SETSZ +INCREMENT_SIZE, int_set_size(set1));
	TEST_ASSERT_NOT_EQUAL(int_set_used(set1), int_set_size(set1));
	
}

void test_int_is_in_set(void){
	tearDown();
	set1 = new_int_set(1);
	TEST_ASSERT_EQUAL(-1, is_in_set(NULL,'a'));
	TEST_ASSERT_EQUAL(0, int_is_in_set(NULL,'a'));
	TEST_ASSERT_EQUAL(0, int_is_in_set(set1,'a'));
	int_add_to_set(&set1,'a');
	TEST_ASSERT_EQUAL(1, int_is_in_set(set1,'a'));
	TEST_ASSERT_EQUAL(0, int_is_in_set(set1,'b'));
}

void test_int_sets_are_same(void){
	int_set *set2;
	set2 = new_int_set(2);
	int_add_to_set(&set1, 'a');
	int_add_to_set(&set2, 'a');
	TEST_ASSERT_EQUAL(0,int_sets_are_same(NULL,set2));
	TEST_ASSERT_EQUAL(0,int_sets_are_same(NULL,NULL));
	TEST_ASSERT_EQUAL(0,int_sets_are_same(set2,NULL));
	TEST_ASSERT_EQUAL(1,int_sets_are_same(set1,set2));

	int_add_to_set(&set2, 'b');
	TEST_ASSERT_NOT_EQUAL(1,int_sets_are_same(set1,set2));

	int_add_to_set(&set1, 'b');
	TEST_ASSERT_EQUAL(1,int_sets_are_same(set1,set2));

	TEST_ASSERT_EQUAL(1,int_sets_are_same(set2,set1));

	int_add_to_set(&set1, 'c');
	int_add_to_set(&set2, 'd');
	TEST_ASSERT_NOT_EQUAL(1,int_sets_are_same(set2,set1));
	int_delete_set(set2);
	set2 = NULL;
}

void test_int_remove_from_set(void){
	int_set *set2;
	set2 = NULL;
	int_add_to_set(&set1,'b');
	int_add_to_set(&set1,'c');
	TEST_ASSERT_EQUAL(2,int_set_used(set1));

	int_remove_from_set(NULL,'c');
	int_remove_from_set(&set2,'c');
	
	int_remove_from_set(&set1,'d');
	TEST_ASSERT_EQUAL(2,int_set_used(set1));

	int_remove_from_set(&set1,'c');
	TEST_ASSERT_EQUAL(1,int_set_used(set1));

}
void test_int_copy_sets(void){
	int_set *set2;
	set2 = NULL;
	TEST_ASSERT_NULL(int_copy_sets(NULL));
	int_add_to_set(&set1,'c');
	int_add_to_set(&set1,'b');
	set2 = int_copy_sets(set1);
	TEST_ASSERT_NOT_NULL(set2);
	
	TEST_ASSERT_TRUE(int_sets_are_same(set1,set2));

	int_add_to_set(&set2,'r');
	TEST_ASSERT_FALSE(int_sets_are_same(set1,set2));
	int_delete_set(set2);
	set2 = NULL;
}

void test_int_merge_sets(void){
	int_set* set2, *set3;
	set2 = set3 =NULL;
	TEST_ASSERT_NULL(int_merge_sets(NULL,set1));
	TEST_ASSERT_NULL(int_merge_sets(NULL,NULL));
	TEST_ASSERT_NULL(int_merge_sets(set1,NULL));

	set2 = new_int_set(1);

	int_add_to_set(&set1, 'a');

	int_add_to_set(&set2, 'a');
	int_add_to_set(&set2, 'd');

	set3 = int_merge_sets(set1,set2);
	TEST_ASSERT_EQUAL(2,int_set_used(set3));
	
	TEST_ASSERT_EQUAL('a',*(int*)int_get_value_by_index_set(set3,0));
	TEST_ASSERT_EQUAL('d',*(int*)int_get_value_by_index_set(set3,1));
	int_delete_set(set3);

	int_add_to_set(&set2, 'c');
	int_add_to_set(&set1, 'b');

	set3 = int_merge_sets(set1,set2);
	TEST_ASSERT_EQUAL(4,int_set_used(set3));
	TEST_ASSERT_EQUAL('a',*(int*)int_get_value_by_index_set(set3,0));
	TEST_ASSERT_EQUAL('b',*(int*)int_get_value_by_index_set(set3,1));
	TEST_ASSERT_EQUAL('c',*(int*)int_get_value_by_index_set(set3,2));
	TEST_ASSERT_EQUAL('d',*(int*)int_get_value_by_index_set(set3,3));

	int_add_to_set(&set2,'t');
	
	TEST_ASSERT_EQUAL(2,int_set_used(set1));
	TEST_ASSERT_EQUAL(4,int_set_used(set2));
	TEST_ASSERT_EQUAL(4,int_set_used(set3));
	
	TEST_ASSERT_FALSE(int_sets_are_same(set2,set3));
	
	int_delete_set(set2);
	int_delete_set(set3);
	set2 = NULL;
	set3 = NULL;
	
}
