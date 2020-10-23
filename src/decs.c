#include <string.h>
#include "Parser.h"
#include "Lexer.h"

char* parseDeclarations(Io* programIO){
	char* declarations;

	declarations = NULL;

	declarations = readRawStringUntilToken(&programIO->own_lexer, CLOSE_STARTER);

	pushBackLastToken(&programIO->own_lexer);
	return declarations;
}


char* oldparseDeclarations(Io* programIO){
	char* c;
    char sbuf[8000];
    char *decs;
    int scount =0;
    char d;
  char **t;
c = &programIO->own_lexer.current_char;
    t = NULL;
    decs = NULL;
    while((*c = getchar(&programIO->own_lexer.inputBuffer))!= EOF && *c !='\0'){
	   if(*c == '%'){
		  d = *c;
		  *c = getchar(&programIO->own_lexer.inputBuffer);
		  if(*c == '}'){
			 sbuf[scount]='\0';
			 decs = malloc(sizeof(char)*strlen(sbuf)+1);
			 strncpy(decs,sbuf,strlen(sbuf)+1);
			 *c = getchar(&programIO->own_lexer.inputBuffer);
			 while(is_ws(*c) == 0)
				*c = getchar(&programIO->own_lexer.inputBuffer);
			 /* return decs; */
			 break;
		  }
		  else{
			 sbuf[scount] = d;
			 sbuf[scount+1] = *c;
			 scount += 2;
			 *c = getchar(&programIO->own_lexer.inputBuffer);
		  }
	   }
	   else{
		  sbuf[scount] = *c;
		  scount++;
	   }
    }
    if(decs){
	   parseDefinitions(programIO);
	   if(*programIO->lexfile.defs != NULL){
		  printf("found definitions, they are as follows\n");
		  t = programIO->lexfile.defs;
		  while(*t != NULL){
			 printf("Definition Name: %s Definition Value %s\n",t[0],t[1]);
			 t += 2;
		  }
		  programIO->lexfile.defbuf = malloc(sizeof(Buffer*)*programIO->lexfile.num_defs);
		  {
			  int y;
			  for(y=0;y<programIO->lexfile.num_defs;y++)
			 	 programIO->lexfile.defbuf[y] = buffer_from_string(programIO->lexfile.defs[(2*y)+1]);
		  }
	   }
	   return decs;
    }
    return NULL;

}

