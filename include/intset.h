#ifndef _INT_SET_CLASS_H
#define _INT_SET_CLASS_H

#include "baseset.h"

#define INCREMENT_SIZE 10

typedef struct _int_set int_set;

struct _int_set {
	base_set super;
	int * values;
};

base_set* new_int_set(int size);

void int_delete_set(base_set* set);	
int int_is_in_set(base_set * set, int value);
int int_sets_are_same(base_set* set1, base_set* set2);
void int_add_to_set(base_set ** set, int value);
void int_remove_from_set(base_set ** set, int value);
base_set * int_merge_sets(base_set * set1, base_set* set2);
base_set * int_copy_sets(base_set * set);
void int_display_set(base_set* set);
int int_set_used(base_set* set);
void* int_get_value_by_index_set(base_set* set, int index);
int int_set_size(base_set* set);

/* may not need these anymore, for now with current
 * implementation */
/*
base_set * int_msort_set(base_set* set);
base_set * int_msort_set_helper(base_set* set,int start,int finish);
base_set * int_msmerge_sets(base_set **left,base_set **right);
*/

static base_set_vtable int_set_vtable = {
 &int_delete_set,
 &int_add_to_set,
 &int_remove_from_set,
 &int_merge_sets,
 &int_copy_sets,
 &int_sets_are_same,
 &int_is_in_set,
 &int_display_set,
 &int_set_used,
 &int_get_value_by_index_set,
 &int_set_used
/* current implementation doesn't need these yet
 * &int_msort_set,
 * &int_msort_set_helper,
 * &int_msmerge_sets,
 */
};

#endif
