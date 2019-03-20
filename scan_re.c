#include "scan_re.h"

struct _ta *parse_file(buffer * mbuf,char *c, struct _lfile*);
char* aux(buffer* mbuf, char*c);

void display_memstats(void);
void cleanup_lex(buffer** mbuf,struct _lfile* lexfile,struct _DFA** dfa);


int main(int argc, const char ** argv){
    
    
    
/*  lexfile structure to hold FILE pointer to .l file opened to parse*/
    struct _lfile lexfile;
/*  buffer pointer used for buffer of .l file opened*/
    static buffer * mbuf;
/* DFA structure pointer to point to DFA record created with this lexer */
    struct _DFA *dfa;
/* the output lexical analyzer source file  FILE pointer */
/* used as current character on input and incremented with getchar routine */
    static char c;
/* currently stores result after running the created DFA on the opened source file */
 //   int result;

    
    
/* Initialize Variables */
    c ='\0';
    dfa = NULL;
    mbuf = NULL;
    lexfile.decs = NULL;
    lexfile.fpos = NULL;
    lexfile.tree = NULL;


/* current looks for 2 filenames on the command line
   first filename is for the .l file, the 2nd is
 for the .or regex file */
    if(argc != 2){
		lex_error(26);
		exit(-1);
	}
//    printf("check mem at beginning of scan\n");
//  display_memstats();
    
    
/* initialize buffer from 1st filename given */
    mbuf = buffer_from_filename(argv[1]);

/* If the file is a .l file, this will start to parse the
 file*/
    parse_file(mbuf,&c,&lexfile);

    
    //    printf("check mem after parse file\n");
//    display_memstats();
//    printf("Displaying Parse Trees before generating DFA\n");
  //  display_tree(lexfile.tree->atop);
//    printf("\n");
    if(lexfile.tree && lexfile.fpos){
	   	dfa = generate_dfa(lexfile.tree,lexfile.fpos,lexfile.tree->alphabet);
//	   printf("check mem after gnerate dfa\n");
//	   display_memstats();
//	   	result = run_dfa(dfa,(char*)argv[2]);
//	   printf("check mem after running dfa\n");
//	   display_memstats();
	//   	printf("here is the result from running the dfa: 0 is yes 1 is no: %d\n",result);
	   generate_output(lexfile,dfa);
    }
    cleanup_lex(&mbuf,&lexfile,&dfa);
    display_memstats();
    return 0;
}

struct _ta *parse_file(buffer * mbuf,char *c, struct _lfile * file){
    if(*c != EOF  && (*c = getchar(mbuf))!= EOF){
	   if(*c != '%'){
		  lex_error(1);
		  return NULL;
	   }
	   *c = getchar(mbuf);
	   if(*c != '{'){
		  lex_error(1);
		  return NULL;
	   }
	  file->decs = declarations(mbuf,c,file);
	   while((is_ws(*c) ==0) || *c == '\n')
		  *c = getchar(mbuf);
	   if(*c != '%'){
		  lex_error(2);
		  return NULL;
	   }
	   *c = getchar(mbuf);
	   if(*c != '%'){
		  lex_error(2);
		  return NULL;
	   }
	   *c = getchar(mbuf);
	   while((is_ws(*c) ==0) || *c == '\n')
		  *c = getchar(mbuf);
	   *c = ungetchar(mbuf);
	   file->tree =  translations(mbuf,c,file);
	   while((is_ws(*c) ==0) && *c != '\n')
		  *c = getchar(mbuf);
	   if(*c != '%'){
		  lex_error(3);
		  return NULL;
	   }
	   *c = getchar(mbuf);
	   if(*c != '%'){
		  lex_error(3);
		  return NULL;
	   }
    }
    return NULL;
}

char* aux(buffer* mbuf, char*c){
    return NULL;
}

void display_memstats(void){
    int tnm = tnum_created();
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("+ value		|	ta	|	t	|	sa	|	s		+\n");
    printf("+ created	|	%d	|	%d	|	%d	|	%d		+\n",atnum_created(),tnm,asnum_created(),snum_created());
    printf("+ deleted	|	%d	|	%d	|	%d	|	%d		+\n",atnum_deleted(),tnum_deleted(),asnum_deleted(),snum_deleted());
    printf("+Total Loss	|	%d	|	%d	|	%d	|	%d		+\n", \
		 atnum_created()-atnum_deleted(),tnm-tnum_deleted(), \
		 asnum_created()-asnum_deleted(),snum_created()-snum_deleted());
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("*note - ta is tree arrays, t are tree nodes, sa are set \n");
    printf("*note - arrays, and s are sets themselvese\n\n");
}

void cleanup_lex(buffer** mbuf,struct _lfile* lexfile,struct _DFA** dfa){
    delete_buffer(*mbuf);
    free((*lexfile).decs);
    (*lexfile).decs = NULL;
    for(int y=0;y<(*lexfile).num_defs;y++){
	   delete_buffer((*lexfile).defbuf[y]);
	   (*lexfile).defbuf[y] = NULL;
    }
    free((*lexfile).defbuf);
    (*lexfile).defbuf = NULL;
    delete_ta((*lexfile).tree);
    delete_iseta((*lexfile).fpos);
    delete_dfa(*dfa);
    *dfa = NULL;
    (*lexfile).fpos = NULL;
    (*lexfile).tree = NULL;
    *mbuf = NULL;

}
