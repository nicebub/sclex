#ifndef _CHAR_SET_CLASS_H
#define _CHAR_SET_CLASS_H

#include "baseset.h"

typedef struct _char_set char_set;

struct _char_set {
	base_set super;
	char * values;
};

base_set* new_char_set(int size);

void char_delete_set(base_set* set);
int char_is_in_set(base_set * set, int value);
int char_sets_are_same(base_set* set1, base_set* set2);
void char_add_to_set(base_set ** set, int value);
void char_remove_from_set(base_set ** set, int value);
base_set * char_merge_sets(base_set * set1, base_set* set2);
base_set * char_copy_sets(base_set * set);
void char_display_set(base_set* set);
int char_set_used(base_set* set);
void* char_get_value_by_index_set(base_set* set, int index);
int char_set_size(base_set* set);

/* may not need these anymore, for now with current
 * implementation */
/*
base_set * char_msort_set(base_set* set);
base_set * char_msort_set_helper(base_set* set,int start,int finish);
base_set * char_msmerge_sets(base_set **left,base_set **right);
*/
#endif
