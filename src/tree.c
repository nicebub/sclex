/**
 This file includes definitions to manipulate, construct
and use _node, _tree, and _ta structures defined in 
tree.h. A binary tree is constructed of _nodes, with each _node
with a left and right child pointer that each point to 2 children.
Thus each node can grow the tree by 2. Some _nodes may have no
children, they are 'leaves' of the tree. Some _nodes 'internal'
may have only 1 child. 1 _node is the root of the tree.
*/

#ifdef __STRICT_ANSI__
#define inline
#endif
#include "tree.h"
#include "log.h"

/** Function Prototype 

	void delete_node(struct _node*);

Functionality:
Parameters:
Returns:
Results:

*/
void delete_node(struct _node*);

/** Function Prototype 

	void delete_node(struct _node*);

Functionality:
Parameters:
Returns:
Results:

*/
void add_node_to_tree(struct _node*, struct _tree*);


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

/** DEBUGGING FUNCTIONS AND VARIABLES **/
static int m_nodes=1;
static int idinc = 0;
static int ndeleted = 0;
static int atinc = 0;
static int atdeleted = 0;
static int missinghelp =0;
extern inline int tnum_deleted(void)
{
    return ndeleted;
}

extern inline int tnum_created(void)
{
    return idinc;
}
extern inline int atnum_deleted(void)
{
    return atdeleted;
}

extern inline int atnum_created(void)
{
    return atinc;
}
extern inline int missingh(void)
{
    return missinghelp;
}


void initTreeArray(TreeArray* treeArray){
	treeArray->t =NULL;
	treeArray->atop = NULL;
	treeArray->alphabet = NULL;
	treeArray-> action_array = NULL;
	treeArray->Fstates = NULL;
	treeArray->finalpos = NULL;
	treeArray->size = 0;
	treeArray->used = 0;
	treeArray->num_re = 0;
	treeArray->id = 0;
}



/** END OF DEUBBGING FUNCTIONS AND VARIABLES */
struct _node * create_node(char value){
	/* _node n is used as the pointer to the memory allocated for the newly created
			_node. Return NULL if any errors, allocating memory */
    struct _node * n;
    n = NULL;
    
    if((n = malloc(sizeof(*n)))){
	   n->left = NULL;
	   n->right = NULL;
	   n->ifirst = NULL;
	   n->ilast = NULL;
	   n->ifollow = NULL;
	   n->value = value;
	   /* neither true or false */
	   n->nullable = -1;
	   /* the factory keeps track of how many id's go out */
	   n->id = idinc;
	   idinc++;
	   /* we only needed for specific _nodes to be 'uniq' for debugging so we tested for it. */
	   if(isalphanum(n->value) || isprintable(n->value) || n->value == '#' || n->value == (char)MINUS || isescape(n->value)){
		  	n->uniq = m_nodes;
		  	m_nodes++;
	   }
	   else
		  n->uniq = -1;
	   return n;
    }
    return NULL;
}

void delete_node(struct _node* n){
	/* Only try deleting _nodes that exist and then
		start to release memory. We do not recursively
		delete other attached _nodes. */
    if(n){
	   n->left = NULL;
	   n->right = NULL;
	   /* delete the firstpos set attached to this _node */
	   delete_set((base_set*)n->ifirst);
	   n->ifirst = NULL;
	   /* delete the lastpos set attached to this _node */
	   delete_set((base_set*)n->ilast);
	   n->ilast = NULL;
	   /* delete the followpos set attached to this _node */
	   delete_set((base_set*)n->ifollow);
	   n->ifollow = NULL;
	   /* debugging next step */
	   missinghelp += n->id;

	   free(n);
	   n = NULL;

	   ndeleted++;
    }
}

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
struct _tree * create_tree(void){
	/* t a _tree structure pointer will be used to access the newly created _tree 
		struct and it will be returned to the caller, if allocation issues, we 
		 return NULL */
    struct _tree * t;
    t = NULL;

    if((t=malloc(sizeof(*t)))){
	   t->depth = 0;
	   t->root = NULL;
	   t->size = 0;
	   return t;
    }
    return NULL;

}

