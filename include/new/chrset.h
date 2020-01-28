#ifndef _CHAR_SET_CLASS_H
#define _CHAR_SET_CLASS_H

#include "baseset.h"

typedef struct _char_set char_set;

struct _char_set {
	base_set super;
	char * values;
	size_t size;
	size_t used;
	size_t uniq;
	size_t id;
};

char_set* new_char_set(size_t size);

void char_delete_set(char_set* set);	
int char_is_in_set(char_set * set, char value);
int char_sets_are_same(char_set* set1, char_set* set2);
void char_add_to_set(char_set ** set, char value);
void char_remove_from_set(char_set ** set, char value);
char_set * char_merge_sets(char_set * set1, char_set* set2);
char_set * char_copy_sets(char_set * set);
void char_display_set(char_set* set);

/* may not need these anymore, for now with current
 * implementation */
/*
char_set * char_msort_set(char_set* set);
char_set * char_msort_set_helper(char_set* set,int start,int finish);
char_set * char_msmerge_sets(char_set **left,char_set **right);
*/
#endif
