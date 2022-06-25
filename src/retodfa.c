#include "../include/retodfa.h"
#include "baseset.h"
#include "intset.h"
#include "log.h"

int nullable(struct _node ** n){
    if(*n){
	   if((*n)->nullable != -1)
		  return (*n)->nullable;
	   if((*n)->left == NULL && (*n)->right == NULL){
		  if((*n)->value == (char) EPSILON){
			 (*n)->nullable = 0;
			 return 0;
		  }
		  else{
			 (*n)->nullable = 1;
			 return 1;
		  }
	   }
	   switch((*n)->value){
		  case (char)COMMA:
			 if((*n)->left->value == '0'){
				(*n)->nullable = 0;
				return 0;
			 }
			 (*n)->nullable = 1;
			 return 1;
		  case (char)REPS:
			 if(nullable(&(*n)->right)==0){
				(*n)->nullable = 0;
				return 0;
			 }
			 (*n)->nullable = 1;
			 return 1;
		  case (char)CHARSET:
			 (*n)->nullable = 1;
			 return 1;
		  case (char)STAR:
			 (*n)->nullable = 0;
				    return 0;
		  case (char)CONCAT:
			 if(nullable(&(*n)->left)==0 && nullable(&(*n)->right)==0){
					(*n)->nullable = 0;
					return 0;
			 }
			 else{
					(*n)->nullable = 1;
					return 1;
			 }
		  case (char)MINUS:
			 (*n)->nullable = 1;
			 return 1;
		  case (char)OR:
			 if(nullable(&(*n)->left)==0 || nullable(&(*n)->right)==0){
				(*n)->nullable = 0;
				return 0;
			 }
			 else{
				(*n)->nullable = 1;
				return 1;
			 }
		  case (char)PLUS:
			 (*n)->nullable = nullable(&(*n)->left);
			 return (*n)->nullable;
		  case (char)QUEST:
			 (*n)->nullable = 0;
			 return 0;
	   }
    }
    LOG_ERROR("nullable error%s","\n");
    return -1;
}
/* int_set* */base_set* pos(struct _node ** n, int ff){
    base_set* h1; /* int_set* */
    base_set*h2; /* int_set* */
    base_set*h3; /* int_set* */
    base_set*h4; /* int_set* */
    char c,d;
    h1 = h2 = h3 = h4 = NULL;
    if(*n){
	   switch((*n)->value){
/*		  case '\n':
			 	print_set(pos(n->left,ff));
			 	print_set(pos(n->right,ff));
			 	break;
*/
		  case (char)CONCAT:
			 if(ff == 1){
			 	if(nullable(&(*n)->left)==0){
				    if(((*n)->ifirst)==NULL){
					   	h1 = pos(&(*n)->left,ff);
/*					   printf("firstpos id h1 solo: %d\n",h1->id);*/
					   	h2 = pos(&(*n)->right,ff);
/*					   printf("firstpos id h2 solo : %d\n",h2->id);*/
/*					   printf("firstpos id h3 copied from h1: %d\n",h3->id);*/
					   	(*n)->ifirst = merge_sets(h1,h2);
/*					   printf("firstpos id h4 merged from h3 and h2: %d\n",h4->id);*/
/*					   printf("deleting firstpost id h3: %d\n",h3->id);*/
/*					   printf("firstpos id n->ifirst copied from h4: %d\n",n->ifirst->id);*/
/*					   printf("deleting firstpost id h4: %d\n",h4->id);*/
/*					   	printf("firstpos of %c\n",gcfprint((*n)->value));*/
/*					   	display_set((*n)->ifirst,0);*/
				    }
				    return (*n)->ifirst;
				}
				else{
				    if(((*n)->ifirst)==NULL){
					   h1 = pos(&(*n)->left,ff);
/*					   printf("firstpos id h1 solo: %d\n",h1->id);*/
					   (*n)->ifirst = copy_sets(h1);
/*					   printf("firstpos id n->ifirst copied from h1: %d\n",n->ifirst->id);*/
/*					   printf("firstpos of %c\n",gcfprint((*n)->value));*/
/*					   display_set((*n)->ifirst,0);*/
				    }
				    return (*n)->ifirst;
				}
			 }
			 else{
				if(nullable(&(*n)->right)==0){
				    if(((*n)->ilast)==NULL){
					   	h1 = pos(&(*n)->left,ff);
/*					   printf("lastpos id h1 solo: %d\n",h1->id);*/
					   	h2 = pos(&(*n)->right,ff);
/*					   printf("lastpos id h2 solo: %d\n",h2->id);*/
/*					   printf("lastpos id h3 copied from h1: %d\n",h3->id);*/
					   	(*n)->ilast = merge_sets(h1,h2);
/*					   printf("lastpos id h4 merged from h3 and h2: %d\n",h4->id);*/
/*					   printf("deleting lastpos id h3: %d\n",h3->id);*/
/*					   printf("lastpos of %c\n",gcfprint((*n)->value));*/
/*					   display_set((*n)->ilast,0);*/
					   
/*					   printf("lastpos id n->ilast copied from h4: %d\n",n->ilast->id);*/
/*					   printf("deleting lastpos id h4: %d\n",h4->id);*/
				    }
				    return (*n)->ilast;
				}
				else{
				    if(((*n)->ilast)==NULL){
					   h1 = pos(&(*n)->right,ff);
/*					   printf("lastpos id h1 solo: %d\n",h1->id);*/
					   (*n)->ilast = copy_sets(h1);
/*					   printf("lastpos id n->ilast copied from h1: %d\n",n->ilast->id);*/
/*					   printf("lastpos of %c\n",gcfprint((*n)->value));*/
/*					   display_set((*n)->ilast,0);*/
				    }
				    
				    return (*n)->ilast;
				}

			 }
		  case (char)OR:
			 if(ff == 1){
				if(((*n)->ifirst)==NULL){
				    h1 = pos(&(*n)->left,ff);
/*				    printf("firstpos id h1 solo: %d\n",h1->id);*/
				    h2 = pos(&(*n)->right,ff);
/*				    printf("firstpos id h2 solo: %d\n",h2->id);*/
/*				    printf("firstpos id h3 copied from h1: %d\n",h3->id);*/
				    (*n)->ifirst = merge_sets(h1,h2);
/*				    printf("firstpos id h4 merged from h3 and h2: %d\n",h4->id);*/
/*				    printf("deleting firstpost id h3: %d\n",h3->id);*/
/*				    printf("firstpos id n->ifirst copied from h4: %d\n",n->ifirst->id);*/
/*				    printf("deleting firstpost id h4: %d\n",h4->id);*/
/*				    printf("firstpos of %c\n",gcfprint((*n)->value));*/
/*				    display_set((*n)->ifirst,0);*/
/*				    return n->ifirst;*/
				}
				return (*n)->ifirst;
			 }
			 else{
				if(((*n)->ilast)==NULL){
				    h1 = pos(&(*n)->left,ff);
/*				    printf("lastpos id h1 solo: %d\n",h1->id);*/
				    h2 = pos(&(*n)->right,ff);
/*				    printf("lastpos id h2 solo: %d\n",h2->id);*/
/*				    printf("lastpos id h3 copied from h1: %d\n",h3->id);*/
				    (*n)->ilast = merge_sets(h1,h2);
/*				    printf("lastpos id h4 merged from h3 and h2: %d\n",h4->id);*/
/*				    printf("deleting lastpos id h3: %d\n",h3->id);*/
/*				    printf("lastpos id n->ilast copied from h4: %d\n",n->ilast->id);*/
/*				    printf("lastpos of %c\n",gcfprint((*n)->value));*/
/*				    display_set((*n)->ilast,0);*/
/*				    printf("deleting lastpos id h4: %d\n",h4->id);*/
/*				    return n->ilast;*/
				}
				return (*n)->ilast;
			 }
		  case (char)STAR:
		  case (char)PLUS:
		  case (char)QUEST:
		  case (char)CHARSET:
		  case (char)REPS:
			 if(ff == 1){
				if(((*n)->ifirst)==NULL){
				    h1 = pos(&(*n)->left,ff);
/*				    printf("firstpos id h1 solo: %d\n",h1->id);*/
				    (*n)->ifirst = copy_sets(h1);
/*				    printf("firstpos id n->ifirst copied from h1: %d\n",n->ifirst->id);*/
/*				    printf("firstpos of %c\n",gcfprint((*n)->value));*/
/*				    display_set((*n)->ifirst,0);*/
				}
				return (*n)->ifirst;
			 }
			 else{
				if(((*n)->ilast)==NULL){
				    h1 = pos(&(*n)->left,ff);
/*				    printf("lastpos id h1 solo: %d\n",h1->id);*/
				    (*n)->ilast = copy_sets(pos(&(*n)->left,ff));
/*				    printf("lastpos id n->ilast copied from h1: %d\n",n->ilast->id);*/
/*				    printf("lastpos of %c\n",gcfprint((*n)->value));*/
/*				    display_set((*n)->ilast,0);*/
				}
				return (*n)->ilast;
			 }

		  case (char)MINUS:
			 if(((*n)->ifirst)==NULL){
				(*n)->ifirst = new_int_set(SETSIZE);
				if((*n)->ifirst == NULL){
				    LOG_ERROR("couldn't create new iset in %s","MINUS\n");
				    return NULL;
				}
/*				printf("firstpos id h1 solo: %d\n",h1->id);*/
				c = (*n)->left->value;
				d = (*n)->right->value;
				if(c > d) return NULL;
				add_to_set(&(*n)->ifirst,(*n)->id);
/*				printf("firstpos id n->ifirst copied from h1: %d\n",n->ifirst->id);*/
				(*n)->ilast = copy_sets((*n)->ifirst);
/*				printf("lastpos id n->ilast copied from h1: %d\n",n->ilast->id);*/
/*				printf("firstpos of %c\n",gcfprint((*n)->value));*/
/*				display_set((*n)->ifirst,0);*/
/*				printf("lastpos of %c\n",gcfprint((*n)->value));*/
/*				display_set((*n)->ilast,0);*/
			 }
			 return (*n)->ifirst;
	   }
	   if(isalphanum((*n)->value) || isprintable((*n)->value) || isescape((*n)->value)){
		  if((*n)->ifirst == NULL){
			 	(*n)->ifirst = new_int_set(SETSIZE);
			 if((*n)->ifirst == NULL){
				LOG_ERROR("couldn't create new set in %s","ALPHANUM/PRINTABLE\n");
				return NULL;
			 }
/*			 printf("firstpos id h1 solo:: %d\n",h1->id);*/
			 	add_to_set(&(*n)->ifirst,(*n)->uniq);
/*			 printf("firstpos id n->ifirst copied from h1: %d\n",n->ifirst->id);*/
			 	(*n)->ilast = copy_sets((*n)->ifirst);
/*			 printf("lastpos id n->ilast copied from h1: %d\n",n->ilast->id);*/
/*			 	printf("firstpos of %c\n",(*n)->value);*/
/*			 	display_set((*n)->ifirst,0);*/
/*			 	printf("lastpos of %c\n",(*n)->value);*/
/*			 	display_set((*n)->ifirst,0);*/

		  }
		  return (*n)->ifirst;
	   }

    }
	   
    return NULL;
}

