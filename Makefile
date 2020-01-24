CC= /usr/bin/gcc
YACC= bison
DEBUG = -g
BUILDDIR= build
LIBDIR= lib
INCLUDEDIR= include
SRCDIR= src
NEWSRC = new
TESTDIR= test
vpath %.c src
vpath %.s src
vpath %.h include
vpath %.so lib
vpath %.la lib
VPATH= src:include
CFLAGS= -I $(INCLUDEDIR) -Wno-comment
#CFLAGS= -I $(INCLUDEDIR) -no-pie

FILES := $(subst $(SRCDIR)/,,$(wildcard src/*.c))
AFILES := $(subst $(SRCDIR)/,,$(wildcard src/*.s))
OUTFILE := $(INCLUDEDIR)/outfile.in
HFILES:= $(subst $(INCLUDEDIR)/,,$(wildcard $(INCLUDEDIR)/*.h))
SOURCES := $(patsubst %,$(SRCDIR)/%,$(FILES))
OBJECTS := $(patsubst %.c,$(BUILDDIR)/%.o,$(FILES))
ASSEMBLYS := $(patsubst %.s,$(BUILDDIR)/%.o,$(AFILES))
DEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(FILES))
NEWFILES := $(wildcard $(SRCDIR)/$(NEWSRC)/*.c)
NEWCLASSOBJS := $(patsubst $(SRCDIR)/$(NEWSRC)/%.c, $(BUILDDIR)/%.o, $(NEWFILES))
NDEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(NEWFILES))

.PHONY: all clean run $(BUILDDIR)
	
$(NEWCLASSOBJS): $(NEWFILES) | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/%.o: $(SRCDIR)/$(NEWSRC)/%.c $(INCLUDEDIR)/%.h $(BUILDDIR)/%.d| $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/%.d: $(SRCDIR)/$(NEWSRC)/%.c $(INCLUDEDIR)/%.h 
	$(CC) $(CFLAGS) $(DEBUG) -MM $< -o $@
-include $(NDEPS)

all: $(BUILDDIR)/sclex
	
$(BUILDDIR):
	[ -d $(BUILDDIR) ] || mkdir -p $(BUILDDIR)
sclex.yy.c: $(INCLUDEDIR)/outfile.in $(TESTDIR)/lex.l
	$(BUILDDIR)/sclex $(TESTDIR)/lex.l
$(OUT): $(OUTFILE)

$(OUTFILE):
	
$(BUILDDIR)/%.o: %.s | $(BUILDDIR)
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
$(BUILDDIR)/%.o: %.c $(INCLUDEDIR)/%.h $(BUILDDIR)/%.d| $(BUILDDIR)
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
$(BUILDDIR)/%.d: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h 
	$(CC) $(CFLAGS) $(DEBUG) -MM $< -o $@
-include $(DEPS)
$(BUILDDIR)/sclex: $(ASSEMBLYS) $(OBJECTS) $(OUTFILE)
	$(CC) $(CFLAGS) $(DEBUG) $(ASSEMBLYS) $(OBJECTS) -o $@
run:
	./build/sclex test/expr.l

lex_driver: test/lex_test.c sclex.yy.c $(BUILDDIR)/basebuffer.o
	$(CC) $(CFLAGS) $(DEBUG) -g $^ -o $@
 clean:
	rm $(BUILDDIR)/bufferdriver $(BUILDDIR)/hashdriver $(BUILDDIR)/sclex lex_driver sclex.yy.c $(BUILDDIR)/*.o;rm -rf *.dSYM; rmdir $(BUILDDIR)
