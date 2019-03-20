#include "buffer.h"

void refresh_upper_buffer(buffer* inbuf);
void refresh_lower_buffer(buffer* inbuf);
void refresh_buffer(buffer* inbuf, const int start);


int bgetchar(buffer* inbuf){
    int r;
    switch(*(inbuf->forward)){
	   case EOF:
//		  printf("found EOF\n");
		  switch(inbuf->type){
			 case 0:
					if(inbuf->forward == &inbuf->buf[HALF_BUFFER-1]){
					    refresh_lower_buffer(inbuf);
					    inbuf->forward = &inbuf->buf[HALF_BUFFER];
					}
					else if(inbuf->forward == &inbuf->buf[BUFFER_LENGTH-1]){
					    refresh_upper_buffer(inbuf);
					    inbuf->forward = &inbuf->buf[0];

					}
					else{
			 //			 printf("POTENTIAL END OF STREAM\n");
			case 1:
					    return EOF;
					}
				break;
		  }
	   default:
		  r = *inbuf->forward;
		  inbuf->forward++;
		  return r;
		  break;
    }
	return '\0';
}
int ungetchar(buffer* mbuf){
    switch(mbuf->type){
	   case 0:
		  if(mbuf->forward == &mbuf->buf[HALF_BUFFER] )
	    		mbuf->forward = &mbuf->buf[HALF_BUFFER-3];
		  else if(mbuf->forward == &mbuf->buf[0])
			 mbuf->forward = &mbuf->buf[BUFFER_LENGTH-3];
		  else
			 mbuf->forward--;
		  return *mbuf->forward;
		  break;
	   case 1:
		  if(mbuf->forward == mbuf->buf )
			 mbuf->forward = &mbuf->buf[mbuf->len-3];
		  else
			 mbuf->forward--;
		  return *mbuf->forward;
		  break;
    }
    return -1;
}

buffer * buffer_from_string(char* instring){
    buffer *mbuf = malloc(sizeof(*mbuf));
    mbuf->len = (int)strlen(instring);
    mbuf->buf = malloc(sizeof(char)*(mbuf->len+2));
    strcpy(mbuf->buf,instring);
    mbuf->buf[mbuf->len] = '\0';
    mbuf->buf[mbuf->len+1] = EOF;
    mbuf->forward = mbuf->buf;
    mbuf->back = mbuf->buf;
    mbuf->type = 1;
    return mbuf;

}

buffer* buffer_from_file(FILE* infile){
    buffer *mbuf = malloc(sizeof(*mbuf));
    
    mbuf->buf = malloc(sizeof(char)*BUFFER_LENGTH);
    
    if(infile == NULL ){
	   printf("\033[0;31merror\033[0m");
	   exit(-1);
    }
//    printf("using buffer with file\n");
    mbuf->work = infile;
    mbuf->forward = mbuf->buf;
    mbuf->back = mbuf->buf;
    mbuf->buf[HALF_BUFFER-1] = EOF;
    mbuf->buf[HALF_BUFFER-2] = '\0';
    mbuf->buf[BUFFER_LENGTH-1] = EOF;
    mbuf->buf[BUFFER_LENGTH-2] = '\0';
    mbuf->type = 0;
    refresh_buffer(mbuf,0);
    
    for(int b=HALF_BUFFER;b<BUFFER_LENGTH-2;b++)
	   mbuf->buf[b]=' ';
    
    return mbuf;
}
buffer* buffer_from_filename(const char * name){

    buffer *mbuf = malloc(sizeof(*mbuf));

    mbuf->buf = malloc(sizeof(char)*BUFFER_LENGTH);

    if((mbuf->work = fopen(name, "r")) == NULL ){
		perror("\033[0;31merror\033[0m");
		exit(-1);
	}
//	printf("opened file\n");

    	mbuf->forward = mbuf->buf;
    	mbuf->back = mbuf->buf;
	mbuf->buf[HALF_BUFFER-1] = EOF;
	mbuf->buf[HALF_BUFFER-2] = '\0';
	mbuf->buf[BUFFER_LENGTH-1] = EOF;
	mbuf->buf[BUFFER_LENGTH-2] = '\0';
    	mbuf->type = 0;
    	refresh_buffer(mbuf,0);

    for(int b=HALF_BUFFER;b<BUFFER_LENGTH-2;b++)
	   mbuf->buf[b]=' ';

    return mbuf;
}

inline void delete_buffer(buffer* mbuf){
	if(mbuf){
	    free(mbuf->buf);
	    mbuf->buf = NULL;
	    free(mbuf);
	    mbuf = NULL;
	}
}

inline void display_buffer(const buffer* inbuf){
    switch(inbuf->type){
	   case 0:
		  printf("--MARK UP END--\n%s\n--MARK MIDDLE--\n",(char*)inbuf->buf);
		  printf("%s\n--MARK LOW END--\n",&inbuf->buf[HALF_BUFFER]);
		  break;
	   case 1:
		  printf("--MARK UP END--\n%s\n--MARK LOW END--\n",(char*)inbuf->buf);
		  break;
    }
}


inline void refresh_upper_buffer(buffer* inbuf){
    refresh_buffer(inbuf,0);
}

inline void refresh_lower_buffer(buffer* inbuf){
    refresh_buffer(inbuf,HALF_BUFFER);
}

inline void refresh_buffer(buffer* inbuf, const int start){
    static size_t amount;
    if((amount=fread(&inbuf->buf[start],1,HALF_BUFFER-2,inbuf->work)) != HALF_BUFFER-2){
//	   printf("charcters matched %zu\n",amount);
	   if(ferror(inbuf->work)!=0){
		  perror("\033[0;31merror\033[0m");
		  exit(-1);
	   }
	   if(feof(inbuf->work)!=0){
		  if(amount >0){
//			 	printf("FOUND END OF FILE\n");
			 	inbuf->buf[start+amount]='\0';
			 	inbuf->buf[start+amount+1]=EOF;
//			 printf("start+amount+2: %lu\n",start+amount+2);
//			 printf("start+HALF_BUFFER-2: %d\n",start+HALF_BUFFER-2);
			 
		  }
		  else
			 ;
//			 printf("ALREADY REACHED EOF\n");
	   }
    }
    
}
