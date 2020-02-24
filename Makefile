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
#	GENERATE_RUNNER= ruby unity/auto/generate_test_runner.rb
endif

.PHONY: clean
.PHONY: test

PATHU = unity/src/
PATHS = src/
PATHI = include/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

BASE_SRCT = $(wildcard $(PATHT)*base*.c)
SRCT = $(wildcard $(PATHT)*[!b][!a][!s][!e]*.c)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHI) -I$(PATHU) -I$(PATHS) -DTEST -ansi -Wall -Wpedantic -pedantic-errors -Wno-comment -Wno-incompatible-pointer-types
CFLAGS += -g
BASE_RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(BASE_SRCT) )
RESULTS = $(patsubst $(PATHT)Test%_Runner.c,$(PATHR)Test%_Runner.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

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
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c $(PATHI)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

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




clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHD)*.d
	$(CLEANUP) $(PATHT)*_Runner.c
	$(CLEANDIR) $(PATHD)
	$(CLEANDIR) $(PATHO)
	$(CLEANDIR) $(PATHR)
	$(CLEANDIR) $(PATHB)

.PRECIOUS: $(PATHB)Testbase%_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHB)Test%set_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHB)Test%vector_Runner$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
