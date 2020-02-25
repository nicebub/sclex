#include "unity.h"
#include "chrvector.h"

char_vector *vec;
base_set * set1;

void setUp(void){
	vec = NULL;
	vec = new_char_vector(1);
	set1 = new_char_set(4);
	add_to_set(&set1,'a');
	add_to_set(&set1,'b');
	add_to_set(&set1,'c');
	add_to_set(&set1,'d');
}

void tearDown(void){
	char_delete_vector(vec);
	vec = NULL;
	char_delete_set(set1);
	set1 = NULL;
}

void test_new_and_delete_char_vector(void){
	tearDown();
	vec = new_char_vector(0);
	TEST_ASSERT_NULL(vec);
	vec = new_char_vector(10);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_EQUAL(10,base_vector_size(vec));
	TEST_ASSERT_EQUAL_PTR(NULL,!vec->super.vtable);
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	TEST_ASSERT_EQUAL(0, vec->super.id);
	delete_vector(NULL);
	
}

void test_new_with_init_and_delete_char_vector(void){
	
	tearDown();
	vec = new_char_vector_with_init_sets(0,0);
	TEST_ASSERT_NULL(vec);
	vec = new_char_vector_with_init_sets(10,0);
	TEST_ASSERT_NULL(vec);
	vec = new_char_vector_with_init_sets(10,1);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_EQUAL(1, char_set_size(*char_get_by_index_in_vector(vec,0)));
	TEST_ASSERT_NOT_EQUAL(0, char_set_size(*char_get_by_index_in_vector(vec,0)));
	TEST_ASSERT_NOT_EQUAL(2, char_set_size(*char_get_by_index_in_vector(vec,0)));
	TEST_ASSERT_EQUAL(10,base_vector_size(vec));
	TEST_ASSERT_EQUAL_PTR(NULL,!vec->super.vtable);
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	TEST_ASSERT_EQUAL(0, vec->super.id);
	delete_vector(NULL);
}

void test_char_display_vector(void){
	char_display_vector(NULL);
	
	char_display_vector(vec);

	char_add_to_vector(set1,vec);
	char_display_vector(vec);
	
}

void test_char_vector_used(void){

	TEST_ASSERT_EQUAL(0,base_vector_used(NULL));
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	char_add_to_vector(set1,vec);
	TEST_ASSERT_EQUAL(1,base_vector_used(vec));
	
}

void test_char_vector_size(void){
	char_set * set2;
	TEST_ASSERT_EQUAL(0,base_vector_size(NULL));
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	char_add_to_vector(set1,vec);
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	set2 = new_char_set(1);
	char_add_to_vector(set2,vec);
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	delete_set(set2);
	set2 = NULL;
}

void test_char_set_vector_used(void){

	TEST_ASSERT_EQUAL(0,base_vector_used(NULL));
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	char_set_vector_used(vec,5);
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
    char_set_vector_used(vec,0);
    TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	char_add_to_vector(set1,vec);
    TEST_ASSERT_EQUAL(1,base_vector_used(vec));
	char_set_vector_used(vec,-1);
    TEST_ASSERT_EQUAL(1,base_vector_used(vec));
	char_set_vector_used(vec,60);
    TEST_ASSERT_EQUAL(1,base_vector_used(vec));
}

void test_char_set_vector_size(void){

	TEST_ASSERT_EQUAL(0,base_vector_size(NULL));
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	char_set_vector_size(vec,5);
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	char_set_vector_size(vec,1);
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	char_set_vector_size(vec,-1);
    TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	char_set_vector_size(vec,60);
    TEST_ASSERT_EQUAL(1,base_vector_size(vec));

}

void test_char_set_by_index_in_vector(void){

	char_set_by_index_in_vector(NULL,0,set1);
	char_set_by_index_in_vector(vec,-1,set1);
	char_set_by_index_in_vector(vec,60,set1);
	char_set_by_index_in_vector(vec,0,NULL);
	TEST_ASSERT_NULL(*char_get_by_index_in_vector(vec,0));
	char_set_by_index_in_vector(vec,0,set1);
	TEST_ASSERT_NOT_NULL(*char_get_by_index_in_vector(vec,0));
	TEST_ASSERT_EQUAL(1,char_vector_used(vec));

}
void test_char_get_by_index_in_vector(void){
	char_set *set2;
	TEST_ASSERT_NULL(char_get_by_index_in_vector(NULL,0));
	TEST_ASSERT_NULL(char_get_by_index_in_vector(vec,-1));
	TEST_ASSERT_NULL(char_get_by_index_in_vector(vec,60));
	
	TEST_ASSERT_NULL(*char_get_by_index_in_vector(vec,0));

	char_add_to_vector(set1,vec);
	TEST_ASSERT_EQUAL_MEMORY(set1,*(char_set**)char_get_by_index_in_vector(vec,0),sizeof(set1));
	TEST_ASSERT_NOT_EQUAL(set1,*(base_set**)char_get_by_index_in_vector(vec,0));
	
	set2 = char_copy_sets(set1);
	TEST_ASSERT_EQUAL_MEMORY(set2,*(char_set**)char_get_by_index_in_vector(vec,0),sizeof(set1));
	char_delete_set(set2);
	
	TEST_ASSERT_TRUE(char_sets_are_same(set1,*(base_set**)char_get_by_index_in_vector(vec,0)));
	
}
