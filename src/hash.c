#include "../include/hash.h"


struct _hashnode *create_hashnode(void * v, int vt, void * k, int kt);
void delete_hashnodel(struct _hashnode* hn);

void set_hnode_value(struct _hashnode*, void * v, int vt);
void set_hnode_key(struct _hashnode*, void * k, int kt);
void * get_hnode_value(struct _hashnode*);
void * get_hnode_key(struct _hashnode*);
int get_hnode_value_type(struct _hashnode* hn);
int get_hnode_key_type(struct _hashnode* hn);

struct _hashnode *remove_from_hash(struct _hash*,void* k, int kt);
struct _hr compute_hash_value(struct _hash*, void * key, int kt);
struct _hr search_cache(struct _hash * s, void * key, int kt);
static int uniques=0;

struct _hashnode *create_hashnode(void * v, int vt, void * k, int kt){
    struct _hashnode *h;
    h = malloc(sizeof(*h));
    h->key = malloc(sizeof(k));
    memcpy(h->key,k,sizeof(k));
    h->ktype = kt;
    h->next = NULL;
    h->value = malloc(sizeof(v));
    memcpy(h->value,v,sizeof(v));
    h->vtype = vt;
    h->uniq=uniques;
    uniques++;
    return h;
}
struct _hash *create_hash(int size){
    struct _hash *h;
    int cache_size = 100;
    h = malloc(sizeof(*h));
    h->size = 0;
    h->bucket = malloc(sizeof(*(h->bucket))*size);
    h->cache = malloc(sizeof(*(h->cache))*size*cache_size);
    for(int j=0,i=0;i<size*cache_size;i++){
	   h->cache[i].p = NULL;
	   h->cache[i].pt = -1;
	   h->cache[i].r = 0;
	   if(j<size){
		  h->bucket[j] = NULL;
		  j++;
	   }
    }
    h->csize = cache_size;
    h->cused = 0;
    h->size = size;
    h->used = 0;
 //   h->lasth = 0;
    h->alpha = 2;
    return h;
}
void delete_hashnode(struct _hashnode* hn){
    if(hn){
	   free(hn->key);
	   hn->key = NULL;
	   free(hn->value);
	   hn->value = NULL;
	   hn->next = NULL;
	   free(hn);
	   hn = NULL;
    }
}
void delete_hashnodel(struct _hashnode* hn){
    if(hn){
	   free(hn->key);
	   hn->key = NULL;
	   free(hn->value);
	   hn->value = NULL;
	   delete_hashnodel(hn->next);
	   hn->next = NULL;
	   free(hn);
	   hn = NULL;
    }
}


void delete_hash(struct _hash* h){
    if(h){
	   for(int t=1;t<=h->size;t++){
		  delete_hashnodel(h->bucket[t-1]);
		  h->bucket[t-1] = NULL;
	   }
	   for(int a=1;a<=h->csize;a++){
		  free(h->cache[a-1].p);
		  h->cache[a-1].p = NULL;
	   }
	   free(h->cache);
	   h->cache = NULL;
	   free(h);
	   h = NULL;
    }
}

void set_hnode_value(struct _hashnode* hn, void * v, int vt){
    if(hn){
	   hn->value = v;
	   hn->vtype = vt;
    }
}
void set_hnode_key(struct _hashnode* hn, void * k, int kt){
    if(hn){
	   hn->key = k;
	   hn->ktype = kt;
    }

}
void * get_hnode_value(struct _hashnode* hn){
    if(hn){
	   return hn->value;
    }
    return NULL;
}
void * get_hnode_key(struct _hashnode* hn){
    if(hn){
	   return hn->key;
    }
    return NULL;

}
int get_hnode_value_type(struct _hashnode* hn){
    if(hn){
	   return hn->vtype;
    }
    return -1;
}
int get_hnode_key_type(struct _hashnode* hn){
    if(hn){
	   return hn->ktype;
    }
    return -1;
    
}
void * get_value_for_key(struct _hash *h, void* k, int kt){
    int v;
    char *n;
    char b;
    struct _hr r;
    struct _hashnode *temp;
    if(h){
	   r = compute_hash_value(h,k,kt);
	   temp = h->bucket[r.r];
	   switch(kt){
		  case 3:
			 n = (char*)k;
			 while(temp != NULL){
				if(temp->ktype == kt){
				    if(strcmp(temp->key,n)==0)
					   	return temp->value;
				}
				temp = temp->next;
			 }
			 break;

		  case 2:
			 b = *(char*)k;
			 while(temp != NULL){
				if(temp->ktype == kt){
				    if(*(char*)temp->key == b)
				    		return temp->value;
					}
				temp = temp->next;
			 }
			 break;
		  case 0:
			 v = *(int*)k;
			 while(temp != NULL){
				if(temp->ktype == kt){
				    if(*(int*)temp->key == v)
					   	return temp->value;
					}
				temp = temp->next;
			 }
			 break;
	   }
    }
    return NULL;
}
void add_to_hash(struct _hash * h, void * v, int vt, void * k, int kt){
    struct _hr r;
    struct _hashnode *hn;
    struct _hashnode *temp;
    if(h){
	   if(get_value_for_key(h,k,kt)!=NULL)
		  return;
	   hn = create_hashnode(v,vt,k,kt);
	   r = compute_hash_value(h,k,kt);
	   if(h->bucket[r.r] == NULL){
		  h->bucket[r.r] = hn;
	   }
	   else{
		  temp = h->bucket[r.r];
		  while(temp->next != NULL)
			 temp = temp->next;
		  temp->next = hn;
	   }
	   h->used++;
//	   h->lasth = r;
    }
}
struct _hashnode *remove_from_hash(struct _hash* h,void* k, int kt){
    struct _hr r;
    struct _hashnode *hn;
    struct _hashnode *temp;
    if(h){
	   if((hn = get_value_for_key(h,k,kt))==NULL)
		  return NULL;
	   r = compute_hash_value(h,k,kt);
	   if(h->bucket[r.r] == NULL){
		  printf("error can't find in bucket\n");
		  return NULL;
	   }
	   else{
		  temp = h->bucket[r.r];
		  while(temp != hn && temp->next != hn && temp != NULL){
			 temp= temp->next;
		  }
			 if(temp == hn){
				h->bucket[r.r] = temp->next;
				h->used--;
				return hn;
			 }
			 else if(temp->next == hn){
				temp->next = hn->next;
				h->used--;
				return hn;
			 }
		  
	   }
    }
    return NULL;
}

