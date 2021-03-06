#include "../include/dfa.h"
#include "basevector.h"
#include "chrvector.h"
#include "intvector.h"
#include "baseset.h"
#include "intset.h"
#include "chrset.h"
#include <stdlib.h>

#define checkForUnmarked()     for(counter=0;counter<sets;counter++) \
	   if(tCalcs.unmarked[counter] ==1) \
		  break; 

#define INITIALSTATE 0
#define ZERO 0
#define TABLEERROR -1

void* initDFATransitionTables(Parser* parser, TableCalculations* tCalcs){
	int row,col;
	int numFirstPositionSets;
	int alphabetSize;
	
	numFirstPositionSets = vector_used(parser->fpos);
	alphabetSize = set_used(parser->parseTree->alphabet);

   tCalcs->Dstates = new_int_vector(numFirstPositionSets);
   if(!tCalcs->Dstates){
		printf("Couldn't allocate enough memory for Dstates in dfa gen\n");
		return NULL;
   }

   tCalcs->Dtransition = malloc(sizeof(int*)*alphabetSize);
   if(!tCalcs->Dtransition){
		printf("Couldnt' allocate memory for Dtransition in dfa gen\n");
		delete_vector(tCalcs->Dstates);
		tCalcs->Dstates = NULL;
		return NULL;
   }

   tCalcs->DUtransition = malloc(sizeof(int_set**)*alphabetSize);
	if(!tCalcs->DUtransition){
   	printf("Couldnt' allocate memory for DUtransition in dfa gen\n");
    	delete_vector(tCalcs->Dstates);
   	tCalcs->Dstates = NULL;
  	 	free(tCalcs->Dtransition);
   	tCalcs->Dtransition = NULL;
   	return NULL;
	}
	for(row=ZERO;row<alphabetSize;row++){
   	tCalcs->Dtransition[row] = malloc(sizeof(int) * numFirstPositionSets);
	   tCalcs->DUtransition[row] = malloc(sizeof(int_set*) * numFirstPositionSets);
 	}
	for(row=ZERO;row<alphabetSize;row++)
   	for(col=ZERO;col<numFirstPositionSets;col++){
	  	 	tCalcs->Dtransition[row][col] = TABLEERROR;
	  		tCalcs->DUtransition[row][col] = new_int_set(numFirstPositionSets);
   	}

   for(row=ZERO;row<numFirstPositionSets;row++){
   	set_by_index_in_vector(tCalcs->Dstates,row,new_int_set(numFirstPositionSets));
   	if(*(int**)get_by_index_in_vector(tCalcs->Dstates,row) == NULL){
			printf("couldn't create new Dstates state\n");
			return NULL;
		}
	}
   set_vector_used(tCalcs->Dstates,INITIALSTATE);
   tCalcs->marked = malloc(sizeof(int)*numFirstPositionSets);
   tCalcs->unmarked = malloc(sizeof(int)*numFirstPositionSets);
   for(row=ZERO;row<numFirstPositionSets;row++){
		tCalcs->marked[row]= TABLEERROR;
		tCalcs->unmarked[row] = TABLEERROR;
   }
    return (void*)1;
}