/**
	 Unimplemented at this time
*/
/*
void add_node_to_tree(struct _node* n, struct _tree* t){
    
}
*/
/** Function Prototype
Destructor for the _tree structure and all the _nodes internal to its struct

	void delete_tree(struct _tree*);

Functionality: Release the memory used by the input _tree and give it back to the
	operating system.

Parameters: a pointer to an initialized _tree structure.

Results: The _tree structure data is no longer valid or exists and the memory it used
	is returned back to the oeprating system.

*/
void delete_tree(struct _tree* t){
	/* only try deleting exisitng trees */
    if(t){
	   if(t->root){
		   /* if we have a least 1 _node, then start deleting recursively, the _node 
		   	tree structure */
		  delete_root(t->root);
		  t->root = NULL;
		  free(t);
		  t = NULL;
	   }
    }
}

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
void delete_root(struct _node * n){
	/* temporary pointers used to help delete current _node before its children */
    struct _node * left;
    struct _node *right;
    left = NULL;
    right = NULL;
	/* as long as the _node exists, ideally, continue */
    if(n){
		/* take children away from current _node, if any */
	   left = n->left;
	   right = n->right;
	   n->left = NULL;
	   n->right = NULL;
	   /* delete a  single _node, no recursion, the input _node */
	   delete_node(n);
	   n = NULL;
	   /* now recursively delete the children of the input _node */
	   delete_root(left);
	   left = NULL;
	   delete_root(right);
	   right = NULL;
	   
    }
}

/** Function Prototype

Debug Function to print to standard output a tree of _nodes

	void display_tree(struct _node *);

Functionality: display on standard output an ascii visual of the sybolic representation
	of the linked _nodes

Parameters: any pointer to a _node, usual a root of a tree

Results: The tree is dsiplayed on standard output

*/
void display_tree(struct _node* n){
    if(n){
	   char rq;
	   if(n->value >= (char)CHARSET && n->value <= (char)COMMA)
		  switch(n->value){
			 case (char) COMMA:
				printf("{");
				break;
			 case (char) MINUS:
			 case (char) CHARSET:
				printf("[");
				break;

		  }
	   else if(n->value == (char)STAR || n->value == (char)PLUS
			 || n->value == (char)QUEST || n->value == (char)OR)
		  	printf("(");

	   display_tree(n->left);
	   if(n->value == (char)STAR || n->value == (char)PLUS || n->value == (char)QUEST)
		  printf(")");
	   if(n->value >= (char)CHARSET && n->value <=(char)COMMA)
		  switch(n->value){
			 case (char)COMMA:
				printf(",");
				break;
			 case (char)REPS:
				break;
			 case (char)MINUS:
				printf("-");
				break;

		  }
	   switch(n->value){
		  case (char)EMPTY:
			 rq = '\0';
			 break;
		  case (char)STAR:
			 rq = '*';
			 break;
		  case (char)OR:
			 rq = '|';
			 break;
		  case (char)CONCAT:
			 rq = '\0';
			 break;
		  case (char)PLUS:
			 rq = '+';
			 break;
		  case (char)QUEST:
			 rq = '?';
			 break;
		  default:
			 rq = n->value;
	   }
	   printf("%c",rq);
	   display_tree(n->right);
	   if(n->value >= (char)CHARSET && n->value <= (char)COMMA)
		  switch(n->value){
			 case (char)COMMA:
				printf("}");
				break;
			 case (char)MINUS:
			 case (char) CHARSET:
				printf("]");
				break;

		  }
	   else if(n->value == (char)OR)
		  printf(")");
    }
}


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
struct _ta * create_ta(int size){
	/* temporary pointer user to setup the newly created tree array */
    struct _ta *temp;
    temp = NULL;
	
/*    int asize =100;*/
	/* TODO add statements to check to see if either of these mallocs were successful
		or not */
    temp = malloc(sizeof(*temp));
    if(!temp){
	   LOG_ERROR("couldn't create temp in %s","create_ta\n");
	   return NULL;
    }
    temp->t = NULL;
    temp->t = malloc(sizeof(*(temp->t))*size);
    if(!temp->t){
	   LOG_ERROR("couldn't create *temp->t in %s","create_ta\n");
	   free(temp);
	   temp = NULL;
	   return NULL;
    }
    temp->alphabet = NULL;
    temp->alphabet = new_char_set(ALPHABET_SIZE);
	/* we did check for successful mallocs here though */
    if(temp->alphabet == NULL){
	   LOG_ERROR("couldn't create %s","new alphabet\n");
	   free(temp->t);
	   temp->t=NULL;
	   free(temp);
	   temp=NULL;
	   return NULL;
    }
	/* TODO the below mallocs also have not been checked to see if they were
		successfull or not. */
    temp->action_array = malloc(sizeof(char*)*size);
    temp->Fstates = malloc(sizeof(*temp->Fstates)*size);
	/* we have size _tree's in our array of size 'size'. */
	{
		int r;
    for(r=0;r<size;r++){
	   temp->t[r] = NULL;
	   temp->action_array[r] = NULL;
	   temp->Fstates[r] = NULL;
    }
}
    temp->atop = NULL;
    temp->size = 0;
    temp->used = 0;
    temp->id = atinc;
	/* TODO check this next malloc to see if it was successful or not */
    temp->finalpos = malloc(sizeof(int)*size);
	/* we have not found and stored any regular expressions yet */
    temp->num_re = 0;
	/* internal factory counter that keeps track of how many tree arrays we've created */
    atinc++;