struct _hr compute_hash_value(struct _hash * s, void * key, int kt){
    char integer[16];
    char *string;
    char a;
    int h;
    struct _hr result;
    h=0;
    size_t leng;
    if(key){
/*	   result = search_cache(s,key,kt);
	   if(result.r != -1)
		  return result;*/
	   switch(kt){
		  case 0:
			 sprintf((char*)&integer,"%d",*(int*)key);
			 leng = strlen(integer);
			 for(int r=0;r<leng;r++)
				h = (s->alpha * h) + integer[r];
			 break;
		  case 1:
			 break;
		  case 2:
			 a = *(char*)key;
			 h = s->alpha * h + a;
			 break;
		  case 3:
			 string = (char*)key;
			 printf("this is string: %s\n",string);
			 leng = strlen(key);
			 for(int r=0;r<leng;r++)
				h = (s->alpha * h) + string[r];
			 break;
		  default:
			 break;
			 
	   }
	   h = h % s->size;
/*	   if(s->cused <= s->csize){
		  	s->cache[s->cused].p = malloc(sizeof(key));
		  	memcpy(s->cache[s->cused].p,key,sizeof(key));
		  if(kt == 3)
			 	printf("this is s->cache[s->cused].p: %s\n",s->cache[s->cused].p);
		  	s->cache[s->cused].pt = kt;
		  	s->cache[s->cused].r = h;
		  	result.i = s->cused;
		  	s->cused++;
	   }*/
	   result.r = h;
	   return result;
    }
    result.r = -1;
    return result;
}

struct _hr search_cache(struct _hash * s, void * key, int kt){
    struct _hr result;
    if(s->cused <= s->csize){
    for(int b=1; b <= s->cused;b++){
	   if(s->cache[b].pt == kt){
		  	switch (kt) {
			    case 0:
				   if(*(int*)s->cache[b-1].p == *(int*)key){
					  result.i=b-1;
					  result.r=s->cache[b-1].r;
					  return result;
				   }
				   break;
			    case 1:
				   break;
			    case 2:
				   if(*(char*)s->cache[b-1].p == *(char*)key){
					  result.i=b-1;
					  result.r=s->cache[b-1].r;
					  return result;
				   }
				   break;
			    case 3:
				   if(strcmp(s->cache[b-1].p,key)==0){
					  result.i=b-1;
					  result.r=s->cache[b-1].r;
					  return result;
				   }
				   break;
			 case 4:
				   break;
			 
	   		}
	   }
    }
    }
    result.r= -1;
    return result;
}

struct _hash* combine_hashes(struct _hash* h1, struct _hash* h2){
    struct _hashnode *temp;
    if(h1 && h2){
	   	for(int e=0;e<h2->size;e++){
		    temp=h2->bucket[e];
		    while(temp != NULL){
			   add_to_hash(h1,temp->value,temp->vtype,temp->key,temp->ktype);
			   temp = temp->next;
		    }
    		}
	   return h1;
    }
    return NULL;
}

struct _hash *copy_hash(struct _hash * h){
    struct _hash *temp;
    if(h){
	   temp = create_hash(h->size);
	   combine_hashes(temp,h);
	   return temp;
    }
    return NULL;
}

void print_hnode(struct _hashnode * hn){
    if(hn){
			 switch(hn->ktype){
				case 0:
				    printf("Key Type: INT Value: %d\n",*(int*)hn->key);
				    break;
				case 2:
				    printf("Key Type: CHAR Value: %c\n",*(char*)hn->key);
				    break;
				case 3:
				    break;
			 }
			 switch(hn->vtype){
				case 0:
				    printf("Value Type: INT Value: %d\n",*(int*)hn->value);
				    break;
				case 2:
				    printf("Value Type: CHAR Value: %c\n",*(char*)hn->value);
				    break;
				case 3:
				    break;
			 }
			 printf("\n");
    }
}
void print_hash(struct _hash * h){
    struct _hashnode *temp;
    int a=0;
    if(h){
	   for(int j=0;j<h->size;j++){
		  printf("Hash Bucket: %d\n",j);
		  temp=h->bucket[j];
		  while(temp != NULL){
			 printf("Item Number %d\n",a);
			 print_hnode(temp);
			 a++;
			 temp = temp->next;
		  }
		  a=0;
	   }
    }
}
