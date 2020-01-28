#include "../include/decs.h"
#include <string.h>
char* declarations(buffer* mbuf, char*c,struct _lfile* file){
    char sbuf[8000];
    char *decs;
    int scount =0;
    char d;
  char **t;
    t = NULL;
    decs = NULL;
    while((*c = getchar(mbuf))!= EOF && *c !='\0'){
	   if(*c == '%'){
		  d = *c;
		  *c = getchar(mbuf);
		  if(*c == '}'){
			 sbuf[scount]='\0';
			 decs = malloc(sizeof(char)*strlen(sbuf)+1);
			 strcpy(decs,sbuf);
			 *c = getchar(mbuf);
			 while(is_ws(*c) == 0)
				*c = getchar(mbuf);
			 /* return decs; */
			 break;
		  }
		  else{
			 sbuf[scount] = d;
			 sbuf[scount+1] = *c;
			 scount += 2;
			 *c = getchar(mbuf);
		  }
	   }
	   else{
		  sbuf[scount] = *c;
		  scount++;
	   }
    }
    if(decs){
	   read_definitions(mbuf,c,file);
	   if(*file->defs != NULL){
		  printf("found definitions, they are as follows\n");
		  t = file->defs;
		  while(*t != NULL){
			 printf("Definition Name: %s Definition Value %s\n",t[0],t[1]);
			 t += 2;
		  }
		  file->defbuf = malloc(sizeof(buffer*)*file->num_defs);
		  {
			  int y;
			  for(y=0;y<file->num_defs;y++)
			 	 file->defbuf[y] = buffer_from_string(file->defs[(2*y)+1]);
		  }
	   }
	   return decs;
    }
    return NULL;

}

void read_definitions(buffer* mbuf,char* c,struct _lfile* file ){
    char *** defbuf = &file->defs;
    int count,num_def;
	int curlen;
   int olast;
    int a;
	    file->num_defs = 0;
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
		  *c = getchar(mbuf);
	   if(*c == '%'){
		  *c = getchar(mbuf);
		  if(*c == '%'){
			 ungetchar(mbuf);
			 ungetchar(mbuf);
			 *c = getchar(mbuf);
			 file->num_defs = num_def;
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
		  *c = getchar(mbuf);
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
				  *c = getchar(mbuf);
			 *c = getchar(mbuf);
			 num_def--;
			 goto defbegin;
		  }
	   }
   }
	   count = 0;
	   curlen = 25;
	   while(is_ws(*c) == 0)
		  *c = getchar(mbuf);
		   olast = -1;
	   while(*c != '\n'){
		  switch(*c){
			 case '{':
				if((olast != -1)){
				    if(olast != '\\'){
					   	*c = getchar(mbuf);
					   	*c = getchar(mbuf);
					   	if(*c == ','){
						    /* found a range so put characters back and keep reading*/
						    ungetchar(mbuf);
						    ungetchar(mbuf);
						    ungetchar(mbuf);
						    *c = getchar(mbuf);
						    /* continue to default section of switch statement*/
				    		}
				    		else{
						    /* found a definition use*/
						    char defname[25];
						    int dnlen = 0;
						    ungetchar(mbuf);
						    ungetchar(mbuf);
						    *c = getchar(mbuf);
						    while(*c != '}'){
							   defname[dnlen] = *c;
							   *c = getchar(mbuf);
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
								 /* *c = getchar(mbuf);*/
							   }
						    }
						}
						    olast = *c;
						    *c = getchar(mbuf);
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
				    *c = getchar(mbuf);
				    while(*c != '}'){
					   defname[dnlen] = *c;
					   *c = getchar(mbuf);
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
						  /* *c = getchar(mbuf);*/
					   }
				    }
				}
				    olast = *c;
				    *c = getchar(mbuf);
				    continue;
				}
			 default:
				(*defbuf)[a+1][count] = *c;
				count++;
				olast = *c;
				*c = getchar(mbuf);
				break;
		  }
	   }
	   *c = getchar(mbuf);
	   (*defbuf)[a+1] = realloc((*defbuf)[a+1],curlen+4);
	   (*defbuf)[a+1][count] = '\0';
	   curlen = 25;
    }
	}
    file->num_defs = num_def;
    return;
}
