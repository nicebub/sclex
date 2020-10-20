#ifndef _BASE_SET_CLASS_H
#define _BASE_SET_CLASS_H
#include <stdlib.h>
#define SETSIZE 400

#define NEWSETERROR(in) printf("couldn't create new " #in "set\n");

typedef struct _base_set base_set;
typedef struct _base_set_vtable base_set_vtable;

struct _base_set {
	base_set_vtable * vtable;
	int size;
	int used;
	int uniq;
	int id;
};
struct _base_set_vtable{
	void (*delete_set)(base_set* inset);	

	void (*add_to_set)(base_set ** set, int value);
	void (*remove_from_set)(base_set ** set, int value);

	base_set * (*merge_sets)(base_set * set1, base_set* set2);
	base_set * (*copy_sets)(base_set * set);

	int (*sets_are_same)(base_set* set1, base_set* set2);
	int (*is_in_set)(base_set * set, int value);

	void (*display_set)(base_set* set);
	int (*set_used)(base_set* set);
	void* (*get_value_by_index_set)(base_set* set, int index);
	int (*set_size)(base_set* set);
	/* current simple implementation won't need these functions
	 * yet 
	 * base_set * (*msort_set)(base_set* set);
	 * base_set * (*msort_set_helper)(base_set* set,int start,int finish);
	 * base_set * (*msmerge_sets)(base_set **left,base_set **right);
	 */
	
};

/*static base_set_vtable vtable_base_set;*/

base_set* new_set(int size);
/* standard set funtions that are used to call set functions
 * of through their individual vtable entries */

void delete_set(base_set* inset);	
int is_in_set(base_set * set, int value);
void add_to_set(base_set ** set, int value);
void remove_from_set(base_set ** set, int value);
base_set * merge_sets(base_set * set1, base_set* set2);
base_set * copy_sets(base_set * set);
int sets_are_same(base_set* set1, base_set* set2);
void display_set(base_set* set);
int set_used(base_set* set);
void* get_value_by_index_set(base_set* set, int index);
int set_size(base_set* set);
/* unneeded at this time
base_set * msort_set(base_set* set);
base_set * msort_set_helper(base_set* set,int start,int finish);
base_set * msmerge_sets(base_set **left,base_set **right);
*/

/* sets standard functions declared above to point to base set
 * stub functions below */
/*void init_base_set_vtable(void);*/

base_set* new_base_set(int size);

void base_delete_set(base_set* set);	
int base_is_in_set(base_set * set, int value);
int base_sets_are_same(base_set* set1, base_set* set2);
void base_add_to_set(base_set ** set, int value);
void base_remove_from_set(base_set ** set, int value);
base_set * base_merge_sets(base_set * set1, base_set* set2);
base_set * base_copy_sets(base_set * set);
int base_sets_are_same(base_set* set1, base_set* set2);
void base_display_set(base_set* set);
int base_set_used(base_set* set);
void* base_get_value_by_index_set(base_set* set, int index);
int base_set_size(base_set* set);

/* unneeded at this time
base_set * base_msort_set(base_set* set);
base_set * base_msort_set_helper(base_set* set,int start,int finish);
base_set * base_msmerge_sets(base_set **left,base_set **right);
*/





/*
#define settype(type) type##_set
#define newset(type,size) new_##type##_set(size)
#define setvtable(type) type##_set##_vtable
#define deleteset(type,in) type##_delete_set(in)
#define isinset(type,in) type##_is_in_set(in)
#define setsaresame(type,first,second) type##_sets_are_same(first,second)
#define addtoset(type,first,value) type##_add_to_set(first,value)
#define removefromset(type,first,value) type##_remove_from_set(first,value)
#define mergesets(type,first,second) type##_merge_sets(first,second)
#define dipslayset(type,in) type##_dsiplay_set(in)
*/
#endif