/* int_set* */base_set* followpos(/*int*/base_vector** ta,struct _node ** n){
    base_set*temp, *temp2; /* int_set* */
    base_set*left; /* int_set* */
    base_set*right; /* int_set* */
    temp = temp2 = left = right = NULL;
    if(*n){
	   if((*n)->ifollow)
		  return (*n)->ifollow;
/*	   printf("taking followpos of %c\n",gcfprint(n->value));*/
	   left = followpos(ta,&(*n)->left);
	   right = followpos(ta,&(*n)->right);
	   switch((*n)->value){
		  case (char)REPS:
			 	if((*n)->right->left->value >= '1')
				    break;
		  case (char)STAR:
		  case (char)PLUS:
		  {
			  int u;
			 for(u=0;u<set_used((*n)->ilast);u++){
				temp = *(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->ilast,u)-1));
/*				printf("followpos id temp solo: %d\n",temp->id);*/
				*(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->ilast,u)-1)) = merge_sets(temp,(*n)->ifirst);
/*				printf("followpos id temp2 merged from temp and nodes firstpos set: %d\n",temp2->id);*/
/*				printf("followpos id ta->iset[n->ilast->s[u]-1] copied from temp2: %d\n",ta->iset[n->ilast->s[u]-1]->id);*/
/*				printf("Deleting followpos temp with id: %d\n", temp->id);*/
				delete_set(temp);
				temp = NULL;
/*				printf("Deleting followpos temp2 with id: %d\n", temp2->id);*/
				temp = *(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->ilast,u)-1));
