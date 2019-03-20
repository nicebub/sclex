#include "translation.h"

struct _ta* translations(buffer* mbuf, char*c, struct _lfile *file){
    file->tree = regexpset(mbuf,c,file);
//    display_set(file->tree->alphabet,1);
    file->fpos = create_iseta(SETSIZE);
    if(file->fpos == NULL){
	   lex_error(4);
	   return NULL;
    }
    for(int r=0;r<file->fpos->size;r++){
	   file->fpos->iset[r] = create_iset(file->fpos->size);
	   if(file->fpos->iset[r] == NULL){
		  lex_error(5);
		  return NULL;
	   }
    }
    for(int r=file->fpos->size;r<SETSIZE;r++)
	   file->fpos->iset[r] = NULL;
    file->fpos->used = file->fpos->size;
    printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");
    for(int h=0;h<file->tree->used;h++){
		  printf("REGEX\n");
		  display_tree(file->tree->t[h]);
		  printf("\n");
    }
    printf("\n");
    followpos(&file->fpos,&file->tree->atop);
    printf("\n");
    printf("ITS ALPHABET\n");
    display_set(file->tree->alphabet,1);
    printf("=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=\n");
/*    printf("all the followpos sets computed\n");
    for(int j=0;j<file->fpos->used;j++){
	   if(file->fpos->iset[j]->used >0)
		  display_set(file->fpos->iset[j],0);
    }*/

    return file->tree;

}
