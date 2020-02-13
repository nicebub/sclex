#include "../include/set.h"

#define NEWSETERROR(in) printf("couldn't create new " #in "set\n");

static int iunq=1;
static int cunq=1;
static int idinc = 0;
static int deleted = 0;
static int asinc = 0;
static int asdeleted = 0;
struct _iset * create_iset(int size){
    return create_set(size,0);
}
struct _cset * create_cset(int size){
    return create_set(size,1);
}
void * create_set(int size, int type){
    struct _iset *i;
    struct _cset *c;
    i = NULL;
    c = NULL;
    switch(type){
	   case 0:
		  i = malloc(sizeof(struct _iset));
		  i->s = malloc(sizeof(int)*size);
		  for(int a=0;a<size;a++)
			 i->s[a] = -1;
		  i->size = size;
		  i->used = 0;
		  i->uniq = iunq;
		  iunq++;
		  i->id = idinc;
		  idinc++;
		  return i;
	   default:
		  c = malloc(sizeof(*i));
		  c->s = malloc(sizeof(char)*size);
		  for(int a=0;a<size;a++)
			 c->s[a] = '\0';
		  c->size = size;
		  c->used = 0;
		  c->uniq = cunq;
		  cunq++;
		  c->id = idinc;
		  idinc++;
		  return c;
    }
    return NULL;
}

void delete_iset(struct _iset * s){
    delete_set(s,0);
}
void delete_cset(struct _cset * s){
    delete_set(s,1);

}
void delete_set(void * s, int type){
    struct _iset *i;
    struct _cset *c;
    i = NULL;
    c = NULL;
    if(s){
	   switch(type){
		  case 0:
			 i = (struct _iset *)s;
			 free(i->s);
			 i->s = NULL;
			 free(i);
			 i=NULL;
			 deleted++;
			 break;
		  default:
			 c = (struct _cset *)s;
			 free(c->s);
			 c->s = NULL;
			 free(c);
			 c=NULL;
			 deleted++;
			 break;
	   }
    }
}

int is_in_iset(struct _iset *s,int i){
    return is_in_set(s,i,0);
}
int is_in_cset(struct _cset *s,char c){
    return is_in_set(s,c,1);
}
int is_in_set(void * s,int value, int type){
    struct _iset *i;
    struct _cset *c;
    i = NULL;
    c = NULL;
    if(s){
	   switch(type){
		  case 0:
			 i = (struct _iset*)s;
			 for(int y=0;i->s[y]<=value && y<i->used;y++){
				if(i->s[y] == value)
				    return 0;
			 }
			 return 1;
		  default:
			 c = (struct _cset*)s;
			 for(int y=0;c->s[y]<=value && y<c->used;y++){
				if(c->s[y] == value)
				    return 0;
			 }
			 return 1;
	   }
    }
    return 1;
}

void add_to_iset(struct _iset** s,int i){
     add_to_set((void**)s,i,0);
}
void add_to_cset(struct _cset **s,char c){
     add_to_set((void**)s,c,1);

}
void add_to_set(void** s,int v, int type){
    struct _iset *i, *itp;
    struct _cset *c, *ctp;
    i = itp = NULL;
    c = ctp = NULL;
    
    if(*s){
	   int y;
	   switch(type){
		  case 0:
			 i = (struct _iset*)*s;
			 if(i->used >= i->size) return;
			 itp = create_iset(i->size);
			 for( y=0;y<i->used;y++){
				if(i->s[y] == v){
				    delete_iset(itp);
				    itp = NULL;
				    return;
				}
				if(i->s[y] > v){
				    itp->s[y] = v;
				    itp->used++;
				    for(int a=y;a<i->used;a++){
					   itp->s[a+1] = i->s[a];
					   itp->used++;
				    }
				    delete_iset(i);
				    i = NULL;
				    *s = itp;
				    return;
				}
				itp->s[y] = i->s[y];
				itp->used++;
			 }
			 itp->s[y] = v;
			 itp->used++;
			 delete_iset(i);
			 i = NULL;
			 *s = itp;
			 return;
		  default:
			 c = (struct _cset*)*s;
			 if(c->used >= c->size) return;
			 ctp = create_cset(c->size);
			 for( y=0;y<c->used;y++){
				if(c->s[y] == v){
				    delete_cset(ctp);
				    ctp = NULL;
				    return;
				}
				if(c->s[y] > v){
				    ctp->s[y] = v;
				    ctp->used++;
				    for(int a=y;a<c->used;a++){
					   ctp->s[a+1] = c->s[a];
					   ctp->used++;
				    }
				    delete_cset(c);
				    c = NULL;
				    *s = ctp;
				    return;
				}
				ctp->s[y] = c->s[y];
				ctp->used++;
			 }
			 ctp->s[y] = v;
			 ctp->used++;
			 delete_cset(c);
			 c = NULL;
			 *s = ctp;
			 return;
	   }
    }
    return;
}

