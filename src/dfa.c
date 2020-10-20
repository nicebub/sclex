#include "../include/dfa.h"
#include "basevector.h"
#include "chrvector.h"
#include "intvector.h"
#include "baseset.h"
#include "intset.h"
#include "chrset.h"
#include <stdlib.h>


struct _DFA* generate_dfa(Io* programIO){
    base_set*** DUTran; /* int_set*** */
    base_vector * Dstates; /* int_vector* */
    base_set* temps, *temps2; /* int_set* */
    base_set* U; /* int_set* */
    struct _DFA *dfa;
    int **Dtran;
    int * marked;
    int * unmarked;
    int a;
    int which_re, current_re;
    int sets;
    base_set*fpt; /* int_set* */
    struct _node *tn;
    int **tTran;
    base_set***tDUTran; /* int_set*** */
    base_set* Fstates; /* int_set* */
    base_set* FFstates; /* int_set* */
    int lastpos;
    int fcount;
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
    Dstates = new_int_vector(vector_used(programIO->lexfile.fpos));
    if(Dstates == NULL){
	   printf("Couldn't allocate enough memory for Dstates in dfa gen\n");
	   return NULL;
    }
    Dtran = malloc(sizeof(int*)*set_used(programIO->lexfile.tree));
    if(!Dtran){
	   printf("Couldnt' allocate memory for Dtran in dfa gen\n");
	   delete_vector(Dstates);
	   Dstates = NULL;
	   return NULL;
    }
    DUTran = malloc(sizeof(int_set**)*set_used(programIO->lexfile.tree));
	if(!DUTran){
	    printf("Couldnt' allocate memory for DUTran in dfa gen\n");
	    delete_vector(Dstates);
	    Dstates = NULL;
	    free(Dtran);
	    Dtran = NULL;
	    return NULL;
	}
	{
		int we;
		for(we=0;we<set_used(programIO->lexfile.tree);we++){
	   	Dtran[we] = malloc(sizeof(int)*vector_used(programIO->lexfile.fpos));
		   DUTran[we] = malloc(sizeof(int_set*)*vector_used(programIO->lexfile.fpos));
    	}
	}
{
	int i;
    for(i=0;i<set_used(programIO->lexfile.tree);i++){
		int j;
	   for(j=0;j<vector_used(programIO->lexfile.fpos);j++){
		  Dtran[i][j] = -1;
		  DUTran[i][j] = new_int_set(vector_used(programIO->lexfile.fpos));
	   }
    }
}
{
	int bb;
    for(bb=0;bb<vector_used(programIO->lexfile.fpos);bb++){
	   set_by_index_in_vector(Dstates,bb,new_int_set(vector_used(programIO->lexfile.fpos)));
	   if(*(int**)get_by_index_in_vector(Dstates,bb) == NULL){
		  printf("couldn't create new Dstates state\n");
		  return NULL;
	   }
    }
}
    set_vector_used(Dstates,0);
    marked = malloc(sizeof(int)*vector_used(programIO->lexfile.fpos));
    unmarked = malloc(sizeof(int)*vector_used(programIO->lexfile.fpos));
    for(a=0;a<vector_used(programIO->lexfile.fpos);a++){
	   marked[a]= -1;
	   unmarked[a] = -1;
    }
    temps = *get_by_index_in_vector(Dstates,sets);
	fpt = firstpos(&tree->atop);
    temps2 = merge_sets(temps,fpt);
    delete_set(temps);
/*    set_by_index_in_vector(Dstates,sets,temps2);*/
    add_to_vector(temps2,Dstates);
    temps = NULL;
    delete_set(temps2);
    temps2 = NULL;
    temps = *get_by_index_in_vector(Dstates,sets);
    ((int_set*)temps)->super.uniq = sets+1;
    unmarked[sets]=1;
    sets++;
    for(a=0;a<sets;a++){
	   if(unmarked[a] ==1)
		  break;
    }
    tn = NULL;
/*    printf("Starting State added, firstpos is\n");*/
/*    display_set(Dstates->iset[0],0);*/
    while(a < sets){
		int same;
 	   int j;
	   unmarked[a] =0;
	   marked[a] = 1;
	   for(j=0;j<set_used(alphabet);j++){
/*		  printf("creating new U set to use\n");*/
		  U = new_int_set(vector_used(firstpos));
		  if(U == NULL){
			 printf("couldn't create new U\n");
			 return NULL;
		  }
		  {
		  int g;
		  for(g=0;
		  	g<set_used(*get_by_index_in_vector(Dstates,a));
		  	g++){
			 tn = get_node_for_uniq(tree->atop,
			 	*(int*)get_value_by_index_set(*get_by_index_in_vector(Dstates,a),g));
			 if(tn->value == *(char*)get_value_by_index_set(alphabet,j)){
/*				printf("alphabet symbol %c from state %d for position %d\n", \
					  alphabet->s[j],a+1,Dstates->iset[a]->s[g]);*/
				temps = U;
				U = merge_sets(U,
					*get_by_index_in_vector(firstpos,	*(int*)get_value_by_index_set(*get_by_index_in_vector(Dstates,a),g)-1));
				((int_set*)U)->super.uniq = sets;
/*				printf("U created: displaying ");*/
/*				display_set(U,0);*/
/*				printf("Adding to DUTran and displaying\n");*/
				add_to_set(&DUTran[j][a],
					*(int*)get_value_by_index_set(*get_by_index_in_vector(Dstates,a),g));
				delete_set(temps);
				temps = NULL;
				temps = U;
			 }
		  }
	  }
				same  = 0;
				if(set_used(U) != 0){
/*				    printf("U is not empty\n");*/
					int z;
				    for(z=0;z<vector_used(Dstates);z++){
					   	if(sets_are_same(U,*get_by_index_in_vector(Dstates,z))){
/*						    printf("set already in Dstates\n");*/
						    ((int_set*)U)->super.uniq = (*(int_set**)get_by_index_in_vector(Dstates,z))->super.uniq;
						    same = 1;
						    break;
						}
						else
						    ;
				    }
				    if(same != 1){
					   int_set* Fstates;
					   Fstates = NULL;
/*					   	printf("haven't seen this state yet\n");*/
					   	((int_set*)U)->super.uniq = sets+1;
					   	add_to_vector(U,Dstates);
					   delete_set(U);
					   U = NULL;
					   U = *get_by_index_in_vector(Dstates,vector_used(Dstates)-1);
					   	unmarked[sets] = 1;
					   	marked[sets] = 0;
				    		sets++;
				    }
				}
				else{
				    ((int_set*)U)->super.uniq = -1;
				}
				Dtran[j][a] = ((int_set*)U)->super.uniq;
	   }

	   for(a=0;a<sets;a++){
		  if(unmarked[a] ==1){
			 break;
		  }
	   }
    }
/*    printf("DONE CREATING DFA STATES\n");*/
/*    printf("THEY ARE AS FOLLOWS\n");*/
/*    for(int j=0;j<vector_used(Dstates);j++)*/
/*	   display_set(Dstates->iset[j],0);*/
	tTran = malloc(sizeof(int*)*set_used(alphabet));
	tDUTran= malloc(sizeof(int_set**)*set_used(alphabet));
	{
	int we;
    	for(we=0;we<set_used(alphabet);we++){
			tTran[we] = malloc(sizeof(int)*vector_used(Dstates));
	   		tDUTran[we] = malloc(sizeof(int_set*)*vector_used(Dstates));
		}
}
{
	int i;
    for(i=0;i<set_used(alphabet);i++){
		int j;
	   for(j=0;j<vector_used(Dstates);j++){
		  tTran[i][j] = Dtran[i][j];
		  tDUTran[i][j] = DUTran[i][j];
		  DUTran[i][j] = NULL;
	   }
	   free(Dtran[i]);
	   free(DUTran[i]);
	   Dtran[i] = NULL;
	   DUTran[i] = NULL;
    }
}
    free(Dtran);
    free(DUTran);
    Dtran = NULL;
    DUTran = NULL;
/*    printf("Dtran table computed\n");*/
    printf("Alphabet Symbol \n");
    printf("S|");
	{
		int i;
		for(i=0;i<set_used(alphabet);i++){
		   printf("|%c",*(char*)get_value_by_index_set(alphabet,i));
		}
	}
    printf("|\n");
	{
		{
		int r;
		for(r=0;r<vector_used(Dstates);r++){
			int i;
			printf("%d|",r+1);
	   	 	for(i=0;i<set_used(alphabet);i++){
		 	   if(tTran[i][r] != -1)
				   printf("|%d", tTran[i][r]);
			   else
				   printf("|x");
		   }
		   printf("|\n");
 	   }
   }
}
/*    printf("DUTran table computed and going to print all sets\n");
    for(int r=0;r<vector_used(Dstates);r++){
	   for(int i=0;i<set_used(alphabet);i++){
		  display_set(tDUTran[i][r],0);
	   }
    }*/
/*    printf("number of states %d\n", vector_used(Dstates));*/
/*    printf("Start State: %d\n",Dstates->iset[0]->uniq);*/
    dfa = create_dfa();
    if(dfa == NULL){
	   printf("couldn't create new DFA\n");
	   return NULL;
    }
    dfa->Dtran = tTran;
    FFstates = NULL;
    FFstates = new_int_set(100);
/*	printf("number of regular expressions found %d\n",tree->num_re);*/
	{
	int k;
    for(k=0;k<tree->num_re;k++){
		int y;
	   	Fstates = NULL;
	   	lastpos = tree->finalpos[k];
/*    printf("Finish States for the whole file RE: \n");*/
	   	fcount = 0;
/*    printf("Position using for last state: %d\n",lastpos);*/
	   	for(y=0;y<vector_used(Dstates);y++){
		    if(is_in_set(*get_by_index_in_vector(Dstates,y),lastpos)==0){
/*		  	  printf("State %d is in finish states\n",y+1);*/
			   fcount++;
		    }
    		}
	   	Fstates = new_int_set(fcount);
	   	if(Fstates == NULL){
		    printf("couldn't create new Fstates\n");
		    return NULL;
    		}
			{
				int y;
	   			for(y=0;y<vector_used(Dstates);y++){
		    		if(is_in_set(*get_by_index_in_vector(Dstates,y),lastpos)==0){
/*		  printf("Adding State %d to finish states\n",y+1);*/
						add_to_set(&Fstates,y+1);
						add_to_set(&FFstates,y+1);
		   		 	}
				}
			}
	   tree->Fstates[k] = Fstates;
    }
}
  /*  printf("final finish state set for the whole file RE\n");*/
/*    display_set(FFstates,0);*/

    dfa->FFstates = FFstates;
    dfa->Fstates = tree->Fstates;
    dfa->start = (*(int_set**)get_by_index_in_vector(Dstates,0))->super.uniq;
    dfa->num_states = vector_used(Dstates);
    dfa->Dstates = Dstates;
    dfa->alphabet = copy_sets(alphabet);
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
 	   int b;
	   free(dfa->Dtran);
	   dfa->Dtran = NULL;
	   for(b=0;b<set_used(dfa->alphabet);b++){
		   int a;
		  for(a=0;a<dfa->num_states;a++){
			 delete_set(dfa->DUTran[b][a]);
			 dfa->DUTran[b][a] = NULL;
		  }
		  free(dfa->DUTran[b]);
		  dfa->DUTran[b] = NULL;
	   }
	   free(dfa->DUTran);
	   dfa->DUTran = NULL;
	   delete_set(dfa->FFstates);
	   dfa->FFstates = NULL;
	   dfa->Fstates = NULL;
	   dfa->action_array= NULL;
	   delete_set(dfa->alphabet);
	   dfa->alphabet = NULL;
	   delete_vector(dfa->Dstates);
	   dfa->Dstates = NULL;
	   free(dfa);
	   dfa = NULL;
    }
}
