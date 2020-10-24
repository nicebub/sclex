#include <string.h>
#include "Parser.h"
#include "Lexer.h"

char* parseDeclarations(Parser* parser){
	char* declarations;
	declarations = NULL;
	declarations = readRawStringUntilToken(&parser->lexer, tokenForType(CLOSE_STARTER));
	pushBackLastToken(parser,tokenForType(CLOSE_STARTER));
	return declarations;
}

/*
char* oldparseDeclarations(Parser* parser){
	char* c;
    char sbuf[8000];
    char *decs;
    int scount =0;
    char d;
  char **t;
c = &parser->lexer.current_char;
    t = NULL;
    decs = NULL;
    while((parser->lexer.current_char = getchar(&parser->lexer.inputBuffer))!= EOF && parser->lexer.current_char !='\0'){
	   if(parser->lexer.current_char == '%'){
		  d = parser->lexer.current_char;
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  if(parser->lexer.current_char == '}'){
			 sbuf[scount]='\0';
			 decs = malloc(sizeof(char)*strlen(sbuf)+1);
			 strncpy(decs,sbuf,strlen(sbuf)+1);
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 while(is_ws(parser->lexer.current_char) == 0)
				parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			break;
		  }
		  else{
			 sbuf[scount] = d;
			 sbuf[scount+1] = parser->lexer.current_char;
			 scount += 2;
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  }
	   }
	   else{
		  sbuf[scount] = parser->lexer.current_char;
		  scount++;
	   }
    }
    if(decs){
	   parseDefinitions(parser);
	   if(*parser->defs != NULL){
		  printf("found definitions, they are as follows\n");
		  t = parser->defs;
		  while(*t != NULL){
			 printf("Definition Name: %s Definition Value %s\n",t[0],t[1]);
			 t += 2;
		  }
		  parser->defbuf = malloc(sizeof(Buffer*)*parser->num_defs);
		  {
			  int y;
			  for(y=0;y<parser->num_defs;y++)
			 	 parser->defbuf[y] = buffer_from_string(parser->defs[(2*y)+1]);
		  }
	   }
	   return decs;
    }
    return NULL;

}
*/
void parseDefinitions(Parser* parser){
	
}
void oldParseDefinitions(Parser* parser){
    char *** defbuf = &parser->defs;
    int count;
    int num_def,curlen;
   int olast;
    int a;
	    parser->num_defs = 0;
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
   
defbegin:	   while((is_ws(parser->lexer.current_char) ==0) || parser->lexer.current_char == '\n')
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	   if(parser->lexer.current_char == '%'){
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		  if(parser->lexer.current_char == '%'){
			 ungetchar(&parser->lexer.inputBuffer);
			 ungetchar(&parser->lexer.inputBuffer);
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 parser->num_defs = num_def;
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
	   while(is_ws(parser->lexer.current_char) !=0){
		  (*defbuf)[a][count] = parser->lexer.current_char;
		  count++;
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
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
			 while(parser->lexer.current_char != '\n')
				  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
			 num_def--;
			 goto defbegin;
		  }
	   }
   }
	   count = 0;
	   curlen = 25;
	   while(is_ws(parser->lexer.current_char) == 0)
		  parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
		   olast = -1;
	   while(parser->lexer.current_char != '\n'){
		  switch(parser->lexer.current_char){
			 case '{':
				if((olast != -1)){
				    if(olast != '\\'){
					   	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					   	parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
					   	if(parser->lexer.current_char == ','){
						    /* found a range so put characters back and keep reading*/
						    ungetchar(&parser->lexer.inputBuffer);
						    ungetchar(&parser->lexer.inputBuffer);
						    ungetchar(&parser->lexer.inputBuffer);
						    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
						    /* continue to default section of switch statement*/
				    		}
				    		else{
						    /* found a definition use*/
						    char defname[25];
						    int dnlen = 0;
						    ungetchar(&parser->lexer.inputBuffer);
						    ungetchar(&parser->lexer.inputBuffer);
						    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
						    while(parser->lexer.current_char != '}'){
							   defname[dnlen] = parser->lexer.current_char;
							   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
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
								/*  olast = parser->lexer.current_char;*/
								 /* parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);*/
							   }
						    }
						}
						    olast = parser->lexer.current_char;
						    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
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
				    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
				    while(parser->lexer.current_char != '}'){
					   defname[dnlen] = parser->lexer.current_char;
					   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
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
						  /*  olast = parser->lexer.current_char;*/
						  /* parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);*/
					   }
				    }
				}
				    olast = parser->lexer.current_char;
				    parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
				    continue;
				}
			 default:
				(*defbuf)[a+1][count] = parser->lexer.current_char;
				count++;
				olast = parser->lexer.current_char;
				parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
				break;
		  }
	   }
	   parser->lexer.current_char = getchar(&parser->lexer.inputBuffer);
	   (*defbuf)[a+1] = realloc((*defbuf)[a+1],curlen+4);
	   (*defbuf)[a+1][count] = '\0';
	   curlen = 25;
    }
	}
    parser->num_defs = num_def;
    return;
}