void parseDefinitions(Io* programIO){
	char* c;
    char *** defbuf = &programIO->lexfile.defs;
    int count;
    int num_def,curlen;
   int olast;
    int a;
	c = &programIO->own_lexer.current_char;
	    programIO->lexfile.num_defs = 0;
    *defbuf = malloc(sizeof(char*)*50);
	{
		int a;
    	for(a=0;a<50;a++)
	   	 (*defbuf)[a] = NULL;
	}
    num_def = 0;
	{
    for(a=0;a<50;a+=2){
	   if(a == 12)
		  ;
   
defbegin:	   while((is_ws(*c) ==0) || *c == '\n')
		  *c = getchar(&programIO->own_lexer.inputBuffer);
	   if(*c == '%'){
		  *c = getchar(&programIO->own_lexer.inputBuffer);
		  if(*c == '%'){
			 ungetchar(&programIO->own_lexer.inputBuffer);
			 ungetchar(&programIO->own_lexer.inputBuffer);
			 *c = getchar(&programIO->own_lexer.inputBuffer);
			 programIO->lexfile.num_defs = num_def;
			 return;
			 /*			 break; */
		  }
	   }
	   (*defbuf)[a] = malloc(sizeof(char)*25);
	   (*defbuf)[a+1] = malloc(sizeof(char)*60);
	   {
		   int b;
	   	for(b=0;b<24;b++)
			  (*defbuf)[a][b] = ' ';
	   }
	   (*defbuf)[a][24] = '\0';
	   {
		   int b;
			for(b=0;b<59;b++)
			  (*defbuf)[a+1][b] = ' ';
	   }
	   (*defbuf)[a+1][59] = '\0';
	   count =0;
	   while(is_ws(*c) !=0){
		  (*defbuf)[a][count] = *c;
		  count++;
		  *c = getchar(&programIO->own_lexer.inputBuffer);
	   }
	   (*defbuf)[a][count] = '\0';
	   num_def++;
	   {
	   int g;
	   for(g=0;g<(num_def*2)-2;g+=2){
		  if(strcmp((*defbuf)[g],(*defbuf)[a])==0){
			 free((*defbuf)[a]);
			 free((*defbuf)[a+1]);
			 (*defbuf)[a] = NULL;
			 (*defbuf)[a+1] = NULL;
			 printf("definition already exists or name already taken\n");
			 while(*c != '\n')
				  *c = getchar(&programIO->own_lexer.inputBuffer);
			 *c = getchar(&programIO->own_lexer.inputBuffer);
			 num_def--;
			 goto defbegin;
		  }
	   }
   }
	   count = 0;
	   curlen = 25;
	   while(is_ws(*c) == 0)
		  *c = getchar(&programIO->own_lexer.inputBuffer);
		   olast = -1;
	   while(*c != '\n'){
		  switch(*c){
			 case '{':
				if((olast != -1)){
				    if(olast != '\\'){
					   	*c = getchar(&programIO->own_lexer.inputBuffer);
					   	*c = getchar(&programIO->own_lexer.inputBuffer);
					   	if(*c == ','){
						    /* found a range so put characters back and keep reading*/
						    ungetchar(&programIO->own_lexer.inputBuffer);
						    ungetchar(&programIO->own_lexer.inputBuffer);
						    ungetchar(&programIO->own_lexer.inputBuffer);
						    *c = getchar(&programIO->own_lexer.inputBuffer);
						    /* continue to default section of switch statement*/
				    		}
				    		else{
						    /* found a definition use*/
						    char defname[25];
						    int dnlen = 0;
						    ungetchar(&programIO->own_lexer.inputBuffer);
						    ungetchar(&programIO->own_lexer.inputBuffer);
						    *c = getchar(&programIO->own_lexer.inputBuffer);
						    while(*c != '}'){
							   defname[dnlen] = *c;
							   *c = getchar(&programIO->own_lexer.inputBuffer);
							   dnlen++;
						    }
						    defname[dnlen] = '\0';
							{
							int g;
						    for(g=0;g<(num_def*2)-2;g+=2){
							   if(strcmp((*defbuf)[g],defname)==0){
/*								  printf("definition already exists and is earlier\n");*/
								  char *ty;
/*								  printf("size of current %d and size of one searching in loop %d\n",sizeof(char)*strlen((*defbuf)[a+1]),sizeof(char)*strlen((*defbuf)[g+1]));*/
								  curlen += strlen((*defbuf)[g+1]);
								  (*defbuf)[a+1] = realloc((*defbuf)[a+1],sizeof(char)*(curlen+3));
								  ty = (*defbuf)[g+1];
								  (*defbuf)[a+1][count] = '(';
								  count++;
								  while(*ty != '\0'){
									 (*defbuf)[a+1][count] = *ty;
									 count++;
									 ty++;
								  }
								  (*defbuf)[a+1][count] = ')';
								  count++;
								  break;
								/*  olast = *c;*/
								 /* *c = getchar(&programIO->own_lexer.inputBuffer);*/
							   }
						    }
						}
						    olast = *c;
						    *c = getchar(&programIO->own_lexer.inputBuffer);
						    continue;
				    		}
				    	}
				    	else{
					    /* found previous escape so keep reading*/
					    /* continue to default section of switch statement*/

				    	}
				}
				else{
				    /* found a definition use*/
				    char defname[25];
				    int dnlen = 0;
				    *c = getchar(&programIO->own_lexer.inputBuffer);
				    while(*c != '}'){
					   defname[dnlen] = *c;
					   *c = getchar(&programIO->own_lexer.inputBuffer);
					   dnlen++;
				    }
				    defname[dnlen] = '\0';
					{
					int g;
				    for(g=0;g<(num_def*2)-2;g+=2){
					   if(strcmp((*defbuf)[g],defname)==0){
/*						  printf("definition already exists and is earlier\n");*/
						  char *ty;
/*						  printf("size of current %d and size of one searching in loop %d\n",sizeof(char)*strlen((*defbuf)[a+1]),sizeof(char)*strlen((*defbuf)[g+1]));*/
						  curlen += strlen((*defbuf)[g+1]);
						  (*defbuf)[a+1] = realloc((*defbuf)[a+1],sizeof(char)*(curlen+3));
						  ty = (*defbuf)[g+1];
						  (*defbuf)[a+1][count] = '(';
						  count++;
						  while(*ty != '\0'){
							 (*defbuf)[a+1][count] = *ty;
							 count++;
							 ty++;
						  }
						  (*defbuf)[a+1][count] = ')';
						  count++;
						  break;
						  /*  olast = *c;*/
						  /* *c = getchar(&programIO->own_lexer.inputBuffer);*/
					   }
				    }
				}
				    olast = *c;
				    *c = getchar(&programIO->own_lexer.inputBuffer);
				    continue;
				}
			 default:
				(*defbuf)[a+1][count] = *c;
				count++;
				olast = *c;
				*c = getchar(&programIO->own_lexer.inputBuffer);
				break;
		  }
	   }
	   *c = getchar(&programIO->own_lexer.inputBuffer);
	   (*defbuf)[a+1] = realloc((*defbuf)[a+1],curlen+4);
	   (*defbuf)[a+1][count] = '\0';
	   curlen = 25;
    }
	}
    programIO->lexfile.num_defs = num_def;
    return;
}
