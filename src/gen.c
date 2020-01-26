#include "../include/gen.h"
#include <string.h>
#include <stdint.h>
void use_later(void){
	/*
*/
}

#define to_file(...) fprintf(outfile, __VA_ARGS__)

void generate_output(struct _lfile lexfile, struct _DFA* dfa){
	char 	cb[50];
    char *	infstring;
    FILE * 	outfile, *infile;
    char 	alen[50];
    char *	temp;
    char *	tp;
    char * 	ala;
    char * 	dara;
    char * 	arra;
	char * 	ffarra;
	char * 	farra;
    int count, acnt, num_tabs;

    outfile = NULL;
    ala = NULL;
    dara = NULL;
    arra = NULL;
	farra = NULL;
	ffarra = NULL;
	count =0;
	acnt = 0;
	num_tabs = 7;
	if((outfile = fopen("sclex.yy.c","w"))!=NULL){
#if defined(__linux__)
		extern uint8_t _blob[];
		extern int _blob_size;
#else
		extern uint8_t blob[];
		extern int blob_size;
#endif
		FILE* temp_file = NULL;
		if((temp_file = fopen("outfile.in","w"))!=NULL){
#if defined(__linux__)
			fwrite(_blob,1,_blob_size,temp_file);
#else
			fwrite(blob,1,blob_size,temp_file);
#endif
			fclose(temp_file);
		}
	    if((infile = fopen("outfile.in","r")) != NULL){
		   fseek(infile, 0, SEEK_END);
		   long len = ftell(infile);
		   fseek(infile, 0, SEEK_SET);
		   ala = malloc(sizeof(char)*((6*dfa->alphabet->used)+1));
		   farra = malloc(sizeof(char)*((dfa->FFstates->used*3)+1));
		   dara = malloc(sizeof(char)*((dfa->num_states*dfa->alphabet->used*7)+2*dfa->num_states+10));
		   ffarra = malloc(sizeof(char)*((dfa->num_re*22)+1));
		   for(int t=0;t<dfa->alphabet->used;t++){
			  ala[acnt] = '\'';
				 switch(dfa->alphabet->s[t]){
					case '\n':
					    ala[acnt+1] = '\\';
					    ala[acnt+2] = 'n';
					    acnt++;
					    break;
					case '\t':
					    ala[acnt+1] = '\\';
					    ala[acnt+2] = 't';
					    acnt++;
					    break;
					case '\\':
					    ala[acnt+1] = '\\';
					    ala[acnt+2] = '\\';
					    acnt++;
					    break;
					default:
					    ala[acnt+1] = dfa->alphabet->s[t];
					    break;
				 }
			  ala[acnt+2] = '\'';
			  acnt +=3;
			  if(t != dfa->alphabet->used -1){
				 ala[acnt] = ',';
				 acnt++;
				 ala[acnt] = ' ';
				 acnt++;
			  }
		   }
		   ala[acnt] = '\0';
 //dara start
		   acnt =0;
//		   printf("%s\n",ala);
		   for(int t=0;t<dfa->alphabet->used;t++){
			  dara[acnt] = '{';
			  acnt++;
			  for(int s=0;s<dfa->num_states;s++){
				 sprintf(cb,"%d",dfa->Dtran[t][s]);
				 sprintf(&dara[acnt],"%d",dfa->Dtran[t][s]);
				 acnt += strlen(cb);
				 if(s != dfa->num_states -1){
					dara[acnt] = ',';
					acnt++;
				 }
			  }
			  dara[acnt] = '}';
			  acnt++;
			  if(t != dfa->alphabet->used -1){
				 dara[acnt] = ',';
				 acnt++;
			  }
			  dara[acnt] = '\n';
			  acnt++;
		   }
		   dara[acnt] = '\0';
//ffarra start
		   acnt =0;
		   for(int t=0;t<dfa->num_re;t++){
			  ffarra[acnt] = '{';
			  acnt++;
			  for(int s=0;s<dfa->Fstates[t]->used;s++){
				 sprintf(cb,"%d",dfa->Fstates[t]->s[s]);
				 sprintf(&ffarra[acnt],"%d",dfa->Fstates[t]->s[s]);
				 acnt += strlen(cb);
				 if(s != dfa->Fstates[t]->used - 1){
					ffarra[acnt] = ',';
					acnt++;
				 }
			  }
			  ffarra[acnt] = '}';
			  acnt++;
			  if(t != dfa->num_re -1){
				 ffarra[acnt] = ',';
				 acnt++;
			  }
			  ffarra[acnt] = '\n';
			  acnt++;
		   }
		  ffarra[acnt] = '\0';
		   
// farra start		   
			   	acnt =0;
				for(int t=0;t<dfa->FFstates->used;t++){
					 sprintf(cb,"%d", dfa->FFstates->s[t]);
					 sprintf(&farra[acnt],"%d",dfa->FFstates->s[t]);
					 acnt += strlen(cb);
					  if(t != dfa->FFstates->used -1){
						  farra[acnt] = ',';
						  acnt++;
				 	 }
			   }
			   farra[acnt] = '\0';
			    printf("%s",farra);
		   infstring = malloc(sizeof(char)*len);
		   temp = malloc(sizeof(char)*(len+20000));
		   tp = temp;
		   fread(infstring,1,len,infile);
		   for(int i=0;i<len;i++){
			  if(i < len-3 && infstring[i] == '#' && infstring[i+1] == '0' && infstring[i+2] == '#'){
				 i += 2;
				 switch(count){
					case 0:
					    	sprintf(tp,"%s",lexfile.decs);
					    tp += strlen(lexfile.decs);
					    count++;
					    break;
					case 1:
					    sprintf(alen,"%d",dfa->alphabet->used);
					    sprintf(tp,"%d",dfa->alphabet->used);
					    tp += strlen(alen);
					    count++;
					    break;
					case 2:
					    sprintf(alen,"%d",dfa->num_states);
					    sprintf(tp,"%d",dfa->num_states);
					    tp += strlen(alen);
					    count++;
					    break;
					case 3:
						sprintf(alen,"%d",dfa->FFstates->used);
						sprintf(tp,"%d",dfa->FFstates->used);
						tp += strlen(alen);
						count++;
						break;
					case 4:
						sprintf(alen,"%d",dfa->num_re);
						sprintf(tp,"%d",dfa->num_re);
						tp += strlen(alen);
						count++;
						break;
					case 5:
					    sprintf(tp,"%s",ala);
					    tp += strlen(ala);
					    count++;
					    break;
					case 6:
					    sprintf(tp,"%s",dara);
					    tp += strlen(dara);
					    count++;
					    break;
					case 7:
						sprintf(tp,"%s",farra);
						tp += strlen(farra);
						count++;
						break;
					case 8:
						sprintf(tp,"%s",ffarra);
						tp += strlen(ffarra);
						count++;
						break;
					case 9:
					   sprintf(tp,"switch(n){\n");
					   tp += 11;
					    for(int i=0;i<lexfile.tree->used;i++){
//						   printf("action array %d: %s\n",i,lexfile.tree->action_array[i]);
						   sprintf(cb,"%d",i);
						   for(int tab=0;tab<num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
						   sprintf(tp,"case %d:\n",i);
						   tp += 7+strlen(cb);
						   for(int tab=0;tab<=num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
						   sprintf(tp,"%s\n",lexfile.tree->action_array[i]);
						   tp += strlen(lexfile.tree->action_array[i]);
						   sprintf(tp,"\n");
						   tp++;
						   for(int tab=0;tab<=num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
						   sprintf(tp,"break;\n");
						   tp += 7;
					    }
					   for(int tab=0;tab<num_tabs;tab++){
						   sprintf(tp,"\t");
						   tp++;
					   }
						sprintf(tp,"}\n");
						tp += 2;
					    count++;
					    break;
				 }
			  }
			  else{
				tp[0] = infstring[i];
				tp++;
			  }
		   }
		   *tp = '\0';

		   to_file("%s",temp);

		   free(ala);
		   ala = NULL;
		   free(dara);
		   dara = NULL;
		   free(farra);
		   farra = NULL;
		   free(ffarra);
		   ffarra = NULL;
		   free(temp);
		   temp = NULL;
		   free(infstring);
		   infstring = NULL;
		   fclose(infile);
		   infile = NULL;
		   fclose(outfile);
		   outfile = NULL;
	    }
	    else{
		   printf("Couldn't open template file used to create the source code for the lexical analyzer\n");
	    fclose(outfile);
	    outfile = NULL;
	    }
		remove("outfile.in");
	}
	else{
	    lex_error(0);
	}
}
#undef to_file
