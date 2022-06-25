/**
	The buffer structure and functions supplied with this program
were created in reference to the algorithm for a double-sided buffer
in the famous dragon book. The buffer is a front for the input stream an
allows for forward and backwards movement up to half the buffers length,
ie, if the buffer is 8K then the backwards direction can be up to 4K of
characters.

*/



#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#include <string.h>
#include <stdlib.h>

#ifndef AS_INCLUDE
#include "basebuffer.h"
#endif
#ifdef __STRICT_ANSI__
#define inline
#endif

#include "log.h"

static base_buffer_vtable vtable_base_buffer = {
	&base_refresh_upper_buffer,
	&base_refresh_lower_buffer,
	&base_refresh_buffer,
	&base_bgetchar,
	&base_ungetchar,
	&base_delete_buffer,
	&base_display_buffer
};
/*
void init_base_buffer_vtable(){
	vtable_base_buffer.refresh_upper_buffer = &base_refresh_upper_buffer;
	vtable_base_buffer.refresh_lower_buffer = &base_refresh_lower_buffer;
	vtable_base_buffer.refresh_buffer = &base_refresh_buffer;
	vtable_base_buffer.bgetchar = &base_bgetchar;
	vtable_base_buffer.ungetchar = &base_ungetchar;
	vtable_base_buffer.delete_buffer = &base_delete_buffer;
	vtable_base_buffer.display_buffer = &base_display_buffer;
}
*/
inline void refresh_upper_buffer(base_buffer* inbuf){
	inbuf->vtable->refresh_upper_buffer(inbuf);
}

inline void refresh_lower_buffer(base_buffer* inbuf){
	inbuf->vtable->refresh_lower_buffer(inbuf);
}

inline void refresh_buffer(base_buffer* inbuf, const int start){
	inbuf->vtable->refresh_buffer(inbuf,start);
}
inline void delete_buffer(base_buffer* mbuf){
	mbuf->vtable->delete_buffer(mbuf);
}

inline void display_buffer(const base_buffer* inbuf){
	inbuf->vtable->display_buffer(inbuf);
}

inline int bgetchar(base_buffer* inbuf){
	return inbuf->vtable->bgetchar(inbuf);
}
inline int ungetchar(base_buffer* mbuf){
	return mbuf->vtable->ungetchar(mbuf);
}

void init_base_buffer(base_buffer* buf){
	buf->vtable= &vtable_base_buffer;
    buf->buf=NULL;
    buf->forward=NULL;
    buf->back=NULL;
    buf->work=NULL;
    buf->len=0;
    buf->type=0;
}

base_buffer* new_base_buffer(size_t size){
    base_buffer *mbuf;
    mbuf = NULL;
    mbuf = malloc(sizeof(*mbuf));
    if(!mbuf){
	   LOG_0("couldn't allocate memory for new buffer%s","");
	   return NULL;
    }
	   mbuf->len = size;
	   mbuf->buf = malloc(sizeof(char)*(mbuf->len+2));
    if(!mbuf->buf){
	   free(mbuf);
	   mbuf = NULL;
	   LOG_0("couldn't allocate memory for new buffer%s","");
	   return NULL;
    }

    /* copy the input string into the buffer, setup the control
	    characters, and return the buffer
    */
	   mbuf->buf[mbuf->len] = '\0';
	   mbuf->buf[mbuf->len+1] = EOF;
	   mbuf->forward = mbuf->buf;
	   mbuf->back = mbuf->buf;
	   mbuf->type = 1;
	    mbuf->vtable = &vtable_base_buffer;
	   return mbuf;
}

base_buffer * base_buffer_from_string(char* instring){
/* create a buffer structure, and from the length of the
	input string create a buffer in memory the same size
	plus a few extra bytes for control characters. 
*/
	size_t in_len = strnlen(instring,128);
    base_buffer *mbuf = malloc(sizeof(*mbuf));
    mbuf->len = in_len;
    mbuf->buf = malloc(sizeof(char)*(mbuf->len+2));
/* copy the input string into the buffer, setup the control
	characters, and return the buffer
*/	
    strncpy(mbuf->buf,instring,in_len);
    mbuf->buf[mbuf->len] = '\0';
    mbuf->buf[mbuf->len+1] = EOF;
    mbuf->forward = mbuf->buf;
    mbuf->back = mbuf->buf;
    mbuf->type = 1;
	mbuf->vtable = &vtable_base_buffer;
    return mbuf;
}

