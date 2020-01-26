#ifndef MTYPE_H
#define MTYPE_H
#include <stdlib.h>
#include <string.h>

/* The initial size of a type array  ? */
#define TINIT_SIZE 16

/* The amount of components to start with ? */
#define TRSIZE_AMT 10


/* Structure Definition

	_type defines a 'type' which can have a 'name'
		and 'value', as well as be made up of other sub-types

    char * name: the character string name of the type
    int value: its uniq ID 
    struct _type *components: NULL or an array of sub-types

*/
struct _type {
    char * name;
    int value;
    struct _type *components;
};

/* Structure Definition

	_tsys defines a 'type' system which can have an array of 'types'
		it has a size and amount really used, just in case.

    struct _type ** type: the type array that holds all of the types
    int size: the size of the array
    int used: how many types are there ??

*/
struct _tsys {
    // array of available types
    struct _type ** type;
    int size;
    int used;
};

#endif
