#ifndef MTREE_H
#define MTREE_H
#include <stdlib.h>
#include <stdio.h>
#include "baseset.h"
#include "intset.h"
#include "chrset.h"
#include "funcs.h"

/* These macro definitions are used for permanent tokens 
 and use negative number to not get confused with other
tokens or user-defined tokens. */
#define COMMA -253
/* Used as a token for symbolic representation of a 
	regular expression number of repetitions spec, ie.
	a{1,4} any concat of 1-4 a's {1,4] is a repetition */
#define REPS -254
#define MINUS -255
/* a character set or class token */
#define CHARSET -256
/* Epsilon is the empty string token */
#define EPSILON -257
/* concatenator operator token */
#define CONCAT -258
/* Inclusive OR operator token */
#define OR -259
/* Kleene Star Operator token  */
#define STAR -260
/* Question Mark, so in regular expression terms, the 0 or 1
	repetition operator */
#define QUEST -261
#define PLUS -262
/* EMPTY string token */
#define EMPTY -263

/* the largest set size of an alphabet */
#define ALPHABET_SIZE 100
/** Structure Definition
	A _node is a structure that we use to create a tree of nodes
that all link up with each other. We use a Binary Tree, but it 
can be configured to be more than a binary tree.

struct _node 

    struct _node *left: A pointer to the left Child of the current node

    struct _node *right: A pointer to the right Child of the current node

    struct _iset *ifirst: The firstpos set of the tree starting at the
					current node

    struct _iset *ilast: The lastpos set of the tree starting at the
					current node

    struct _iset *ifollow: The followpos set of the tree starting at the
					current node
    int uniq: A unique ID given to each _node instantiated by the _node
					constructor. No two nodes can have the same 'uniq'.

    int id: An id given to a node, but can be changed. Two nodes can have the
				same 'id'.

    int nullable: An answer as to whether the tree starting at the current node
					is 'nullable' or not, as per the nullable function.

    char value: The value the _node holds, for semantic, numerical, or other use.

*/
typedef struct _node TreeNode;
struct _node {
    struct _node *left;
    struct _node *right;
    base_set *ifirst; /* int_set* */
    base_set *ilast;	/* int_set* */
    base_set *ifollow;	/* int_set* */
    int uniq;
    int id;
    int nullable;
    char value;
};
/** Structure Definition

The tree _tree structure is used to wrap the tree of _node's
	with a pointer to the root of the tree _node* root, and
a size and depth to the tree. This struct is used very little
at this time, and is saved for future use.

struct _tree 

    struct _node *root: A pointer to the root _node of the tree

    int depth: The depth of the tree, ie, the maximum edges from the,
				lowest child to the root.

    int size: The total amount of _nodes in the tree.

*/
typedef struct _tree Tree;
struct _tree {
    struct _node *root;
    int depth;
    int size;
};

/** Structure Definition

The _ta structure is an Array of Tree's. This struct has additional
	members that could be broken out, as they may not have much meaning
	in the context of a Tree Array. But in the use of the existing program,
	I didn't want to make certain functions take too many parameters, and
	instead, stuffed certain shared data structures into others.
Otherwise, the Tree Array, has a certain size, id, and root.

struct _ta 

    struct _node **t: An array of _node pointers, which would represent
						individual binary trees

    struct _node *atop: The top of the whole entire Binary tree, as each
							individual tree in the array will all be
							attached to one another.

    struct _cset *alphabet: The alphabet of the regular expressions read
								in the existing program

    char**  action_array: The specific user-defined source code that is 
							attached to each regular expression, in the
							existing programs, spec file.

    struct _iset **Fstates: The Array of Final states, each Tree/Regular
								Expression uses as an accept state in the constructed
								DFA representation.

    int *finalpos: The array of finalpos set for the entire Tree Array

    int size: The max size of the Tree Array

    int used: The actual number of Tree's that we are using in the Array

    int num_re: The number of regular expression in the application we 
					have read in and recoginzed thus far

    int id: The identification 'ID' for the _ta struct. Each _ta instantiated
				will have an 'id' from its constructor.

*/
typedef struct _ta TreeArray;
struct _ta {
    struct _node **t;
    struct _node *atop;
    base_set *alphabet; /* char_set* */
    char**  action_array;
    base_set **Fstates; /* int_set** */
    int *finalpos;
    int size;
    int used;
    int num_re;
    int id;
};

void initTreeArray(TreeArray* treeArray);
/** Function Prototype
A constructor for a node, with an input value

	struct _node * create_node(char value);

Functionality: Instantiates in memory a new _node structure
	with the value of the input character and returns a pointer
	to the new _node to the caller.

Parameters: a character, char value, to store in the new _node

Returns: a pointer to a _node struct, struct _node* or NULL if there is
	an error

Results: Either a new node with the input value is created in memory and returned
	to the caller, or NULL is returned on Error

*/
struct _node * create_node(char value);

