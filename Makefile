ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	CLEANDIR = rmdir
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
#	GENERATE_RUNNER= tools/genrunners.sh
endif

.PHONY: all clean test run lex_driver #regen

vpath %.c src
vpath %.s src
vpath %.h include
vpath %.so lib
vpath %.la lib

COMPILER=gcc-9

PATHU = unity/src/
PATHS = src/
PATHI = include/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

EXAMPLES = example/
EXEC = $(PATHB)sclex

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

BASE_SRCT = $(wildcard $(PATHT)*base*.c)
SRCT = $(wildcard $(PATHT)*[!b][!a][!s][!e]*.c)

SRC_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.c))
ASSEM_FILES := $(subst $(PATHS),,$(wildcard $(PATHS)*.s))
OUTFILE := $(PATHI)outfile.in
HEAD_FILES:= $(subst $(PATHI),,$(wildcard $(PATHI)*.h))
SOURCES := $(patsubst %,$(PATHS)%,$(SRC_FILES))
OBJECTS := $(patsubst %.c,$(PATHO)%.o,$(SRC_FILES))
ASSEMBLYS := $(patsubst %.s,$(PATHO)%.o,$(ASSEM_FILES))
DEPS := $(patsubst %.c, $(PATHD)%.d,$(SRC_FILES))
#NEWFILES := $(wildcard $(PATHS)$(NEWSRC)/*.c)
#NEWCLASSOBJS := $(patsubst $(PATHS)$(NEWSRC)/%.c, $(PATHB)%.o, $(NEWFILES))
#NDEPS := $(patsubst %.c,, $(BUILDDIR)/%.D,$(NEWFILES))

COMPILE=$(COMPILER) -c
LINK=$(COMPILER)
DEPEND=$(COMPILER) -MM -MG -MF
CFLAGS=-I. -I$(PATHI) -I$(PATHU) -I$(PATHS) -ansi -Wall -Wpedantic -pedantic-errors -Wno-comment -Wno-incompatible-pointer-types
CFLAGS += -g -Wno-unused-variable
TFLAGS = $(CFLAGS) -DTEST
BASE_RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(BASE_SRCT) )
RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

all: $(BUILD_PATHS) $(EXEC)

clean: test_clean
	$(CLEANUP) sclex.yy.c
	$(CLEANUP) $(PATHB)sclex.yy.c
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHD)*.d
	$(CLEANUP) $(PATHB)sclex
	$(CLEANUP) $(PATHB)lex_driver
	$(CLEANUP) -rf $(PATHB)lex_driver.dSYM
	$(CLEANDIR) $(PATHD)
	$(CLEANDIR) $(PATHO)
	$(CLEANDIR) $(PATHR)
	$(CLEANDIR) $(PATHB)
test_clean:
	$(CLEANUP) $(PATHT)*_Runner.c

.PRECIOUS: $(PATHB)Testbase%_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHB)Test%set_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHB)Test%vector_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt


$(PATHD)%.d:: %.c %.h $(BUILD_PATHS)
	$(CC) $(CFLAGS) $(DEBUG) -MM -MG $< -o $@
#-include $(DEPS)

$(PATHB)sclex.yy.c:: $(EXAMPLES)lex.l
	$(EXEC) $<
	mv sclex.yy.c $(PATHB)

#$(OUTFILE):

$(PATHO)%.o:: %.s
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

#$(PATHO)%.o:: %.c $(PATHI)%.h $(PATHD)%.d
#	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(EXEC):: $(BUILD_PATHS) $(ASSEMBLYS) $(OBJECTS) $(OUTFILE) #$(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) $(ASSEMBLYS) $(OBJECTS) -o $@

run: $(EXEC)
	./$(EXEC) $(EXAMPLES)expr.l

lex_driver: $(EXEC) $(PATHB)lex_driver

$(PATHB)lex_driver: $(EXAMPLES)lex_test.c $(PATHB)sclex.yy.c
	$(CC) $(CFLAGS) $(DEBUG) $^ -o $@

#regen:
#	$(GENERATE_RUNNER)

test: $(BUILD_PATHS) $(BASE_RESULTS) $(RESULTS)
#	@echo "RESULTS: $(RESULTS)"
#	@echo "BASE_RESULTS: $(BASE_RESULTS)"
#	@echo "BASE_SRCT $(BASE_SRCT)"
#	@echo "SRCT $(SRCT)"
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"


$(PATHR)%.txt: $(PATHB)%$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Testbase%_Runner$(TARGET_EXTENSION): $(PATHO)Testbase%_Runner.o $(PATHO)Testbase%.o $(PATHO)base%.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%set_Runner$(TARGET_EXTENSION): $(PATHO)Test%set_Runner.o $(PATHO)baseset.o $(PATHO)Test%set.o $(PATHO)%set.o  $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHB)Test%vector_Runner$(TARGET_EXTENSION): $(PATHO)Test%vector_Runner.o $(PATHO)Test%vector.o $(PATHO)baseset.o $(PATHO)basevector.o $(PATHO)%set.o $(PATHO)%vector.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^


#$(PATHB)Test%_Runner$(TARGET_EXTENSION): $(PATHO)Test%_Runner.o $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o #$(PATHD)Test%.d
#	$(LINK) -o $@ $^ $(PATHO)base*.o


#$(PATHB)Test%$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o #$(PATHD)Test%.d
#	$(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(TFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c $(PATHI)%.h
	$(COMPILE) $(TFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(TFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)
