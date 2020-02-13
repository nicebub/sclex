#ifndef _CHRVEC_H
#define _CHRVEC_H

#include "basevector.h"
#include "chrset.h"
typedef struct _char_vector char_vector;

struct _char_vector {
	base_vector super;
	char ** values;
};

char_vector* new_char_vector(size_t size);

void char_delete_vector(char_vector* vector);	
void char_add_to_vector(char_set* data,char_vector * vector);
void char_display_vector(char_vector* vector);

#endif