base_buffer* base_buffer_from_file(FILE* infile){
/* buffer created and set to size of BUFFER_LENGTH */
	int b;
    base_buffer *mbuf = malloc(sizeof(*mbuf));
    
    mbuf->buf = malloc(sizeof(char)*BUFFER_LENGTH);
    
	/* exit with error, nothing given to function as input */
    if(infile == NULL ){
	   LOG_0("\033[0;31merror\033[0m%s","");
	   exit(-1);
    }

	/* 
	set buffer to associate with the FILE * infile for later use,
	as well as initialize control characters
	*/
    mbuf->work = infile;
    mbuf->forward = mbuf->buf;
    mbuf->back = mbuf->buf;
    mbuf->buf[HALF_BUFFER-1] = EOF;
    mbuf->buf[HALF_BUFFER-2] = '\0';
    mbuf->buf[BUFFER_LENGTH-1] = EOF;
    mbuf->buf[BUFFER_LENGTH-2] = '\0';
    mbuf->type = 0;
	mbuf->vtable = &vtable_base_buffer;
	/* 
	Call refresh_buffer to initialize buffer for first time
	*/
    fseek(mbuf->work, 0, SEEK_END);
    mbuf->len = (size_t) ftell(mbuf->work);
    fseek(mbuf->work, 0, SEEK_SET);
    refresh_buffer(mbuf,0);
    
	/* clear 2nd half of buffer until later */
    for(b=HALF_BUFFER;b<BUFFER_LENGTH-2;b++)
	   mbuf->buf[b]=' ';
    

    return mbuf;
}


base_buffer* base_buffer_from_filename(const char * name){
	/* allocate memory for buffer */
	int b;
    base_buffer *mbuf = malloc(sizeof(*mbuf));

    mbuf->buf = malloc(sizeof(char)*BUFFER_LENGTH);
	/* try to open file, if it exists continue otherwise
		exit with an error
	*/
    if((mbuf->work = fopen(name, "r")) == NULL ){
	   free(mbuf);
	   
		 return NULL;
	}
	/* initialize control characters and refresh buffer to initialize
		the buffer with data from the input file
	*/

    mbuf->forward = mbuf->buf;
    mbuf->back = mbuf->buf;
	mbuf->buf[HALF_BUFFER-1] = EOF;
	mbuf->buf[HALF_BUFFER-2] = '\0';
	mbuf->buf[BUFFER_LENGTH-1] = EOF;
	mbuf->buf[BUFFER_LENGTH-2] = '\0';
    mbuf->type = 0;
	mbuf->vtable = &vtable_base_buffer;
    fseek(mbuf->work, 0, SEEK_END);
    mbuf->len = (size_t) ftell(mbuf->work);
    fseek(mbuf->work, 0, SEEK_SET);
    refresh_buffer(mbuf,0);

	/* clear the lower half of the buffer */
    for(b=HALF_BUFFER;b<BUFFER_LENGTH-2;b++)
	   mbuf->buf[b]=' ';

    return mbuf;
}

int base_bgetchar(base_buffer* inbuf){
	/* Temporary used to return current character of buffer */
    int r;
/* Check buffer, either we have found EOF in which we may be at the end of half
	the buffer or we can increment the buffer 1 character instead
*/
    switch(*(inbuf->forward)){
	   case EOF:
/* 
	Check whether we found true EOF or just the token used to represent the end
	   of the buffer half.
*/
		  switch(inbuf->type){
			  /* Buffer Half has been found */
			 case 0:
			 /* either we found the upper buffer limit ... */
			 /* and if so we move the pointer to the proper start of next buffer */
					if(inbuf->forward == &inbuf->buf[HALF_BUFFER-1]){
					    refresh_lower_buffer(inbuf);
					    inbuf->forward = &inbuf->buf[HALF_BUFFER];
					}
			/* or we found the lower buffer limit */
					else if(inbuf->forward == &inbuf->buf[BUFFER_LENGTH-1]){
					    refresh_upper_buffer(inbuf);
					    inbuf->forward = &inbuf->buf[0];

					}
					else{
			/* True EOF has been found, so return it */
			case 1:
					    return EOF;
					}
				break;
		  }
/* we can increment the buffer and return the appropriate 
		  current character */
	   default:
		  r = *inbuf->forward;
		  inbuf->forward++;
		  return r;
		  break;
    }
	/* All else fails return the NULL character */
	return '\0';
}

