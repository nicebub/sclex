#include "baseset.h"
#include "intset.h"
#include "basevector.h"
#include "intvector.h"
int main(){
	int_set* set1, *set2, *set3, *set4;
	int_vector *my_vec;
	int i;
	set1 = new_int_set(5);
	set2 = new_int_set(6);
	set3 = new_int_set(7);
	set4 = new_int_set(8);
	for(i=0;i<5;i++){
		add_to_set(&set1,i+1);
		add_to_set(&set2,i+3);
		add_to_set(&set3,i+7);
		add_to_set(&set4,i+11);
	}
	display_set(set1);
	display_set(set2);
	display_set(set3);
	display_set(set4);

	my_vec = new_int_vector(4);
	display_vector(my_vec);
	
	add_to_vector(set1,my_vec);
	add_to_vector(set2,my_vec);
	add_to_vector(set3,my_vec);
	add_to_vector(set4,my_vec);
	display_vector(my_vec);
	

	delete_vector(my_vec);
	my_vec = NULL;

	/* adding set to vector gives vector the responsibility
		of deleting the set
	*/

	set1 = set2 = set3 = set4 = NULL;
	return 0;
}