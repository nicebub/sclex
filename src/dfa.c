#include "../include/dfa.h"



struct _DFA* generate_dfa(struct _ta *tree,struct _iseta * it, struct _cset *al){
    struct _iset *** DUTran;
    struct _iseta * Dstates;
    struct _iset * temps, *temps2;
    struct _iset * U;
    struct _DFA *dfa;
    int **Dtran;
    int * marked;
    int * unmarked;
    int a;
    int which_re, current_re;
    int sets;
    Dstates = NULL;
    temps = temps2 = NULL;
    U = NULL;
    dfa = NULL;
    Dtran = NULL;
    marked = NULL;
    unmarked = NULL;
    current_re = 0;
    which_re = 0;
    sets =0;
    Dstates = create_iseta(it->used);
    if(Dstates == NULL){
	   printf("Couldn't allocate enough memory for Dstates in dfa gen\n");
	   return NULL;
    }
    Dtran = malloc(sizeof(int*)*al->used);
    DUTran = malloc(sizeof(struct _iset**)*al->used);
    for(int we=0;we<al->used;we++){
	   Dtran[we] = malloc(sizeof(int)*it->used);
	   DUTran[we] = malloc(sizeof(struct _iset*)*it->used);
    }
    for(int i=0;i<al->used;i++){
	   for(int j=0;j<it->used;j++){
		  Dtran[i][j] = -1;
		  DUTran[i][j] = create_iset(it->used);
	   }
    }
    for(int bb=0;bb<it->used;bb++){
	   Dstates->iset[bb] = create_iset(it->used);
	   if(Dstates->iset[bb] == NULL){
		  printf("couldn't create new Dstates state\n");
		  return NULL;
	   }
    }
    marked = malloc(sizeof(int)*it->used);
    unmarked = malloc(sizeof(int)*it->used);
    for(a=0;a<it->used;a++){
	   marked[a]= -1;
	   unmarked[a] = -1;
    }
    temps = Dstates->iset[sets];
    struct _iset *fpt = firstpos(&tree->atop);
    temps2 = merge_isets(temps,fpt);
    add_iset_to_sa(temps2,Dstates);
    delete_iset(temps);
    temps = NULL;
    delete_iset(temps2);
    temps2 = NULL;
    temps = Dstates->iset[sets];
    temps->uniq = sets+1;
    unmarked[sets]=1;
    sets++;
    for(a=0;a<sets;a++){
	   if(unmarked[a] ==1)
		  break;
    }
    struct _node *tn;
    tn = NULL;
//    printf("Starting State added, it is\n");
//    display_set(Dstates->iset[0],0);
    while(a < sets){
	   unmarked[a] =0;
	   marked[a] = 1;
	   for(int j=0;j<al->used;j++){
//		  printf("creating new U set to use\n");
		  U = create_iset(it->used);
		  if(U == NULL){
			 printf("couldn't create new U\n");
			 return NULL;
		  }
		  for(int g=0;g<Dstates->iset[a]->used;g++){
			 tn = get_node_for_uniq(tree->atop,Dstates->iset[a]->s[g]);
			 if(tn->value == al->s[j]){
//				printf("alphabet symbol %c from state %d for position %d\n", \
					  al->s[j],a+1,Dstates->iset[a]->s[g]);
				temps = U;
				U = merge_isets(U,it->iset[Dstates->iset[a]->s[g]-1]);
				U->uniq = sets;
//				printf("U created: displaying ");
//				display_set(U,0);
//				printf("Adding to DUTran and displaying\n");
				add_to_iset(&DUTran[j][a],Dstates->iset[a]->s[g]);
				delete_iset(temps);
				temps = NULL;
				temps = U;
			 }
		  }
				int same = 0;
				if(U->used != 0){
//				    printf("U is not empty\n");
				    for(int z=0;z<Dstates->used;z++){
					   	if(isets_are_same(U,Dstates->iset[z])){
//						    printf("set already in Dstates\n");
						    U->uniq = Dstates->iset[z]->uniq;
						    same = 1;
						    break;
						}
						else
						    ;
				    }
				    if(same != 1){
					   struct _iset * Fstates;
					   Fstates = NULL;
//					   	printf("haven't seen this state yet\n");
					   	U->uniq = sets+1;
					   	add_iset_to_sa(U,Dstates);
					   delete_iset(U);
					   U = NULL;
					   U = Dstates->iset[Dstates->used-1];
					   	unmarked[sets] = 1;
					   	marked[sets] = 0;
				    		sets++;
				    }
				}
				else{
				    U->uniq = -1;
				}
				Dtran[j][a] = U->uniq;
	   }

	   for(a=0;a<sets;a++){
		  if(unmarked[a] ==1){
			 break;
		  }
	   }
    }