int base_ungetchar(base_buffer* mbuf){
/* Check to see if we have found True EOF, the token EOF, or other */
    switch(mbuf->type){
	  /* Buffer Half has been found */
	   case 0:
		 /* either we found the upper buffer limit ... */
		 /* and if so we move the pointer to the proper start of next buffer */
		  if(mbuf->forward == &mbuf->buf[HALF_BUFFER] )
	    		mbuf->forward = &mbuf->buf[HALF_BUFFER-3];
		/* or we found the lower buffer limit */
		  else if(mbuf->forward == &mbuf->buf[0])
			 mbuf->forward = &mbuf->buf[BUFFER_LENGTH-3];
		  /* or we can move the buffer backwards 1 character and 
		  	return 
		  */
		  else
			 mbuf->forward--;
		  return *(mbuf->forward-1);
		  break;
		/* True EOF has been found, so we check if we can move
		  	 the buffer by one or not */
	   case 1:
	   /* we are at the start so go to the end */
		  if(mbuf->forward == mbuf->buf )
			 mbuf->forward = &mbuf->buf[mbuf->len-3];
		  /* we can just move backwards by 1 character and 
		  	return the current character */
		  else
			 mbuf->forward--;
		  return mbuf->forward == mbuf->buf ? *mbuf->forward:*(mbuf->forward-1);
		  break;
    }
	/* all else fails, return -1 */
    return -1;
}

inline void base_delete_buffer(base_buffer* mbuf){
	if(mbuf){
	    free(mbuf->buf);
	    mbuf->buf = NULL;
	    free(mbuf);
	    mbuf = NULL;
	}
}


inline void base_display_buffer(const base_buffer* inbuf){
    switch(inbuf->type){
	   case 0:
		  LOG_0("--MARK UP END--\n%s\n--MARK MIDDLE--\n",(char*)inbuf->buf);
		  LOG_0("%s\n--MARK LOW END--\n",&inbuf->buf[HALF_BUFFER]);
		  break;
	   case 1:
		  LOG_0("--MARK UP END--\n%s\n--MARK LOW END--\n",(char*)inbuf->buf);
		  break;
    }
}
inline void base_refresh_upper_buffer(base_buffer* inbuf){
    refresh_buffer(inbuf,0);
}

inline void base_refresh_lower_buffer(base_buffer* inbuf){
    refresh_buffer(inbuf,HALF_BUFFER);
}

inline void base_refresh_buffer(base_buffer* inbuf, const int start){
    static size_t amount;
	/* read more data into the buffer and store the amount read into 'amount' */
	if(inbuf->work == stdin){
		fgets(&inbuf->buf[start],(int)(HALF_BUFFER-2),inbuf->work);
		amount = strlen(&inbuf->buf[start]);
	}
	else
		amount=fread(&inbuf->buf[start],1,HALF_BUFFER-2,inbuf->work);	
    if( amount != HALF_BUFFER-2){
	   if(ferror(inbuf->work)!=0){
		  perror("\033[0;31merror\033[0m");
		  exit(-1);
	   }
	   /* if we found data then reset the control characters */
	   if(feof(inbuf->work)!=0){
		  if(amount >0){
			 	inbuf->buf[(unsigned long)start+amount]='\0';
			 	inbuf->buf[(unsigned long)start+amount+1]=EOF;
		 
		  }
		  else
			 ;
	   }
    }
  
}
