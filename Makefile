#CC= /usr/bin/gcc
#CFLAGS=
YACC= bison
#FILES= sclex_driver.c
BUILDDIR= build
LIBDIR= lib
INCLUDEDIR= include
SRCDIR= src
TESTDIR= test
vpath %.c src
vpath %.h include
VPATH= src:include
CFLAGS= -I $(INCLUDEDIR)
FILES := $(subst $(SRCDIR)/,,$(wildcard src/*.c))
HFILES=  $(INCLUDEDIR)/*.h
#DEBUG="-g"
SOURCES := $(patsubst %,$(SRCDIR)/%,$(FILES))
	
#HEADERS := $(patsubst %,$(INCLUDEDIR)/%,$)

OBJECTS := $(patsubst %.c,$(BUILDDIR)/%.o,$(FILES))
DEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(FILES))
	
.PHONY: all clean $(BUILDDIR)
	
all: $(BUILDDIR)/sclex
	
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	
	
sclex.yy.c: $(INCLUDEDIR)/outfile.in $(TEST)/lex.l
	$(BUILDDIR)/sclex $(TESTDIR)/lex.l
	
#%.o: $(FILES) $(INCLUDEDIR)/*.h
#	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
$(BUILDDIR)/%.o: %.c $(INCLUDEDIR)/%.h $(BUILDDIR)/%.d| $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILDDIR)/%.d: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h 
	$(CC) $(CFLAGS) $(DEBUG) -MM $< -o $@
	
-include $(DEPS)
	
#$(OBJECTS):  | $(BUILDDIR)
	
	
$(BUILDDIR)/sclex: $(OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@
	
	
clean:
	rm $(BUILDDIR)/bufferdriver $(BUILDDIR)/hashdriver $(BUILDDIR)/sclex $(BUILDDIR)/lex_driver $(SRCDIR)/sclex.yy.c $(BUILDDIR)/*.o *.dSYM; rmdir $(BUILDDIR)
