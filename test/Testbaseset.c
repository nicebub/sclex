#include "unity.h"
#include "baseset.h"

void test_new_and_delete_base_set(void){
	base_set *set1;
	set1 = NULL;
	set1 = new_set(0);
	TEST_ASSERT_NULL(set1);
	set1 = new_set(10);
	TEST_ASSERT_NOT_NULL(set1);
	TEST_ASSERT_EQUAL(10,set_size(set1));
	TEST_ASSERT_EQUAL_PTR(NULL,!set1->vtable);
	TEST_ASSERT_EQUAL(0,set_used(set1));
	TEST_ASSERT_EQUAL(0, set1->id);
	TEST_ASSERT_EQUAL(0, set1->uniq);
	delete_set(NULL);
	delete_set(set1);
	set1 = NULL;
	
}
void test_display_set(void)
{
	base_set *set1;
	set1 = new_set(10);
	display_set(NULL);
	display_set(set1);
	delete_set(set1);
	set1 = NULL;
}
