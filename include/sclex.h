#ifndef SCLEXDRIVER_H
#define SCLEXDRIVER_H

/*#include "lfile.h"*/
#include "dfa.h"
#include "Parser.h"
#include <stdbool.h>
#ifdef __STRICT_ANSI__
#define inline
#endif

#define ARGUMENTS_NEEDED 2
#define FILENAME_ARG 1

int CleanupMemory(Io* programIO, struct _DFA** dfa);

#endif
