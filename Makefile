CC = /usr/bin/gcc


all: hashdriver sclex bufferdriver lex_driver
	
tree.o: tree.c tree.h
	$(CC) -g -c tree.c	
	
hash.o: hash.c hash.h
	$(CC) -g -c hash.c	
	
type.o: type.c type.h
	$(CC) -g -c type.c	

buffer.o: buffer.c buffer.h
	$(CC) -g -c buffer.c	

funcs.o: funcs.c funcs.h
	$(CC) -g -c funcs.c
	
retodfa.o: retodfa.c retodfa.h
	$(CC) -g -c retodfa.c

sclex_driver.o: sclex_driver.c sclex_driver.h
	$(CC) -g -c sclex_driver.c

set.o: set.c set.h
	$(CC) -g -c set.c
	
dfa.o: dfa.c dfa.h
	$(CC) -g -c dfa.c
	
gen.o: gen.c gen.h
	$(CC) -g -c gen.c

decs.o: decs.c decs.h
	$(CC) -g -c decs.c

translation.o: translation.c translation.h
	$(CC) -g -c translation.c
	
allregex.o: allregex.c allregex.h
	$(CC) -g -c allregex.c

lex_error.o: lex_error.c lex_error.h
	$(CC) -g -c lex_error.c

regex.o: regex.c regex.h
	$(CC) -g -c regex.c

expror.o: expror.c expror.h
	$(CC) -g -c expror.c

exprcat.o: exprcat.c exprcat.h
	$(CC) -g -c exprcat.c

expr.o: expr.c expr.h
	$(CC) -g -c expr.c

charset.o: charset.c charset.h
	$(CC) -g -c charset.c
	
escape.o: escape.c escape.h
	$(CC) -g -c escape.c
sclex.yy.c: outfile.in lex.l
	./sclex lex.l


bufferdriver: driver.c buffer.o type.o hash.o tree.o funcs.o set.o
	$(CC) -g -o bufferdriver driver.c buffer.o tree.o hash.o type.o funcs.o set.o
	
hashdriver: hashdriver.c hash.o funcs.o
	$(CC) -g -o hashdriver hashdriver.c hash.o funcs.o
	
sclex: sclex_driver.o buffer.o funcs.o tree.o retodfa.o hash.o set.o dfa.o gen.o decs.o translation.o allregex.o lex_error.o regex.o expror.o exprcat.o expr.o charset.o escape.o
	$(CC) -g -o sclex sclex_driver.o buffer.o funcs.o tree.o retodfa.o hash.o set.o dfa.o gen.o decs.o translation.o allregex.o lex_error.o regex.o expror.o exprcat.o expr.o charset.o escape.o

lex_driver: lex_test.c sclex.yy.c buffer.o
	$(CC) -g -o lex_driver lex_test.c sclex.yy.c buffer.o
	
clean:
	rm bufferdriver hashdriver sclex lex_driver sclex.yy.c *.o; rm -r *.dSYM