/*				display_set(temp,0);*/
/*				printf("followpos id n->ifollow copied from temp: %d\n",n->ifollow->id);*/
/*			    printf("current followpos of %c for what node is ", gcfprint(n->value));*/
/*				printf("%d\n",n->ilast->s[u]);*/
			 }
/*			 display_set(n->ifollow,0);*/
		 }
			 break;
			 
		  case (char)CONCAT:
		  {
		  int u;
		 for(u=0;u<set_used((*n)->left->ilast);u++){
			temp = *(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->left->ilast,u)-1));
/*			printf("followpos id temp solo: %d\n",temp->id);*/
			*(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->left->ilast,u)-1)) = merge_sets(temp,(*n)->right->ifirst);
/*			printf("followpos id temp2 merged from temp and nodes right child  firstpos set: %d\n",temp2->id);*/
/*			printf("followpos id ta->iset[n->left->ilast->s[u]-1] copied from temp2: %d\n",ta->iset[n->left->ilast->s[u]-1]->id);*/
/*			printf("Deleting followpos temp with id: %d\n", temp->id);*/
			delete_set(temp);
			temp = NULL;
/*			printf("Deleting followpos temp2 with id: %d\n", temp2->id);*/
			temp = *(get_by_index_in_vector((*ta), *(int*)get_value_by_index_set((*n)->left->ilast,u)-1));
