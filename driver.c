/** 
	This is the buffer test main and other helper functions
We test refreshing the buffer, the upper half of the buffer, 
the lower half, buffer_from_filename(), displaying the buffer.
We print the buffer forwards and backwards to see if moving
forward and backward in the buffer works well.

*/

#include "buffer.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
extern void refresh_upper_buffer(buffer* inbuffer, FILE* infile);
extern void refresh_lower_buffer(buffer* inbuffer, FILE* infile);
/** Function Prototype

	void printline(buffer* mybuf);

Functionality: print a full line up to a newline character out to
	stanard output

Parameters: a pointer to an initialized buffer buffer* mybuf

Results: A line is printed to standard output from the input stream
	up to a new line '\n' character

*/
void printline(buffer* mybuf);

/** Function Prototype

	void printbackline(buffer* mybuf);

Functionality: Same as above but the character sequence goes backwards
	to a newline character and not forwards

Parameters: a pointer to an initialized buffer buffer* mybuf

Results: a Line is printed to standard output from the input stream up
	to a newline '\n' character, but reading backwards in the stream, not
	forwards
*/
void printbackline(buffer* mybuf);

/* unsed at this time */
buffer *forward;
buffer *back;

int main(int argc, const char ** argv){
	/* new file */
	static FILE* work;
	/* new buffer*/
	buffer* mybuf;
    /* new tree */
	struct _tree * tre;
	/* opening file error, from command line arguemnt 1v*/
	if((work = fopen(argv[1], "r")) == NULL ){
		perror("\033[0;31merror\033[0m");
		exit(-1);
	}

	printf("opened file on my own\n");
	fclose(work);
	work = NULL;
    
	/* initializing buffer from command line argument filename */
	printf("opening file with buffer from filename\n");
	mybuf = buffer_from_filename(argv[1]);

    printf("showing full buffer\n");
	display_buffer(mybuf);
	/* print to standard output 102 lines */
    for(int j=0;j<102;j++)
	   	printline(mybuf);
    display_buffer(mybuf);
	/* print the last 80 lines to standard output */
    for(int j=0;j<80;j++)
	   printbackline(mybuf);
    /* testing tree construction and deletion for a minute */
    tre = create_tree();
    delete_tree(tre);
    
    /* and any cleanup needed */
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

/**  

	void printline(buffer* mybuf)

Functionality: print a full line up to a newline character out to
	stanard output

Parameters: a pointer to an initialized buffer buffer* mybuf

Results: A line is printed to standard output from the input stream
	up to a new line '\n' character

*/

inline void printline(buffer* mybuf){
	/* 4 kilobytes character string */
	char  mystring[4048];

    char s;
    int i;

    i=0;
	/*construct a string up to end of file or null or newline \n character */
    while((s=getchar(mybuf))!= '\n' && s != '\0' && s != EOF){
	   mystring[i]=s;
	   i++;
    }
    mystring[i]='\0';
	/* print the string */
    printf("string founds: %s\n",mystring);
}

/**  

	void printbackline(buffer* mybuf)

Functionality: Same as above but the character sequence goes backwards
	to a newline character and not forwards

Parameters: a pointer to an initialized buffer buffer* mybuf

Results: a Line is printed to standard output from the input stream up
	to a newline '\n' character, but reading backwards in the stream, not
	forwards
*/
inline void printbackline(buffer* mybuf){
	/* 4 kilobytes character string*/
    char  mystring[4048];
	/* 4 kiobytes character string to duplicate previous declared */
    char duplicate[4048];

    char s;
    int i;
    i=0;
	/* construct a string from the input until eond of file, null or a 
	newline character are found */
    while((s=ungetchar(mybuf))!= EOF && s != '\0' && s!= '\n'){
	   mystring[i]=s;
	   i++;
    }
	/* duplicate the string in reverse */
    for(int t=i-1,v=0;t>=0;t--,v++)
	   duplicate[v]=mystring[t];
    duplicate[i]='\0';
	/* print the reversed string */
    printf("IN REVERSE \n%s\n",duplicate);
}
