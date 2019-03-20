#ifndef MTREE_H
#define MTREE_H
#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include "funcs.h"

#define COMMA -253
#define REPS -254
#define MINUS -255
#define CHARSET -256
#define EPSILON -257
#define CONCAT -258
#define OR -259
#define STAR -260
#define QUEST -261
#define PLUS -262
#define EMPTY -263

struct _node {
    struct _node *left;
    struct _node *right;
    struct _iset *ifirst;
    struct _iset *ilast;
    struct _iset *ifollow;
    int uniq;
    int id;
    int nullable;
    char value;
};

struct _tree {
    struct _node *root;
    int depth;
    int size;
};

struct _ta {
    struct _node **t;
    struct _node *atop;
    struct _cset *alphabet;
    char**  action_array;
    struct _iset **Fstates;
    int *finalpos;
    int size;
    int used;
    int num_re;
    int id;
};

struct _node * create_node(char value);

struct _tree * create_tree(void);
struct _ta * create_ta(int size);
void delete_ta(struct _ta*);

void delete_tree(struct _tree*);
void delete_root(struct _node * n);
void display_tree(struct _node *);

char get_value_for_uniq(struct _node *, int);
struct _node * get_node_for_uniq(struct _node *, int);

int tnum_deleted(void);
int tnum_created(void);
int atnum_deleted(void);
int atnum_created(void);
int missingh(void);

#endif
