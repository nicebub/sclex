int run_dfa(struct _DFA *dfa, char* filename);
int smove(int s, char c);

int run_dfa(struct _DFA *dfa,char * filename){
    char stringbuf[100];
    buffer *dbuf;
    char *matched;
    char c;
    int s,d,e,last;
    dbuf = NULL;
    matched = NULL;
    if(dfa){
//	   printf("character 'a' as int %d and after 'a'-'0' %d\n",'a','a'-'0');
//	   printf("character '0' %d\n",'0');
	   dbuf = buffer_from_filename(filename);
	   s  = dfa->start-1;
	   last = 0;
	   c = getchar(dbuf);
	   while(is_ws(c) ==0){
		  c = getchar(dbuf);
	   }
   while(1){
//	  printf("dbuf->back == %c as char and %d as int\n",*dbuf->back, *dbuf->back);
		  d=0;
		  for(e=0;e<dfa->alphabet->used;e++){
			 if(dfa->alphabet->s[e] == c){
				d = e;
				break;
			 }
		  }
		  if(e >= dfa->alphabet->used || c == EOF || c== '\0'){
			 if(c != EOF && c!= '\0'){
				printf("Character not recognized in alphabet: %c\n",(c));
				if(matched != dbuf->back-1){
				    c = getchar(dbuf);
				    s = last;
				    continue;
				}
			 }
		  }
		  if(c != EOF && c != '\0')
			 s = dfa->Dtran[d][s]-1;
		  if(c == EOF || c == '\0' || s <0){
//				printf("put back character before %c\n",c);
			 if(matched !=NULL){
					dbuf->forward = matched+2;
					c = *(matched+1) ;
			 }
			 if(matched == NULL || matched == dbuf->back-1){
				if(is_in_iset(dfa->FFstates,s+1)!=0){
				    printf("Couldnt find a match with current lexeme\n");
				    return 1;
				}
				else{
				    printf("Matched, looking for pattern that matched\n");
				    for(int l=0;l<dfa->FFstates->used;l++){
					   if(is_in_iset(dfa->Fstates[l],s+1) ==0){
						  printf("Regular Expression %d Matched\n", l+1);
						  break;
					   }
				    }
				    return 0;
				}
			 }
//				printf("put back character after put back %c\n",c);
			 int ret;
			 ret = last;
			 last = s;
			 s = ret;
			 if(is_in_iset(dfa->FFstates,s+1)==0){
				int d =0;
				for(char* h= dbuf->back;h<=matched;h++){
				    stringbuf[d] = *h;
				    d++;
				}
				stringbuf[d] = '\0';
//				printf("currently in an accepting state %d with FINAL lexeme matched %s\n",s+1,stringbuf);
//				printf("Positions that could have gotten us here include\n");
//				display_set(dfa->Dstates->iset[s-1],0);
//				printf("those positions represent the letters\n");
//				printf("Matched, looking for pattern that matched\n");
				for(int l=0;l<dfa->FFstates->used;l++){
				    if(is_in_iset(dfa->Fstates[l],s+1) ==0){
					   printf("Regular Expression %d Matched\n", l+1);
					   printf("here is the action that is associated with this RE\n");
					   if(dfa->action_array[l] != NULL)
						  printf("%s\n",dfa->action_array[l]);
					   break;
				    }
				}
				dbuf->back = matched+1;
				if(c != EOF && c != '\0'){
				    s = 0;
				    continue;
				}
			 }
//			 printf("found EOF or NULL CHAR??? |%c|\n",c);
//			 printf("input past accepting state\n");
		  }
	  if((c != EOF && c != '\0') && is_in_iset(dfa->FFstates,s+1)==0){
		 last = s;
		 int d =0;
		 matched = dbuf->forward-1;
		 for(char* h= dbuf->back;h<=matched;h++){
			stringbuf[d] = *h;
			d++;
		 }
		 stringbuf[d] = '\0';
		 printf("currently in an accepting state %d with lexeme matched %s\n",s+1,stringbuf);
		 printf("Matched, looking for pattern that matched\n");
		 for(int l=0;l<dfa->FFstates->used;l++){
			if(is_in_iset(dfa->Fstates[l],s+1) ==0){
			    printf("Regular Expression %d Matched\n", l+1);
			    break;
			}
		 }
	  }

	  if(c == EOF || c == '\0'){
		 if(is_in_iset(dfa->FFstates,s+1)==0){
			printf("Matched, looking for pattern that matched\n");
			for(int l=0;l<dfa->FFstates->used;l++){
			    if(is_in_iset(dfa->Fstates[l],s+1) ==0){
				   printf("Regular Expression %d Matched\n", l+1);
				   break;
			    }
			}
			 return 0;
		 }
		 return 1;
	  }
	  c = getchar(dbuf);
	  while(is_ws(c) ==0){
		 c = getchar(dbuf);
	  }
	  
	   }
    }
    return 1;
}

int smove(int s, char c){
    return -1;
}