/** Function Prototype
A constructor for a _tree, takes no input

	struct _tree * create_tree(void);

Functionality: A new _tree struct is created in memory, initialized and a pointer
	to its address is returned

Parameters: none

Returns: a pointer to a _tree struct, _tree* or NULL if an error occurs.

Results: Either NULL is returned, or a _tree struct is created and initialized in memory
			and a pointer to it is returned.

*/
struct _tree * create_tree(void);

/** Function Prototype
A constructor for a Tree Array, with an input on its initial maximum size.

	struct _ta * create_ta(int size);

Functionality: Create a Tree Array in memory of size 'size' and return a pointer
	to its memory address to the caller

Parameters: an integer specifying the initial maximum number to the Array.

Returns: A pointer to a _ta struct, _ta*, or NULL if an error occurs.

Results: A _ta tree Array struct is created and initialized in memory and returned
	to the caller, or an error occurs, and NULL is returned.

*/
struct _ta * create_ta(int size);

/** Function Prototype
Destructor for the _ta struct, and all the tree's in the array

	void delete_ta(struct _ta*);

Functionality: Give any memory used by the _ta struct back to the operating system

Parameters: A pointer to an initialized _ta structure. 

Results: The _ta struct data no longer is valid or exists in memory.

*/
void delete_ta(struct _ta*);

/** Function Prototype
Destructor for the _tree structure and all the _nodes internal to its struct

	void delete_tree(struct _tree*);

Functionality: Release the memory used by the input _tree and give it back to the
	operating system.

Parameters: a pointer to an initialized _tree structure.

Results: The _tree structure data is no longer valid or exists and the memory it used
	is returned back to the oeprating system.

*/
void delete_tree(struct _tree*);

/** Function Prototype
A helper function to delete the root of the _tree struct and all of lower nodes of the
	tree

	void delete_root(struct _node * n);

Functionality: Delete a full tree of _node's and return the memory back to the oeprating
	system.

Parameters: A initialized _node or tree of _nodes.

Results: In a full entire _node or tree of _nodes are invalidated, and their memory is
	returned back to the operating system.

*/
void delete_root(struct _node * n);

/** Function Prototype

Debug Function to print to standard output a tree of _nodes

	void display_tree(struct _node *);

Functionality: display on standard output an ascii visual of the sybolic representation
	of the linked _nodes

Parameters: any pointer to a _node, usual a root of a tree

Results: The tree is dsiplayed on standard output

*/
void display_tree(struct _node *);

/** Function Prototype
Given a 'uniq', which is a _node unique identifier, return its character value being
	stored in that node

	char get_value_for_uniq(struct _node *, int);

Functionality: Take a tree starting at some _node, and search it for the matching 'uniq'
	to the given input. If one matches, then its character value is returned to the caller.

Parameters: A pointer to _node, which generally is a binary tree, an integer representing
	a 'uniq' value used as the key for searching

Returns: either an error, the NULL character, or if found, the character value for the given
	'uniq'

Results: A 'uniq' _node is found and its value is returned back to the caller. If the tree is
	searched and no match is found, then an error occurs and an error character is returned.

*/
char get_value_for_uniq(struct _node *, int);

/** Function Prototype
Given a 'uniq' and a tree, return the _node whose 'uniq' matches the one given as input.

	struct _node * get_node_for_uniq(struct _node *, int);

Functionality: Take in a pointer to a tree of _nodes and an integer representation of a 'uniq'.
	If during a search of the tree a 'uniq' matches one in the tree, a pointer to that _node is
	returned.

Parameters: A pointer to a _node, which may be a binary tree, and an integer representing a 
	'uniq'.

Returns: A pointer to a _node structure. This will be a single _node, or NULL if no match.

Results: Either a _node was found and returned or, NULL is returned because a node with the
	input 'uniq' isn't part of the searched tree.

*/
struct _node * get_node_for_uniq(struct _node *, int);

/** Function Prototype
DEBuG - return the amount of tree's deleted

	int tnum_deleted(void);

Functionality: return from the internal counter of the number of trees deleted so far during
	program execution

Returns: an integer
*/
int tnum_deleted(void);
/** Function Prototype
DEBUG - return the amount of tree's created
	int tnum_created(void);

Functionality: return from an internal counter of trees, the amount created trees so far during
 the program execution

Returns: an integer 

*/
int tnum_created(void);
/** Function Prototype
DEBuG - return the number of tree Array's deleted
	int atnum_deleted(void);

Functionality: returns from an internal counter of tree arrays, the number of tree arrays that 
	have been deleted so far during program execution

Returns: an integer

*/
int atnum_deleted(void);
/** Function Prototype
DEBuG - return the number of tree Array's created
	int atnum_created(void);

Functionality: returns from an internal counter of tree arrays, the number of tree arrays that
	have been created so far, during program execution

Returns: an integer

*/
int atnum_created(void);
/** Function Prototype
DEBuG - return the amount of missing _nodes we can't account for but know exist
	int missingh(void);

Functionality: returns from an internal counter the number of missing _nodes

Returns: an integer

*/
int missingh(void);

#endif
