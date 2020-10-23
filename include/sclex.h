#ifndef SCLEXDRIVER_H
#define SCLEXDRIVER_H

#include "lfile.h"

#ifdef __STRICT_ANSI__
#define inline
#endif

#define ARGUMENTS_NEEDED 2
#define FILENAME_ARG 1


void initIO(Io* programIO);
inline int ASTExists(Io* inIO);
inline int firstPositionSetExists(Io* inIO);
inline int canGenerateDFA(Io* programIO);
inline void initializeParserWithArgument(Io* programIO,char* argumentFileName);

int CleanupMemory(Io* programIO, struct _DFA** dfa);

#endif
