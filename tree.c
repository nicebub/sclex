#include "tree.h"

void delete_node(struct _node*);
void add_node_to_tree(struct _node*, struct _tree*);

 static int m_nodes=1;
static int idinc = 0;
static int ndeleted = 0;
static int atinc = 0;
static int atdeleted = 0;
static int missinghelp =0;
inline int tnum_deleted(void){
    return ndeleted;
}

inline int tnum_created(void){
    return idinc;
}
inline int atnum_deleted(void){
    return atdeleted;
}

inline int atnum_created(void){
    return atinc;
}
inline int missingh(void){
    return missinghelp;
}


struct _node * create_node(char value){
    struct _node * n;
    n = NULL;
    
    if((n = malloc(sizeof(*n)))){
	   n->left = NULL;
	   n->right = NULL;
	   n->ifirst = NULL;
	   n->ilast = NULL;
	   n->ifollow = NULL;
	   n->value = value;
	   n->nullable = -1;
	   n->id = idinc;
	   idinc++;
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
    if(n){
	   n->left = NULL;
	   n->right = NULL;
	   delete_set(n->ifirst,0);
	   n->ifirst = NULL;
	   delete_set(n->ilast,0);
	   n->ilast = NULL;
	   delete_iset(n->ifollow);
	   n->ifollow = NULL;
	   missinghelp += n->id;
	   free(n);
	   n = NULL;
	   ndeleted++;
    }
}
struct _tree * create_tree(void){
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
void add_node_to_tree(struct _node* n, struct _tree* t){
    
}
void delete_tree(struct _tree* t){
    if(t){
	   if(t->root){
		  delete_root(t->root);
		  t->root = NULL;
		  free(t);
		  t = NULL;
	   }
    }
}

void delete_root(struct _node * n){
    struct _node * left;
    struct _node *right;
    left = NULL;
    right = NULL;
    if(n){
	   left = n->left;
	   right = n->right;
	   n->left = NULL;
	   n->right = NULL;
	   delete_node(n);
	   n = NULL;
	   delete_root(left);
	   left = NULL;
	   delete_root(right);
	   right = NULL;
	   
    }
}

void display_tree(struct _node* n){
    if(n){
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
	   char rq;
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


struct _ta * create_ta(int size){
    struct _ta *temp;
    temp = NULL;
    int asize =100;
    temp = malloc(sizeof(*temp));
    temp->t = malloc(sizeof(*temp->t)*size);
    temp->alphabet = create_cset(asize);
    if(temp->alphabet == NULL){
	   printf("couldn't create new alphabet\n");
	   return NULL;
    }

    temp->action_array = malloc(sizeof(char*)*size);
    temp->Fstates = malloc(sizeof(*temp->Fstates)*size);
    for(int r=0;r<size;r++){
	   temp->t[r] = NULL;
	   temp->action_array[r] = NULL;
	   temp->Fstates[r] = NULL;
    }
    temp->atop = NULL;
    temp->size = 0;
    temp->used = 0;
    temp->id = atinc;
    temp->finalpos = malloc(sizeof(int)*size);
    temp->num_re = 0;
    atinc++;
    return temp;
}

void delete_ta(struct _ta * ta){
    if(ta){
	   delete_root(ta->atop);
	   ta->atop = NULL;
	   for(int f=0;f<ta->used;f++){
		  ta->t[f] = NULL;
		  free(ta->action_array[f]);
		  ta->action_array[f] = NULL;
		  delete_iset(ta->Fstates[f]);
		  ta->Fstates[f] = NULL;
	   }
	   free(ta->action_array);
	   ta->action_array = NULL;
	   delete_cset(ta->alphabet);
	   ta->alphabet = NULL;
	   free(ta->finalpos);
	   ta->finalpos= NULL;
	   free(ta);
	   ta = NULL;
	   atdeleted++;
	   
    }
}

char get_value_for_uniq(struct _node * n, int u){
    char l,r;
    if(n){
	   if(n->uniq == u)
		  return n->value;
	   else{
		  l = get_value_for_uniq(n->left,u);
		  if(l != 0)
			 return l;
		  r = get_value_for_uniq(n->right,u);
		  if(r != 0)
			 return r;
	   }
    }
    return (char)0;
}

struct _node* get_node_for_uniq(struct _node * n, int u){
    struct _node * l,*r;
    l = r = NULL;
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
    return NULL;
}
