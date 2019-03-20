#ifndef BUFFER_PAIR_H
#define BUFFER_PAIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 8196
#define HALF_BUFFER BUFFER_LENGTH / 2
#define getchar(inf) bgetchar(inf)


typedef struct _buffer{
    char *buf;
    char *forward;
    char *back;
    FILE* work;
    int type;
    int len;
} buffer;


int bgetchar(buffer* inf);
int ungetchar(buffer* inf);


buffer* buffer_from_file(FILE*);
buffer* buffer_from_filename(const char * name);
buffer * buffer_from_string(char* instring);
void delete_buffer(buffer*);
void display_buffer(const buffer*);



#endif
