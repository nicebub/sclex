CC = /usr/bin/gcc
#DEBUG="-g"

all: sclex
	
tree.o: tree.c tree.h
	$(CC) $(DEBUG) -c tree.c	
	
hash.o: hash.c hash.h
	$(CC) $(DEBUG) -c hash.c	
	
type.o: type.c type.h
	$(CC) $(DEBUG) -c type.c	

buffer.o: buffer.c buffer.h
	$(CC) $(DEBUG) -c buffer.c	

funcs.o: funcs.c funcs.h
	$(CC) $(DEBUG) -c funcs.c
	
retodfa.o: retodfa.c retodfa.h
	$(CC) $(DEBUG) -c retodfa.c

sclex_driver.o: sclex_driver.c sclex_driver.h
	$(CC) $(DEBUG) -c sclex_driver.c

set.o: set.c set.h
	$(CC) $(DEBUG) -c set.c
	
dfa.o: dfa.c dfa.h
	$(CC) $(DEBUG) -c dfa.c
	
gen.o: gen.c gen.h
	$(CC) $(DEBUG) -c gen.c

decs.o: decs.c decs.h
	$(CC) $(DEBUG) -c decs.c

translation.o: translation.c translation.h
	$(CC) $(DEBUG) -c translation.c
	
allregex.o: allregex.c allregex.h
	$(CC) $(DEBUG) -c allregex.c

lex_error.o: lex_error.c lex_error.h
	$(CC) $(DEBUG) -c lex_error.c

regex.o: regex.c regex.h
	$(CC) $(DEBU) -c regex.c

expror.o: expror.c expror.h
	$(CC) $(DEBUG) -c expror.c

exprcat.o: exprcat.c exprcat.h
	$(CC) $(DEBUG) -c exprcat.c

expr.o: expr.c expr.h
	$(CC) $(DEBUG) -c expr.c

charset.o: charset.c charset.h
	$(CC) $(DEBUG) -c charset.c
	
escape.o: escape.c escape.h
	$(CC) $(DEBUG) -c escape.c
sclex.yy.c: outfile.in lex.l
	./sclex lex.l


bufferdriver: driver.c buffer.o type.o hash.o tree.o funcs.o set.o
	$(CC) $(DEBUG) -o $@ driver.c buffer.o tree.o hash.o type.o funcs.o set.o
	
hashdriver: hashdriver.c hash.o funcs.o
	$(CC) $(DEBUG) -o $@ hashdriver.c hash.o funcs.o
	
sclex: sclex_driver.o buffer.o funcs.o tree.o retodfa.o hash.o set.o dfa.o gen.o decs.o translation.o allregex.o lex_error.o regex.o expror.o exprcat.o expr.o charset.o escape.o
	$(CC) $(DEBUG) -o $@ sclex_driver.o buffer.o funcs.o tree.o retodfa.o hash.o set.o dfa.o gen.o decs.o translation.o allregex.o lex_error.o regex.o expror.o exprcat.o expr.o charset.o escape.o

lex_driver: lex_test.c sclex.yy.c buffer.o
	$(CC) $(DEBUG) -o $@ lex_test.c sclex.yy.c buffer.o
test: bufferdriver hashdriver lex_driver
	
	
clean:
	rm bufferdriver hashdriver sclex lex_driver sclex.yy.c *.o; rm -r *.dSYM
