#ifndef SCLEXDRIVER_H
#define SCLEXDRIVER_H

#include "lfile.h"
#include "dfa.h"

#ifdef __STRICT_ANSI__
#define inline
#endif

#define ARGUMENTS_NEEDED 2
#define FILENAME_ARG 1


void initIO(Io* programIO);
inline int regularExpressionTreeArrayExists(Io* inIO);
inline int firstPositionSetExists(Io* inIO);
inline int canGenerateDFA(Io* programIO);

int CleanupMemory(Io* programIO, struct _DFA** dfa);

#endif
