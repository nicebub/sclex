#ifdef __STRICT_ANSI__
#define inline
#endif

#define _POSIX_C_SOURCE 200809L
#include <strings.h>
#include "../include/type.h"
struct _type * create_type(const char* name, const int value,  struct _type *components);
void delete_type(struct _type * t);

void set_type_name(struct _type * t, char * n);
void set_type_value(struct _type *t, int v);
void set_type_comp(struct _type * t, struct _type * c);

char* get_type_name(struct _type * t);
int get_type_value(struct _type *t);
struct _type * get_type_comp(struct _type * t);

struct _tsys * create_tsys(void);
void delete_tsys(struct _tsys * s);

void init_tsys(struct _tsys *, size_t size);
void enlarge_type_array(struct _type ** array, const int add);
void add_type_to_tsys(struct _tsys * s, struct _type * t);
void remove_type_from_tsys(struct _tsys *s, void * v, const int type);
void remove_type_from_tsyst(struct _tsys *s, struct _type *t);
void remove_type_from_tsysn(struct _tsys *s, char * name);
void remove_type_from_tsysv(struct _tsys *s, const int value);
struct _type * get_type_from_name(struct _tsys *s,char * name );
struct _type * get_type_from_value(struct _tsys *s, int value );
/*struct _type * tpcpy(struct _type ** array);*/


struct _type * create_type(const char* name, const int value,  struct _type *components){
    struct _type *t;
    t = malloc(sizeof(*t));
    t->name = strdup(name);
    t->value = value;
    t->components = components;
    return t;
}

void delete_type(struct _type * t){
    if(t){
	   free(t->name);
	   t->name = NULL;
	   if(t->components){
		  delete_type(t->components);
		  t->components = NULL;
	   }
	   free(t);
	   t = NULL;
    }
}


inline void set_type_name(struct _type * t, char * n){
    if(t->name){
	   free(t->name);
	   t->name = NULL;
	   t->name = strdup(n);
    }
}
inline void set_type_value(struct _type *t, int v){
    t->value = v;
}
inline void set_type_comp(struct _type * t, struct _type * c){
    t->components = c;
}

inline char* get_type_name(struct _type * t){
    return t->name;
}
inline int get_type_value(struct _type *t){
    return t->value;
}
inline struct _type * get_type_comp(struct _type * t){
    return t->components;
}

 struct _tsys * create_tsys(void){
    struct _tsys *s;
    s = malloc(sizeof(*s));
    s->type = NULL;
    init_tsys(s, TINIT_SIZE);
    return s;
}
void delete_tsys(struct _tsys * s){
    if(s){
		int e;
	   for(e=0;e<s->used;e++){
		  delete_type(s->type[e]);
		  s->type[e]= NULL;
	   }
	   s->size = 0;
	   s->used = 0;
	   free(s);
	   s = NULL;
    }
}

inline void init_tsys(struct _tsys * s, size_t size){
	int a;
    s->type = malloc(sizeof(struct _type*)*size);
    for(a=0;a<size;a++)
	   s->type[a] = NULL;
    s->size = size;
    s->used = 0;
}
inline void enlarge_type_array(struct _type ** array, const int add){
    struct _type ** newa;
    int zz = sizeof(*array);
    if(add >0){
 	   int v;
	   newa = realloc(array,zz+(sizeof(struct _type*)*add));
	   for(v=0;v<add;v++)
		  newa[zz+v] = NULL;
    }
}
void add_type_to_tsys(struct _tsys * s, struct _type * t){
    if(s->used == s->size){
	   enlarge_type_array(s->type,TRSIZE_AMT);
	   s->size = s->size + TRSIZE_AMT;
    }
    s->type[s->used] = t;
    s->used++;
}
void remove_type_from_tsys(struct _tsys *s, void *v, const int type){
    
    struct _type *p;
    int g;
    struct _type *t;
    char * name;
    int value;
    switch(type){
	   case 4:
		  	t = (struct _type*) v;
		  	for(g=0;g<s->used;g++){
			    if(s->type[g] == t){
				   p = s->type[g];
				   s->type[g] = NULL;
				   delete_type(t);
				   t = NULL;
				   s->used--;
				   break;
			    }
    			}
		  break;
	   case 3:
		  break;
	   case 2:
		  name = (char*)v;
		  for(g=0;g<s->used;g++){
			 if(strcmp(s->type[g]->name,name)){
				p = s->type[g];
				s->type[g] = NULL;
				delete_type(p);
				p = NULL;
				s->used--;
				break;
			 }
		  }

		  break;
	   case 1:
		  break;
	   case 0:
		  value = *(int*)v;
		  for(g=0;g<s->used;g++){
			 if(s->type[g]->value == value){
				p = s->type[g];
				s->type[g] = NULL;
				delete_type(p);
				p = NULL;
				s->used--;
				break;
			 }
		  }

		  break;
    }
}
inline void remove_type_from_tsyst(struct _tsys *s, struct _type *t){
    remove_type_from_tsys(s,t,4);
}
inline void remove_type_from_tsysn(struct _tsys *s, char * name){
    remove_type_from_tsys(s,name,2);
}
inline void remove_type_from_tsysv(struct _tsys *s,  int value){
    remove_type_from_tsys(s,&value,0);
}

struct _type *get_type_from(struct _tsys *s, void * v, int type){
    char * name;
    int value;
    if(s && v){
	   switch(type){
		  case 2:
			 name = (char*)v;
			 {
				 int k;
				for(k=0;k<s->used;k++){
				    if(strcmp(s->type[k]->name,name)){
					   return s->type[k];
				    }
				}
			}
			 break;
		  case 0:
			 	value = *(int*)v;
				{
					int k;
				for(k=0;k<s->used;k++){
				    if(s->type[k]->value == value){
					   return s->type[k];
				    }
				}
			}
			 break;
	   }
    }
    return NULL;
}

struct _type * get_type_from_name(struct _tsys *s,char * name ){
    return get_type_from(s,name,2);
}
struct _type * get_type_from_value(struct _tsys *s, int value ){
    return get_type_from(s,&value,0);
}
