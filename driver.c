#include "buffer.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
extern void refresh_upper_buffer(buffer* inbuffer, FILE* infile);
extern void refresh_lower_buffer(buffer* inbuffer, FILE* infile);
void printline(buffer* mybuf);
void printbackline(buffer* mybuf);


buffer *forward;
buffer *back;

int main(int argc, const char ** argv){
	static FILE* work;
	buffer* mybuf;
    struct _tree * tre;
	if((work = fopen(argv[1], "r")) == NULL ){
		perror("\033[0;31merror\033[0m");
		exit(-1);
	}

	printf("opened file on my own\n");
//	buffer_from_file(work);
	fclose(work);
	work = NULL;
    
    
	printf("opening file with buffer from filename\n");
	mybuf = buffer_from_filename(argv[1]);

    printf("showing full buffer\n");
	display_buffer(mybuf);

    for(int j=0;j<102;j++)
	   	printline(mybuf);
    display_buffer(mybuf);
    for(int j=0;j<80;j++)
	   printbackline(mybuf);
    
    tre = create_tree();
    delete_tree(tre);
    
    
    fclose(work);

    if(mybuf != NULL){

	   if(mybuf->buf != NULL)
		  free(mybuf->buf);

	   mybuf->buf = NULL;

	   free(mybuf);

	   mybuf = NULL;
    }
	return 0;
}


inline void printline(buffer* mybuf){
    char  mystring[4048];
    char s;
    int i;
    i=0;
    while((s=getchar(mybuf))!= '\n' && s != '\0' && s != EOF){
	   mystring[i]=s;
	   i++;
    }
    mystring[i]='\0';
    printf("string founds: %s\n",mystring);
}

inline void printbackline(buffer* mybuf){
    char  mystring[4048];
    char duplicate[4048];
    char s;
    int i;
    i=0;
    while((s=ungetchar(mybuf))!= EOF && s != '\0' && s!= '\n'){
	   mystring[i]=s;
	   i++;
    }
    for(int t=i-1,v=0;t>=0;t--,v++)
	   duplicate[v]=mystring[t];
    duplicate[i]='\0';
    printf("IN REVERSE \n%s\n",duplicate);
}
