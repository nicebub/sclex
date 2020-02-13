CC= gcc-9
YACC= bison
DEBUG = -g
BUILDDIR= build
LIBDIR= lib
INCLUDEDIR= include
SRCDIR= src
NEWSRC = new
TESTDIR= test
UNITDIR=unit
vpath %.c ../../src/new/
vpath %.s src
vpath %.h ../../include/
vpath %.so lib
vpath %.la lib
VPATH= ../../src/new:../../include/new
CFLAGS= -I ../../$(INCLUDEDIR) -ansi -Wall -Wpedantic -pedantic-errors -Wno-comment 
UNITFLAGS = -I ../../$(INCLUDEDIR)/new/ -Wno-incompatible-pointer-types
#CFLAGS= -I $(INCLUDEDIR) -ansi
#CFLAGS= -I $(INCLUDEDIR) -std=c90
#CFLAGS= -I $(INCLUDEDIR) -std=c90 -Wpedantic
#CFLAGS= -I $(INCLUDEDIR) -no-pie
EXECS := $(patsubst %.c, %, $(wildcard *.c))
#OBJECTS := $(subst %, %.o $(EXECS))
UTESTABLES := $(wildcard $(SRCDIR)/new/*.c)
UTESTFILES :=  $(patsubst $(SRCDIR)/new/%.c,$(TESTDIR)/$(UNITDIR)/%_test.c,$(UTESTABLES))

UNITTESTS := $(patsubst %.c,%, $(UTESTFILES))

.PHONY: all clean run unit_tests $(BUILDDIR)
	
%.o: %.c %.h
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) -c $< 
all: $(EXECS)


baseset_test: baseset.o baseset_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@
intset_test: baseset.o intset.h intset.c intset_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@
chrset_test: baseset.o chrset.h chrset.c chrset_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@
vector_test: basevector.o vector_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@
intvector_test: basevector.o baseset.o intset.o intvector.h intvector.c intvector_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@
chrvector_test: basevector.o baseset.o chrset.o chrvector.h chrvector.c chrvector_test.c
	$(CC) $(DEBUG) $(CFLAGS) $(UNITFLAGS) $^ -o $@

clean:
	rm $(EXECS)  *.o;rm -rf *.dSYM