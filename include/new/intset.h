#ifndef _INT_SET_CLASS_H
#define _INT_SET_CLASS_H

#include "baseset.h"

typedef struct _int_set int_set;

struct _int_set {
	base_set super;
    int * s;
    size_t size;
    size_t used;
    size_t uniq;
    size_t id;
};

int_set* new_int_set(int size);

void int_delete_set(int_set* set);	
int int_is_in_set(int_set * set, int value);
int int_sets_are_same(int_set* set1, int_set* set2);
void int_add_to_set(int_set ** set, int value);
void int_remove_from_set(int_set ** set, int value);
int_set * int_merge_sets(int_set * set1, int_set* set2);
int_set * int_copy_sets(int_set * set);
/*int int_sets_are_same(int_set* set1, int_set* set2);*/
int_set * int_msort_set(int_set* set);
int_set * int_msort_set_helper(int_set* set,int start,int finish);
int_set * int_msmerge_sets(int_set **left,int_set **right);
void int_display_set(int_set* set);

#endif