void* processUnmarkedState(Parser* parser, int* counter,int* sets,TableCalculations* tCalcs,base_set** U){
	base_set* temps;
	struct _node *tempNode;
		int same;
 	   int currentLetter;
		int currentState;
		int alphabetSize;
		/* mark the state */
		 alphabetSize = set_used(parser->parseTree->alphabet);
	   tCalcs->unmarked[*counter] =0;
	   tCalcs->marked[*counter] = 1;
      tempNode = NULL;
	   for(currentLetter=0;currentLetter<alphabetSize;currentLetter++){
			int stateSetSize;
			int stateNode;
			base_set* stateSet;
/*		  printf("creating new U set to use\n");*/
		  *U = new_int_set(vector_used(parser->fpos));
		  if(*U == NULL){
			 printf("couldn't create new U\n");
			 return NULL;
		  }
		  stateSet = *get_by_index_in_vector(tCalcs->Dstates,*counter);
		  stateSetSize = set_used(stateSet);
		  for(currentState=0;currentState<stateSetSize;currentState++){
			  stateNode = *(int*)get_value_by_index_set(stateSet,currentState);
			  tempNode = get_node_for_uniq(parser->parseTree->atop,stateNode);
			  /*check to see if this state has any transition for this alphabet letter*/
			 if(tempNode->value == *(char*)get_value_by_index_set(parser->parseTree->alphabet,currentLetter)){
/*				printf("alphabet symbol %c from state %d for position %d\n", \
					  alphabet->s[j],a+1,Dstates->iset[a]->s[g]);*/
				temps = *U;
				*U = merge_sets( *U, *get_by_index_in_vector(parser->fpos,stateNode - 1));
				((int_set*)*U)->super.uniq = *sets;
/*				printf("U created: displaying ");*/
/*				display_set(U,0);*/
/*				printf("Adding to DUtransition and displaying\n");*/
				add_to_set(&tCalcs->DUtransition[currentLetter][*counter],stateNode);
				delete_set(temps);
				temps = NULL;
				temps = *U;
			 }
		  }
	  		
			same  = 0;
			if(set_used(*U) != 0){
/*				    printf("U is not empty\n");*/
				int z;
				    for(z=0;z<vector_used(tCalcs->Dstates);z++){
					   	if(sets_are_same(*U,*get_by_index_in_vector(tCalcs->Dstates,z))){
/*						    printf("set already in Dstates\n");*/
						    ((int_set*)*U)->super.uniq = (*(int_set**)get_by_index_in_vector(tCalcs->Dstates,z))->super.uniq;
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
					   	((int_set*)*U)->super.uniq = *sets+1;
					   	add_to_vector(*U,tCalcs->Dstates);
					   delete_set(*U);
					   *U = NULL;
					   *U = *get_by_index_in_vector(tCalcs->Dstates,vector_used(tCalcs->Dstates)-1);
					   	tCalcs->unmarked[*sets] = 1;
					   	tCalcs->marked[*sets] = 0;
				    		sets++;
				    }
			}
			else{
				    ((int_set*)*U)->super.uniq = -1;
			}
			tCalcs->Dtransition[currentLetter][*counter] = ((int_set*)*U)->super.uniq;
	   }


/*	   for(counter=0;counter<sets;counter++)
			if(unmarked[counter] ==1)
				break;
				*/
    return NULL;
}

struct _DFA* generate_dfa(Parser* parser){
    base_set*** DUtransition; /* int_set*** */
    base_vector * Dstates; /* int_vector* */
    base_set* temps, *temps2; /* int_set* */
    base_set* U; /* int_set* */
    struct _DFA *dfa;
    int **Dtransition;
    int * marked;
    int * unmarked;
    int a;
    int which_re, current_re;
    int sets;
    base_set*fpt; /* int_set* */
    int **tTran;
    base_set***tDUtransition; /* int_set*** */
    base_set* Fstates; /* int_set* */
    base_set* FFstates; /* int_set* */
    int lastpos;
    int fcount;
	 int counter;
	 int row,col;
	 int* status;
	 int alphabetSize;
	 TableCalculations tCalcs;
    Dstates = NULL;
    temps = temps2 = NULL;
    U = NULL;
    dfa = NULL;
    Dtransition = NULL;
    marked = NULL;
    unmarked = NULL;
    current_re = 0;
    which_re = 0;
    sets =0;
	 status = NULL;
	 alphabetSize = set_used(parser->parseTree->alphabet);
	 
	 if(!(status = initDFATransitionTables(parser,&tCalcs)))
	 	return status;

    temps = *get_by_index_in_vector(tCalcs.Dstates,INITIALSTATE);
	fpt = firstpos(&(parser->parseTree->atop));
    temps2 = merge_sets(temps,fpt);
    delete_set(temps);
    temps = NULL;
/*    set_by_index_in_vector(Dstates,sets,temps2);*/
    add_to_vector(temps2,tCalcs.Dstates);
    delete_set(temps2);
    temps2 = NULL;

    temps = *get_by_index_in_vector(tCalcs.Dstates,INITIALSTATE);
    ((int_set*)temps)->super.uniq = sets+1;
    tCalcs.unmarked[sets]=1;
    sets++;
	 checkForUnmarked();
/*    for(counter=0;counter<sets;counter++)
	   if(unmarked[counter] ==1)
		  break;*/

/*    printf("Starting State added, firstpos is\n");*/
/*    display_set(Dstates->iset[0],0);*/
    while(counter < sets){
		 processUnmarkedState(parser,&counter,&sets,&tCalcs,&U);
	  	 checkForUnmarked();
}
/*    printf("DONE CREATING DFA STATES\n");*/
/*    printf("THEY ARE AS FOLLOWS\n");*/
/*    for(int j=0;j<vector_used(Dstates);j++)*/
/*	   display_set(Dstates->iset[j],0);*/
	tTran = malloc(sizeof(int*)*set_used(parser->parseTree->alphabet));
	tDUtransition= malloc(sizeof(int_set**)*set_used(parser->parseTree->alphabet));
	{
	int we;
    	for(we=0;we<set_used(parser->parseTree->alphabet);we++){
			tTran[we] = malloc(sizeof(int)*vector_used(tCalcs.Dstates));
	   		tDUtransition[we] = malloc(sizeof(int_set*)*vector_used(tCalcs.Dstates));
		}
}
{
	int i;
    for(i=0;i<set_used(parser->parseTree->alphabet);i++){
		int j;
	   for(j=0;j<vector_used(tCalcs.Dstates);j++){
		  tTran[i][j] = tCalcs.Dtransition[i][j];
		  tDUtransition[i][j] = tCalcs.DUtransition[i][j];
		  tCalcs.DUtransition[i][j] = NULL;
	   }
	   free(tCalcs.Dtransition[i]);
	   free(tCalcs.DUtransition[i]);
	   tCalcs.Dtransition[i] = NULL;
	   tCalcs.DUtransition[i] = NULL;
    }
}
    free(tCalcs.Dtransition);
    free(tCalcs.DUtransition);
    tCalcs.Dtransition = NULL;
    tCalcs.DUtransition = NULL;
/*    printf("Dtransition table computed\n");*/
    printf("Alphabet Symbol \n");
    printf("S|");
	{
		int i;
		for(i=0;i<set_used(parser->parseTree->alphabet);i++){
		   printf("|%c",*(char*)get_value_by_index_set(parser->parseTree->alphabet,i));
		}
	}
    printf("|\n");
	{
		{
		int r;
		for(r=0;r<vector_used(tCalcs.Dstates);r++){
			int i;
			printf("%d|",r+1);
	   	 	for(i=0;i<set_used(parser->parseTree->alphabet);i++){
		 	   if(tTran[i][r] != -1)
				   printf("|%d", tTran[i][r]);
			   else
				   printf("|x");
		   }
		   printf("|\n");
 	   }
   }
}
/*    printf("DUtransition table computed and going to print all sets\n");
    for(int r=0;r<vector_used(Dstates);r++){
	   for(int i=0;i<set_used(alphabet);i++){
		  display_set(tDUtransition[i][r],0);
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
    for(k=0;k<parser->parseTree->num_re;k++){
		int y;
	   	Fstates = NULL;
	   	lastpos = parser->parseTree->finalpos[k];
/*    printf("Finish States for the whole file RE: \n");*/
	   	fcount = 0;
/*    printf("Position using for last state: %d\n",lastpos);*/
	   	for(y=0;y<vector_used(tCalcs.Dstates);y++){
		    if(is_in_set(*get_by_index_in_vector(tCalcs.Dstates,y),lastpos)==0){
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
	   			for(y=0;y<vector_used(tCalcs.Dstates);y++){
		    		if(is_in_set(*get_by_index_in_vector(tCalcs.Dstates,y),lastpos)==0){
/*		  printf("Adding State %d to finish states\n",y+1);*/
						add_to_set(&Fstates,y+1);
						add_to_set(&FFstates,y+1);
		   		 	}
				}
			}
	   parser->parseTree->Fstates[k] = Fstates;
    }
}
  /*  printf("final finish state set for the whole file RE\n");*/
/*    display_set(FFstates,0);*/

    dfa->FFstates = FFstates;
    dfa->Fstates = parser->parseTree->Fstates;
    dfa->start = (*(int_set**)get_by_index_in_vector(tCalcs.Dstates,0))->super.uniq;
    dfa->num_states = vector_used(tCalcs.Dstates);
    dfa->Dstates = tCalcs.Dstates;
    dfa->alphabet = copy_sets(parser->parseTree->alphabet);
    dfa->DUTran = tDUtransition;
    dfa->action_array = parser->parseTree->action_array;
    dfa->num_re = parser->parseTree->num_re;
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
