#ifndef _BASE_SET_CLASS_H
#define _BASE_SET_CLASS_H

typedef struct _base_set base_set;
typedef struct _base_set_vtable base_set_vtable;

struct _base_set {
	base_set_vtable * vtable;
    void * s;
    int size;
    int used;
    int uniq;
    int id;
};
struct _base_set_vtable{
	void (*delete_set)(base_set* inset, int type);	

	void (*add_to_set)(base_set ** set, int value, int type);
	void (*remove_from_set)(base_set ** set, int value, int type);

	base_set * (*merge_sets)(base_set * set1, base_set* set2, int type);
	base_set * (*copy_sets)(base_set * set, int type);

	base_set * (*sets_are_same)(base_set* set1, base_set* set2, int type);
	int (*is_in_set)(base_set * set, int value, int type);

	base_set * (*msort_set)(base_set* set);
	base_set * (*msort_set_helper)(base_set* set,int start,int finish);
	base_set * (*msmerge_sets)(base_set **left,base_set **right);

	void (*display_set)(base_set* set, int type);
	
};

/* standard set funtions that are used to call set functions
 * of through their individual vtable entries */
base_set* create_set(int size, int type);

void delete_set(base_set* inset, int type);	
int is_in_set(base_set * set, int value, int type);
void add_to_set(base_set ** set, int value, int type);
void remove_from_set(base_set ** set, int value, int type);
base_set * merge_sets(base_set * set1, base_set* set2, int type);
base_set * copy_sets(base_set * set, int type);
base_set * sets_are_same(base_set* set1, base_set* set2, int type);
base_set * msort_set(base_set* set);
base_set * msort_set_helper(base_set* set,int start,int finish);
base_set * msmerge_sets(base_set **left,base_set **right);
void display_set(base_set* set, int type);

/* sets standard functions declared above to point to base set
 * stub functions below */
void init_base_set_vtable();

/* stubs for base set that don't do anything*/
base_set* base_create_set(int size, int type);

void base_delete_set(base_set* set, int type);	
int base_is_in_set(base_set * set, int value, int type);
void base_add_to_set(base_set ** set, int value, int type);
void base_remove_from_set(base_set ** set, int value, int type);
base_set * base_merge_sets(base_set * set1, base_set* set2, int type);
base_set * base_copy_sets(base_set * set, int type);
base_set * base_sets_are_same(base_set* set1, base_set* set2, int type);
base_set * base_msort_set(base_set* set);
base_set * base_msort_set_helper(base_set* set,int start,int finish);
base_set * base_msmerge_sets(base_set **left,base_set **right);
void base_display_set(base_set* set, int type);

#endif
