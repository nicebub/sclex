#ifndef MHASH_H
#define MHASH_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASHMAX 256

#define value_from_int(h,k) get_value_for_key(h,k,0)
#define value_from_char(h,k) get_value_for_key(h,k,2)
#define value_from_string(h,k) get_value_for_key(h,k,3)

#define add_itoh(h,v,k,kt) add_to_hash(h,v,0,k,kt)
#define add_ctoh(h,v,k,kt) add_to_hash(h,v,2,k,kt)
#define add_stoh(h,v,k,kt) add_to_hash(h,v,3,k,kt)

#define add_iitoh(h,v,k) add_to_hash(h,v,0,k,0)
#define add_ictoh(h,v,k) add_to_hash(h,v,0,k,2)
#define add_istoh(h,v,k) add_to_hash(h,v,0,k,3)
#define add_citoh(h,v,k) add_to_hash(h,v,2,k,0)
#define add_cctoh(h,v,k) add_to_hash(h,v,2,k,2)
#define add_cstoh(h,v,k) add_to_hash(h,v,2,k,3)
#define add_sitoh(h,v,k) add_to_hash(h,v,3,k,0)
#define add_sctoh(h,v,k) add_to_hash(h,v,3,k,2)
#define add_sstoh(h,v,k) add_to_hash(h,v,3,k,3)

struct _hashnode {
    void * value;
    void * key;
    struct _hashnode *next;
    int uniq;
    int vtype;
    int ktype;
};

typedef struct _hashnode ** hashbucket_array;

struct _ca{
    void* p;
    int pt;
    int r;
};

struct _hr{
    int r;
    int i;
};
//typedef struct _ca ** ca;

struct _hash {
    hashbucket_array bucket;
    struct _ca *cache;
    int csize;
    int cused;
    int size;
    int used;
 //   int lasth;
    int alpha;
};
struct _hash *create_hash(int size);
void add_to_hash(struct _hash *, void * v, int vt, void * k, int kt);

struct _hash *copy_hash(struct _hash * h);

void * get_value_for_key(struct _hash*, void* k, int kt);

struct _hash* combine_hashes(struct _hash*, struct _hash*);

void print_hash(struct _hash * h);
void delete_hash(struct _hash*);
void delete_hashnode(struct _hashnode*);

#endif