void remove_from_iset(struct _iset** s,int i){
     remove_from_set((void**)s,i,0);
}
void remove_from_cset(struct _cset** s,char c){
     remove_from_set((void**)s,c,1);
}
void remove_from_set(void** s,int i, int type){
    struct _iset *is, *ist;
    struct _cset *cs, *cst;
    is = NULL;
    cs = NULL;
//    int t;
    if(*s){
	   switch(type){
		  case 0:
			 is = (struct _iset *)*s;
			 ist = create_iset(is->size);
			 for(int a=0;a<is->used;a++){
				if(is->s[a] == i){
				    continue;
				}
				ist->s[ist->used] = is->s[a];
				ist->used++;
			 }
			 delete_iset(is);
			 is = NULL;
			 *s = ist;
			 return;
		  default:
			 cs = (struct _cset *)s;
			 cst = create_cset(cs->size);
			 for(int a=0;a<cs->used;a++){
				if(cs->s[a] == i){
				    continue;
				}
				cst->s[cst->used] = cs->s[a];
				cst->used++;
			 }
			 delete_cset(cs);
			 cs = NULL;
			 *s = cst;
			 return;
	   }
    }
    return;
}


struct _iset * merge_isets(struct _iset * s1, struct _iset* s2){
    return merge_sets(s1,s2,0);

}
struct _cset * merge_csets(struct _cset * s1, struct _cset* s2){
    return merge_sets(s1,s2,1);

}
void * merge_sets(void * s1, void* s2, int type){
    struct _iset *i1, *i2,*it, *its;
    struct _cset *c1, *c2,*ct;
    i1 = i2 = it = NULL;
    c1 = c2 = ct = NULL;
    if(s1 && s2){
	   switch(type){
		  case 0:
			 i1 = (struct _iset*)s1;
			 i2 = (struct _iset*)s2;
			 it = copy_sets(i1,0);
			 for(int a=0;a<i2->used;a++){
				add_to_set((void**)&it,i2->s[a],0);
			 }
			 its = msort_set(it);
			 delete_iset(it);
			 it = NULL;
			 return its;
		  default:
			 c1 = (struct _cset*)s1;
			 c2 = (struct _cset*)s2;
			 ct = copy_sets(c1,1);
			 for(int a=0;a<c2->used;a++){
				add_to_set((void**)&ct,c2->s[a],1);
			 }
			 return ct;
	   }
    }
    return NULL;

}

struct _iset * copy_iset(struct _iset * s){
    return copy_sets(s,0);

}
struct _cset * copy_cset(struct _cset * s){
    return copy_sets(s,1);

}
void * copy_sets(void* s, int type){
    struct _iset *i,*it;
    struct _cset *c,*ct;
    i = it = NULL;
    c = ct = NULL;
    if(s){
	   switch(type){
		  case 0:
			 i =(struct _iset*)s;
			 it = create_set(i->size,0);
			 if(it == NULL){
				NEWSETERROR(i)
//				printf("couldn't create new iset\n");
				return NULL;
			 }
			 for(int a=0;a<i->used;a++)
				add_to_set((void**)&it,i->s[a],0);
			 it->uniq = i->uniq;
			 return it;
		  default:
			 c =(struct _cset*)s;
			 ct = create_set(c->size,1);
			 if(ct == NULL){
				NEWSETERROR(c)
//				printf("couldn't create new cset\n");
				return NULL;
			 }
			 for(int a=0;a<c->used;a++)
				add_to_set((void**)&ct,c->s[a],1);
			 ct->uniq = c->uniq;
			 return ct;
	   }
    }
    return NULL;

}


void display_set(void *s, int type){
    struct _iset *i;
    struct _cset *c;
    i = NULL;
    c = NULL;
    if(s){
	   printf("{");
	   switch(type){
		  case 0:
			 i = (struct _iset*)s;
			 for(int a=0;a<i->used;a++)
				printf("%d,",i->s[a]);
			 printf("}\n");
			 break;
		  default:
			 c = (struct _cset*)s;
			 for(int a=0;a<c->used;a++)
				printf("%c,",c->s[a]);
			 printf("}\n");
			 break;
	   }
    }
}


struct _iseta* create_iseta(int size){
    return create_seta(size,0);
}
struct _cseta* create_cseta(int size){
    return create_seta(size,1);

}
void * create_seta(int size, int type){
    struct _iseta * ia;
    struct _cseta * ca;
    ia = NULL;
    ca = NULL;
    switch(type){
	   case 0:
		  ia = malloc(sizeof(*ia));
		  ia->iset = malloc(sizeof(struct _iset*)*size);
		  for(int j=0;j<size;j++)
			 ia->iset[j] = NULL;
		  ia->size = size;
		  ia->used = 0;
		  ia->id = asinc;
		  asinc++;
		  return ia;
	   default:
		  ca = malloc(sizeof(*ca));
		  ca->cset = malloc(sizeof(struct _cset*)*size);
		  for(int j=0;j<size;j++)
			 ca->cset[j] = NULL;
		  ca->size = size;
		  ca->used = 0;
		  ca->id = asinc;
		  asinc++;
		  return ca;
    }
}