/*			printf("followpos id n->ifollow copied from temp: %d\n",n->ifollow->id);*/
/*				    printf("current followpos of %c for what node is ", gcfprint(n->value));*/
/*					printf("%d\n",n->left->ilast->s[u]);*/
/*			display_set(temp,0);*/
		 }
	 }
			 break;
		  case (char) MINUS:
			 ;
	/*		 printf("MINUS FOLLOWPOS\n");*/
	   }
    }
    return NULL;
}

/*
void print_set(struct _hash * h){
    struct _hashnode *temp;
    int a=0;
    if(h){
	   printf("{");
	   for(int j=0;j<h->size;j++){
		  temp=h->bucket[j];
		  while(temp != NULL){
			 print_hset(temp);
			 printf(",");
			 a++;
			 temp = temp->next;
		  }
		  a=0;
	   }
	   printf("}\n");
    }
}

void print_hset(struct _hashnode * hn){
    if(hn){
	   switch(hn->vtype){
		  case 0:
			 printf("%d",*(int*)hn->value);
			 break;
		  case 2:
			 printf("%c",*(char*)hn->value);
			 break;
		  case 3:
			 break;
	   }
    }
}
*/
char gcfprint(char c){
    char rq;
    switch(c){
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
		  rq = '.';
		  break;
	   case (char)PLUS:
		  rq = '+';
		  break;
	   case (char)MINUS:
		  rq = '-';
		  break;
	   case (char)QUEST:
		  rq = '?';
		  break;
	   case (char)COMMA:
		  rq = ',';
		  break;
	   case (char)CHARSET:
		  rq = 'C';
		  break;
	   case (char)REPS:
		  rq = 'R';
		  break;
	   default:
		  rq = c;
    }
    return rq;
}