//    printf("DONE CREATING DFA STATES\n");
//    printf("THEY ARE AS FOLLOWS\n");
//    for(int j=0;j<Dstates->used;j++)
//	   display_set(Dstates->iset[j],0);
    int **tTran = malloc(sizeof(int*)*al->used);
    struct _iset ***tDUTran = malloc(sizeof(struct _iset **)*al->used);
    for(int we=0;we<al->used;we++){
	   tTran[we] = malloc(sizeof(int)*Dstates->used);
	   tDUTran[we] = malloc(sizeof(struct _iset *)*Dstates->used);
    }
    for(int i=0;i<al->used;i++){
	   for(int j=0;j<Dstates->used;j++){
		  tTran[i][j] = Dtran[i][j];
		  tDUTran[i][j] = DUTran[i][j];
		  DUTran[i][j] = NULL;
	   }
	   free(Dtran[i]);
	   free(DUTran[i]);
	   Dtran[i] = NULL;
	   DUTran[i] = NULL;
    }
    free(Dtran);
    free(DUTran);
    Dtran = NULL;
    DUTran = NULL;
//    printf("Dtran table computed\n");
    printf("Alphabet Symbol \n");
    printf("S|");
    for(int i=0;i<al->used;i++){
	   printf("|%c",al->s[i]);
    }
    printf("|\n");
    for(int r=0;r<Dstates->used;r++){
	   printf("%d|",r+1);
	   for(int i=0;i<al->used;i++){
		  if(tTran[i][r] != -1)
			 printf("|%d", tTran[i][r]);
		  else
			 printf("|x");
	   }
	   printf("|\n");

    }
/*    printf("DUTran table computed and going to print all sets\n");
    for(int r=0;r<Dstates->used;r++){
	   for(int i=0;i<al->used;i++){
		  display_set(tDUTran[i][r],0);
	   }
    }*/
//    printf("number of states %d\n", Dstates->used);
//    printf("Start State: %d\n",Dstates->iset[0]->uniq);
    dfa = create_dfa();
    if(dfa == NULL){
	   printf("couldn't create new DFA\n");
	   return NULL;
    }
    dfa->Dtran = tTran;
    struct _iset * Fstates;
    struct _iset * FFstates;
    int lastpos;
    int fcount;
    FFstates = NULL;
    FFstates = create_iset(100);
//	printf("number of regular expressions found %d\n",tree->num_re);
    for(int k=0;k<tree->num_re;k++){
	   	Fstates = NULL;
	   	lastpos = tree->finalpos[k];
//    printf("Finish States for the whole file RE: \n");
	   	fcount = 0;
//    printf("Position using for last state: %d\n",lastpos);
	   	for(int y=0;y<Dstates->used;y++){
		    if(is_in_iset(Dstates->iset[y],lastpos)==0){
//		  	  printf("State %d is in finish states\n",y+1);
			   fcount++;
		    }
    		}
	   	Fstates = create_iset(fcount);
	   	if(Fstates == NULL){
		    printf("couldn't create new Fstates\n");
		    return NULL;
    		}
	   	for(int y=0;y<Dstates->used;y++){
		    if(is_in_iset(Dstates->iset[y],lastpos)==0){
//		  printf("Adding State %d to finish states\n",y+1);
			   add_to_iset(&Fstates,y+1);
			   add_to_iset(&FFstates,y+1);
		    }
    		}
	   tree->Fstates[k] = Fstates;
    }
  //  printf("final finish state set for the whole file RE\n");
//    display_set(FFstates,0);

    dfa->FFstates = FFstates;
    dfa->Fstates = tree->Fstates;
    dfa->start = Dstates->iset[0]->uniq;
    dfa->num_states = Dstates->used;
    dfa->Dstates = Dstates;
    dfa->alphabet = copy_cset(al);
    dfa->DUTran = tDUTran;
    dfa->action_array = tree->action_array;
    dfa->num_re = tree->num_re;
    return dfa;
}


struct _DFA* create_dfa(void){
    struct _DFA * dfa;
    dfa = NULL;
    dfa = malloc(sizeof(*dfa));
    dfa->Dtran = NULL;
    dfa->DUTran = NULL;
    dfa->alphabet = NULL;
    dfa->FFstates = NULL;
    dfa->Fstates = NULL;
    dfa->Dstates = NULL;
    dfa->action_array= NULL;
    dfa->num_states = 0;
    dfa->start =0;
	dfa->num_re = -1;
    return dfa;
}
void delete_dfa(struct _DFA* dfa){
    if(dfa){
	   free(dfa->Dtran);
	   dfa->Dtran = NULL;
	   for(int b=0;b<dfa->alphabet->used;b++){
		  for(int a=0;a<dfa->num_states;a++){
			 delete_iset(dfa->DUTran[b][a]);
			 dfa->DUTran[b][a] = NULL;
		  }
		  free(dfa->DUTran[b]);
		  dfa->DUTran[b] = NULL;
	   }
	   free(dfa->DUTran);
	   dfa->DUTran = NULL;
	   delete_iset(dfa->FFstates);
	   dfa->FFstates = NULL;
	   dfa->Fstates = NULL;
	   dfa->action_array= NULL;
	   delete_cset(dfa->alphabet);
	   dfa->alphabet = NULL;
	   delete_iseta(dfa->Dstates);
	   dfa->Dstates = NULL;
	   free(dfa);
	   dfa = NULL;
    }
}
