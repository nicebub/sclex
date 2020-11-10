#include "../include/gen.h"
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
void use_later(void){
	/*
*/
}

/*
only after C99
#define to_file(...) fprintf(outfile, __VA_ARGS__)
*/

void generate_output(Parser* parser, struct _DFA* dfa){
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
		extern uint8_t _bufferh[];
		extern uint8_t _bufferc[];
		extern int _blob_size;
		extern int _bufferh_size;
		extern int _bufferc_size;
#else
		extern uint8_t blob[];
		extern uint8_t bufferh[];
		extern uint8_t bufferc[];
		extern int blob_size;
		extern int bufferh_size;
		extern int bufferc_size;
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
 		   long len;
		   int t;
		   int i;
		   fseek(infile, 0, SEEK_END);
		   len = ftell(infile);
		   fseek(infile, 0, SEEK_SET);
		   ala = malloc(sizeof(char)*((6*set_used(dfa->alphabet))+1));
		   farra = malloc(sizeof(char)*((set_used(dfa->FFstates)*3)+1));
		   dara = malloc(sizeof(char)*((dfa->num_states*set_used(dfa->alphabet)*7)+2*dfa->num_states+10));
		   ffarra = malloc(sizeof(char)*((dfa->num_re*200)+1));
		   for(t=0;t<set_used(dfa->alphabet);t++){
			  ala[acnt] = '\'';
				 switch(*(char*)get_value_by_index_set(dfa->alphabet,t)){
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
					    ala[acnt+1] = *(char*)get_value_by_index_set(dfa->alphabet,t);
					    break;
				 }
			  ala[acnt+2] = '\'';
			  acnt +=3;
			  if(t != set_used(dfa->alphabet) -1){
				 ala[acnt] = ',';
				 acnt++;
				 ala[acnt] = ' ';
				 acnt++;
			  }
		   }
		   ala[acnt] = '\0';
 /*dara start*/
		   acnt =0;
/*		   printf("%s\n",ala);*/
		   {
		   int t;
		   for(t=0;t<set_used(dfa->alphabet);t++){
 			  int s;
			  dara[acnt] = '{';
			  acnt++;
			  for(s=0;s<dfa->num_states;s++){
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
			  if(t != set_used(dfa->alphabet) -1){
				 dara[acnt] = ',';
				 acnt++;
			  }
			  dara[acnt] = '\n';
			  acnt++;
		   }
	   }
		   dara[acnt] = '\0';
/*ffarra start*/
		   acnt =0;
		   {
			   int t;
		   for(t=0;t<dfa->num_re;t++){
 			  int s;
			  ffarra[acnt] = '{';
			  acnt++;
			  for(s=0;s<set_used(dfa->Fstates[t]);s++){
				 sprintf(cb,"%d",*(int*)get_value_by_index_set(dfa->Fstates[t],s));
				 sprintf(&ffarra[acnt],"%d",
				 	*(int*)get_value_by_index_set(dfa->Fstates[t],s));
				 acnt += strlen(cb);
				 if(s != set_used(dfa->Fstates[t]) - 1){
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
	   }
		  ffarra[acnt] = '\0';
		   
/* farra start	*/	   
			   	acnt =0;
				{
					int t;
				for(t=0;t<set_used(dfa->FFstates);t++){
					 sprintf(cb,"%d", *(int*)get_value_by_index_set(dfa->FFstates,t));
					 sprintf(&farra[acnt],"%d",
					 	*(int*)get_value_by_index_set(dfa->FFstates,t));
					 acnt += strlen(cb);
					  if(t != set_used(dfa->FFstates) -1){
						  farra[acnt] = ',';
						  acnt++;
				 	 }
			   }
		   }
			   farra[acnt] = '\0';
			    printf("%s",farra);
		   infstring = malloc(sizeof(char)*len);
#if defined(__linux__)
		   temp = malloc(_bufferh_size+_bufferc_size+sizeof(char)*(len+20000));
#else
		   temp = malloc(bufferh_size+bufferc_size+sizeof(char)*(len+20000));
#endif


		   tp = temp;
		   fread(infstring,1,len,infile);
		   for(i=0;i<len;i++){
			  if(i < len-3 && infstring[i] == '#' && infstring[i+1] == '0' && infstring[i+2] == '#'){
				 i += 2;
				 switch(count){
					 case BUFFER_PAR:
						#if defined(__linux__)
						snprintf(tp,_bufferh_size,"%s",_bufferh);
						tp += _bufferh_size-1;
					    snprintf(tp,_bufferc_size,"%s",_bufferc);
					    tp += _bufferc_size-1;
						#else
						snprintf(tp,bufferh_size,"%s",bufferh);
						tp += bufferh_size-1;/*bufferh_size;*/
					    snprintf(tp,bufferc_size,"%s",bufferc);
					    tp += bufferc_size-1;
						#endif

						count++;
						break;
					case DECL_PAR:
					    	sprintf(tp,"%s",parser->decs);
					    tp += strlen(parser->decs);
					    count++;
					    break;
					case ALPH_SZ_PAR:
					    sprintf(alen,"%d",set_used(dfa->alphabet));
					    sprintf(tp,"%d",set_used(dfa->alphabet));
					    tp += strlen(alen);
					    count++;
					    break;
					case STATE_SZ_PAR:
					    sprintf(alen,"%d",dfa->num_states);
					    sprintf(tp,"%d",dfa->num_states);
					    tp += strlen(alen);
					    count++;
					    break;
					case ACCEPT_STATE_SZ_PAR:
					    sprintf(alen,"%d",set_used(dfa->FFstates));
					    sprintf(tp,"%d",set_used(dfa->FFstates));
						tp += strlen(alen);
						count++;
						break;
					case NUM_REGEX_PAR:
						sprintf(alen,"%d",dfa->num_re);
						sprintf(tp,"%d",dfa->num_re);
						tp += strlen(alen);
						count++;
						break;
					case ALPH_PAR:
					    sprintf(tp,"%s",ala);
					    tp += strlen(ala);
					    count++;
					    break;
					case MOVEMENT_PAR:
					    sprintf(tp,"%s",dara);
					    tp += strlen(dara);
					    count++;
					    break;
					case ACCEPT_STATE_PAR:
						sprintf(tp,"%s",farra);
						tp += strlen(farra);
						count++;
						break;
					case ACCEPT_TABLE_PAR:
						sprintf(tp,"%s",ffarra);
						tp += strlen(ffarra);
						count++;
						break;
					case USER_CODE_PAR:
					   sprintf(tp,"switch(n){\n");
					   tp += 11;
					   {
					   int i;
					    for(i=0;i<parser->parseTree->used;i++){
/*						   printf("action array %d: %s\n",i,lexfile.tree->action_array[i]);*/
						   sprintf(cb,"%d",i);
						   {
						   int tab;
						   for(tab=0;tab<num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
					   }
				   
						   sprintf(tp,"case %d:\n",i);
						   tp += 7+strlen(cb);
						   {
							   int tab;
						   for(tab=0;tab<=num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
					   }
						   sprintf(tp,"%s\n",parser->parseTree->action_array[i]);
						   tp += strlen(parser->parseTree->action_array[i]);
						   sprintf(tp,"\n");
						   tp++;
						   {
							   int tab;
						   for(tab=0;tab<=num_tabs;tab++){
							   sprintf(tp,"\t");
							   tp++;
						   }
					   }
						   sprintf(tp,"break;\n");
						   tp += 7;
					    }
				 }
						{
							int tab;
					   for(tab=0;tab<num_tabs;tab++){
						   sprintf(tp,"\t");
						   tp++;
					   }
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
		   fprintf(outfile,"%s",temp);
/*		   to_file("%s",temp);*/

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