    return temp;
}

/** Function Prototype
Destructor for the _ta struct, and all the tree's in the array

	void delete_ta(struct _ta*);

Functionality: Give any memory used by the _ta struct back to the operating system

Parameters: A pointer to an initialized _ta structure. 

Results: The _ta struct data no longer is valid or exists in memory.

*/
void delete_ta(struct _ta * ta){
	/* check to see if ta exists, or is valid */
    if(ta){
		/* recursively delete the whole tree */
	   delete_root(ta->atop);
	   ta->atop = NULL;
	   /* free other data structures we've created over our use */
	   {
		   int f;
		   for(f=0;f<ta->used;f++){
		 	 ta->t[f] = NULL;
		 	 free(ta->action_array[f]);
		  	ta->action_array[f] = NULL;
			  delete_set((base_set*)ta->Fstates[f]);
			  ta->Fstates[f] = NULL;
	  	 }
	   }
	   free(ta->action_array);
	   ta->action_array = NULL;
	   /* delete the final structures attached out our tree array, and then finaly the
	   	 array itself */
	   delete_set((base_set*)ta->alphabet);
	   ta->alphabet = NULL;
	   free(ta->finalpos);
	   ta->finalpos= NULL;
	   free(ta);
	   ta = NULL;
	   /* DEBUG - the factory counter is incremented to keep track for later use */
	   atdeleted++;
	   
    }
}

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
char get_value_for_uniq(struct _node * n, int u){
	/* temporary characters 'l' and 'r' used to store values from 
		recursively calling the function on its own children */
    char l,r;
	/* if we aren't NULL */
    if(n){
	   if(n->uniq == u)
		  return n->value;
	   else{
		  l = get_value_for_uniq(n->left,u);
		  /* check against a NULL character */
		  if(l != 0)
			 return l;
		  r = get_value_for_uniq(n->right,u);
		  /* check against a NULL character */
		  if(r != 0)
			 return r;
	   }
    }
	/* return the NULL character because we are a NULL _node */
    return (char)0;
}

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
struct _node* get_node_for_uniq(struct _node * n, int u){
	/* _node pointers 'l' and 'r' are used to store the results from recursively calling this
		function on its own children */
    struct _node * l,*r;
    l = r = NULL;
	/* if n is a _node and isn't NULL */
    if(n){
	   if(n->uniq == u)
		  return n;
	   else{
		  l = get_node_for_uniq(n->left,u);
		  if(l)
			 return l;
		  r = get_node_for_uniq(n->right,u);
		  if(r)
			 return r;
	   }
    }
	/* n is not a _node so return NULL */
    return NULL;
}