void delete_iseta(struct _iseta *s){
    delete_seta(s,0);
}
void delete_cseta(struct _cseta *s){
    delete_seta(s,1);

}
void delete_seta(void *s, int type){
    struct _iseta * ia;
    struct _cseta * ca;
    ia = NULL;
    ca = NULL;

    if(s){
	   switch(type){
		  case 0:
			 ia = (struct _iseta*)s;
			 for(int u=0;u<ia->used;u++){
				delete_iset(ia->iset[u]);
				ia->iset[u] = NULL;
			 }
			 free(ia);
			 ia = NULL;
			 asdeleted++;
			 break;
		  default:
			 ca = (struct _cseta*)s;
			 for(int u=0;u<ca->used;u++){
				delete_cset(ca->cset[u]);
				ca->cset[u] = NULL;
			 }
			 free(ca);
			 ca = NULL;
			 asdeleted++;
			 break;
	   }
    }
}
void add_iset_to_sa(void *s, void *sa){
    add_set_to_sa(s,sa,0);
}
void add_cset_to_sa(void *s, void *sa){
    add_set_to_sa(s,sa,1);
}

void add_set_to_sa(void *s, void *sa, int type){
    struct _cset * cs;
    struct _cseta * csa;
    struct _iset *is;
    struct _iseta * isa;
    cs = NULL;
    csa = NULL;
    is = NULL;
    isa = NULL;
    if(sa && s){
	   switch(type){
		  case 0:
			 isa = (struct _iseta*)sa;
			 is = (struct _iset*)s;
			 if(isa->used >= isa->size)
				return;
			 isa->iset[isa->used] = copy_iset(is);
			 isa->used++;
			 break;
		  default:
			 csa = (struct _cseta*)sa;
			 cs = (struct _cset*)s;
			 if(csa->used >= csa->size)
				return;
			 csa->cset[csa->used] = copy_cset(cs);
			 csa->used++;
			 break;
	   }
    }
}
int sets_are_same(void *s1, void* s2, int type){
    struct _iset *is1, *is2;
    struct _cset *cs1, *cs2;
    is1 = is2 = NULL;
    cs1 = cs2 = NULL;
    if(s1 && s2){
	   switch(type){
		  case 0:
			 is1 = (struct _iset*)s1;
			 is2 = (struct _iset*)s2;
			 if(is1->used != is2->used)
				return 0;
			 int g;
			 for(g=0;is1->s[g] <=is2->s[g] && g<is1->used;g++){
				if(is1->s[g] != is2->s[g])
				    return 0;
			 }
			 if(g>=is1->used)
				return 1;
			 return 0;
		  default:
			 cs1 = (struct _cset*)s1;
			 cs2 = (struct _cset*)s2;
			 break;
	   }
    }
    return -1;
}
int isets_are_same(void *s1, void* s2){
    return sets_are_same(s1,s2,0);

}
int csets_are_same(void *s1, void* s2){
    return sets_are_same(s1,s2,1);
}


struct _iset * msort_set(struct _iset* is){
    return msort_set_helper(is, 0,is->used-1);
}

struct _iset * msort_set_helper(struct _iset* is,int start,int finish){
    struct _iset *l, *r;
    struct _iset * merged;
    l = r = NULL;
    merged = NULL;
    if(is){
	   if(start > finish)
		  return NULL;
	   if(start == finish){
		  l = create_iset(is->size);
		  if(l == NULL){
			 NEWSETERROR()
//			 printf("couldn't create new set\n");
			 return NULL;
		  }

		  add_to_iset(&l,is->s[start]);
		  return l;
	   }
	   l =  msort_set_helper(is,start,(start+finish)/2);
	   r = msort_set_helper(is,(start+finish)/2+1,finish);
	   merged = msmerge_isets(&l,&r);
	   delete_iset(l);
	   delete_iset(r);
	   l = NULL;
	   r = NULL;
	   return merged;
    }
    return NULL;
}

struct _iset * msmerge_isets(struct _iset **l,struct _iset **r){
    struct _iset * final;
    final = NULL;
    if(*l && *r){
	   final = create_iset((*l)->size);
	   if(final == NULL){
		  NEWSETERROR()
//		  printf("couldn't create new set\n");
		  return NULL;
	   }

	   while((*l)->used != 0 && (*r)->used != 0){
		  if((*l)->s[0] < (*r)->s[0]){
			 add_to_iset(&final,(*l)->s[0]);
			 remove_from_iset(l,(*l)->s[0]);
		  }
		  else{
			 add_to_iset(&final,(*r)->s[0]);
			 remove_from_iset(r,(*r)->s[0]);

		  }
	   }
	   while((*l)->used != 0){
		  add_to_iset(&final,(*l)->s[0]);
		  remove_from_iset(l,(*l)->s[0]);
	   }
	   while((*r)->used != 0){
		  add_to_iset(&final,(*r)->s[0]);
		  remove_from_iset(r,(*r)->s[0]);
	   }
	   return final;
    }
    return NULL;
}

int snum_deleted(void){
    return deleted;
}
int snum_created(void){
    return idinc;
}
int asnum_deleted(void){
    return asdeleted;
}
int asnum_created(void){
    return asinc;
}
