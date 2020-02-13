#ifndef MSET_H
#define MSET_H

#include <stdlib.h>
#include <stdio.h>

#define SETSIZE 400


struct _iset {
    int * s;
    int size;
    int used;
    int uniq;
    int id;
};

struct _cset {
    char * s;
    int size;
    int used;
    int uniq;
    int id;

};

struct _iseta {
    struct _iset ** iset;
    int size;
    int used;
    int id;
};
struct _cseta {
    struct _cset ** cset;
    int size;
    int used;
    int id;
};

struct _iset * create_iset(int size);
struct _cset * create_cset(int size);
void * create_set(int size, int type);
struct _iseta* create_iseta(int size);
struct _cseta* create_cseta(int size);
void * create_seta(int size, int type);

void delete_iseta(struct _iseta *);
void delete_cseta(struct _cseta *);
void delete_seta(void *, int type);
void delete_iset(struct _iset *);
void delete_cset(struct _cset *);
void delete_set(void *, int type);

int is_in_iset(struct _iset*,int);
int is_in_cset(struct _cset*,char);
int is_in_set(void*,int value, int type);

void add_to_iset(struct _iset**,int i);
void add_to_cset(struct _cset**,char c);
void add_to_set(void**,int i, int type);

void remove_from_iset(struct _iset**,int i);
void remove_from_cset(struct _cset**,char c);
void remove_from_set(void**,int i, int type);


void add_iset_to_sa(void *, void *);
void add_cset_to_sa(void *, void *);
void add_set_to_sa(void *, void *, int type);

struct _iset * merge_isets(struct _iset *, struct _iset*);
struct _cset * merge_csets(struct _cset *, struct _cset*);
void * merge_sets(void *, void*, int type);

struct _iset * copy_iset(struct _iset *);
struct _cset * copy_cset(struct _cset *);
void * copy_sets(void*, int type);

void display_set(void *s, int type);

int sets_are_same(void *s1, void* s2, int type);
int isets_are_same(void *s1, void* s2);
int csets_are_same(void *s1, void* s2);


struct _iset * msort_set(struct _iset* is);
struct _iset * msort_set_helper(struct _iset* is,int start,int finish);
struct _iset * msmerge_isets(struct _iset **l,struct _iset **r);

int snum_deleted(void);
int snum_created(void);
int asnum_deleted(void);
int asnum_created(void);
#endif
