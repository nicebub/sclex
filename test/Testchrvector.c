#include "baseset.h"
#include "chrset.h"
#include "basevector.h"
#include "chrvector.h"

/*int main(){*/
void test_chr_set(void){
	char_set* set1, *set2, *set3, *set4;
	char_vector *my_vec;
	int i;
	set1 = new_char_set(5);
	set2 = new_char_set(5);
	set3 = new_char_set(5);
	set4 = new_char_set(5);
	for(i=0;i<5;i++){
		add_to_set(&set1,i+'a');
		add_to_set(&set2,i+'d');
		add_to_set(&set3,i+'g');
		add_to_set(&set4,i+'r');
	}
	
	display_set(set1);
	display_set(set2);
	display_set(set3);
	display_set(set4);

	my_vec = new_char_vector(4);
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
}
