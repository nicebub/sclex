#ifndef MDDFA_H
#define MDDFA_H

#include "tree.h"
#include "retodfa.h"

struct _DFA {
    struct _iseta *Dstates;
    struct _iset *FFstates;
    struct _cset *alphabet;
    struct _iset ***DUTran;
    struct _iset **Fstates;
    int **Dtran;
    char ** action_array;
    int start;
    int num_states;
	int num_re;
};


struct _DFA* generate_dfa(struct _ta *tree,struct _iseta * fpos, struct _cset * alphabet);

struct _DFA* create_dfa(void);
void delete_dfa(struct _DFA*);

#endif
