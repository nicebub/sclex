CC= /usr/bin/gcc
YACC= bison
BUILDDIR= build
LIBDIR= lib
INCLUDEDIR= include
SRCDIR= src
TESTDIR= test
vpath %.c src
vpath %.s src
vpath %.h include
vpath %.so lib
vpath %.la lib
VPATH= src:include
CFLAGS= -I $(INCLUDEDIR)
#CFLAGS= -I $(INCLUDEDIR) -no-pie

FILES := $(subst $(SRCDIR)/,,$(wildcard src/*.c))
AFILES := $(subst $(SRCDIR)/,,$(wildcard src/*.s))
OUTFILE := $(INCLUDEDIR)/outfile.in
HFILES:= $(subst $(INCLUDEDIR)/,,$(wildcard $(INCLUDEDIR)/*.h))
SOURCES := $(patsubst %,$(SRCDIR)/%,$(FILES))
OBJECTS := $(patsubst %.c,$(BUILDDIR)/%.o,$(FILES))
ASSEMBLYS := $(patsubst %.s,$(BUILDDIR)/%.o,$(AFILES))
DEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(FILES))
	
.PHONY: all clean run $(BUILDDIR)
	
all: $(BUILDDIR)/sclex
	
$(BUILDDIR):
	[ -d $(BUILDDIR) ] || mkdir -p $(BUILDDIR)
sclex.yy.c: $(INCLUDEDIR)/outfile.in $(TEST)/lex.l
	$(BUILDDIR)/sclex $(TESTDIR)/lex.l
$(OUT): $(OUTFILE)

$(OUTFILE):
	
$(BUILDDIR)/%.o: %.s | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/%.o: %.c $(INCLUDEDIR)/%.h $(BUILDDIR)/%.d| $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILDDIR)/%.d: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h 
	$(CC) $(CFLAGS) $(DEBUG) -MM $< -o $@
-include $(DEPS)
$(BUILDDIR)/sclex: $(ASSEMBLYS) $(OBJECTS) $(OUTFILE)
	$(CC) $(CFLAGS) $(DEBUG) $(ASSEMBLYS) $(OBJECTS) -o $@
run:
	./build/sclex test/expr.l

clean:
	rm $(BUILDDIR)/bufferdriver $(BUILDDIR)/hashdriver $(BUILDDIR)/sclex $(BUILDDIR)/lex_driver $(SRCDIR)/sclex.yy.c $(BUILDDIR)/*.o *.dSYM; rmdir $(BUILDDIR)
