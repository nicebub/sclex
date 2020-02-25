#include "unity.h"
#include "basevector.h"

base_vector *vec;

void setUp(void){
	vec = NULL;
	vec = new_vector(1);
}


void tearDown(void){
	delete_vector(vec);
	vec = NULL;
}
void test_new_and_delete_base_vector(void){
	tearDown();
	vec = new_vector(0);
	TEST_ASSERT_NULL(vec);
	vec = new_vector(10);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_EQUAL(10,base_vector_size(vec));
	TEST_ASSERT_EQUAL_PTR(NULL,!vec->vtable);
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	TEST_ASSERT_EQUAL(0, vec->id);
	delete_vector(NULL);
	
}

void test_new_with_init_and_delete_base_vector(void){
	
	tearDown();
	vec = new_vector_with_init_sets(0,0);
	TEST_ASSERT_NULL(vec);
	vec = new_vector_with_init_sets(10,0);
	TEST_ASSERT_NOT_NULL(vec);
	TEST_ASSERT_EQUAL(10,base_vector_size(vec));
	TEST_ASSERT_EQUAL_PTR(NULL,!vec->vtable);
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	TEST_ASSERT_EQUAL(0, vec->id);
	delete_vector(NULL);	
}


void test_base_display_vector(void){
	display_vector(NULL);
	
	display_vector(vec);
}

void test_base_vector_used(void){

	TEST_ASSERT_EQUAL(0,base_vector_used(NULL));
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));

}

void test_base_vector_size(void){

	TEST_ASSERT_EQUAL(0,base_vector_size(NULL));
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));

}

void test_base_set_vector_used(void){

	TEST_ASSERT_EQUAL(0,base_vector_used(NULL));
	TEST_ASSERT_EQUAL(0,base_vector_used(vec));
	base_set_vector_used(vec,5);
	TEST_ASSERT_EQUAL(5,base_vector_used(vec));

}

void test_base_set_vector_size(void){

	TEST_ASSERT_EQUAL(0,base_vector_size(NULL));
	TEST_ASSERT_EQUAL(1,base_vector_size(vec));
	base_set_vector_size(vec,5);
	TEST_ASSERT_EQUAL(5,base_vector_size(vec));

}
void test_vector(void){
	base_vector* madvector;
	madvector = new_vector(50);
	add_to_vector(NULL,madvector);
	display_vector(madvector);
	delete_vector(madvector);
	madvector = NULL;
}
