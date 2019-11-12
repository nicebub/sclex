#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include "sof.h"
#define NUM_ARGS_NECESARRY 2
#define READ_ONLY "r"
#define ERR_STR "Error"

int main(int argc, char const ** argv){
	if(argc != NUM_ARGS_NECESARRY){
		usage();
		return EXIT_FAILURE;
	}
	FILE* fp = fopen(argv[1],READ_ONLY);
	if(fp == NULL){
		perror(ERR_STR);
		usage();
		return EXIT_FAILURE;
	}
	size_t file_start = ftell(fp);
	fseek(fp,0,SEEK_END);
	size_t file_end = ftell(fp);
	rewind(fp);
	size_t file_size=file_end-file_start;
	char * serial = malloc(file_size);
	fread(serial,1,file_size,fp);
	fclose(fp);
	printf("%s\n",serial);
	printf("length of file: %lu bytes\n",file_size);
	free(serial);
	serial = NULL;
	return EXIT_SUCCESS;
}




inline void usage(void){
	printf("Usage: sof [filename] ** a file to serialize\n");	
}