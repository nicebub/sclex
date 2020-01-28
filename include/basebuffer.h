#ifndef _BASE_BUFFER_CLASS_H
#define _BASE_BUFFER_CLASS_H

#include <stdio.h>
/* Buffer is 8K Bytes */
#define BUFFER_LENGTH 8196
/* middle of buffer can be found here */
#define HALF_BUFFER BUFFER_LENGTH / 2
#define getchar(inf) bgetchar(inf)

#define buffer_from_filename base_buffer_from_filename
#define buffer_from_string base_buffer_from_string
#define buffer_from_file base_buffer_from_file

typedef struct _base_buffer base_buffer;
typedef struct _base_buffer_vtable base_buffer_vtable;
typedef struct _base_buffer buffer;

struct _base_buffer_vtable {

	void (*refresh_upper_buffer)(base_buffer* inbuf);

	void (*refresh_lower_buffer)(base_buffer* inbuf);

	void (*refresh_buffer)(base_buffer* inbuf, const int start);

	int (*bgetchar)(base_buffer* inf);

	int (*ungetchar)(base_buffer* inf);

	void (*delete_buffer)(base_buffer*);

	void (*display_buffer)(const base_buffer*);	

};
struct _base_buffer{
	base_buffer_vtable *vtable;
    char *buf;
    char *forward;
    char *back;
    FILE* work;
    int type;
    size_t len;


};
base_buffer* new_base_buffer(size_t size);

base_buffer* base_buffer_from_file(FILE*);

base_buffer* base_buffer_from_filename(const char * name);

base_buffer* base_buffer_from_string(char* instring);

void init_base_buffer_vtable(void);

void refresh_upper_buffer(base_buffer* inbuf);

void refresh_lower_buffer(base_buffer* inbuf);

void refresh_buffer(base_buffer* inbuf, const int start);

int bgetchar(base_buffer* inf);

int ungetchar(base_buffer* inf);

void delete_buffer(base_buffer*);

void display_buffer(const base_buffer*);	



void base_refresh_upper_buffer(base_buffer* inbuf);

void base_refresh_lower_buffer(base_buffer* inbuf);

void base_refresh_buffer(base_buffer* inbuf, const int start);

int base_bgetchar(base_buffer* inf);

int base_ungetchar(base_buffer* inf);

void base_delete_buffer(base_buffer*);

void base_display_buffer(const base_buffer*);	



#endif
