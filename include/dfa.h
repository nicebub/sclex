#ifndef MDDFA_H
#define MDDFA_H

#include "tree.h"
#include "retodfa.h"
#include "baseset.h"
#include "intset.h"
#include "chrset.h"
#include "basevector.h"
#include "intvector.h"
#include "chrvector.h"
/*#include "lfile.h"*/
#include "Parser.h"
struct _DFA {
    base_vector *Dstates; /* int_vector* */
    base_set *FFstates; /* int_set* */
    base_set *alphabet; /* char_set* */
    base_set ***DUTran; /* int_set*** */
    base_set **Fstates; /* int_set** */
    int **Dtran;
    char ** action_array;
    int start;
    int num_states;
	int num_re;
};


struct _DFA* generate_dfa(Parser* parser);
			 /* int_vector*  and char_set* */

struct _DFA* create_dfa(void);
void delete_dfa(struct _DFA*);

#endif
