#include "basevector.h"
/*int main(){*/
void test_vector(void){
	base_vector* madvector;
	madvector = new_vector(50);
	add_to_vector(NULL,madvector);
	display_vector(madvector);
	delete_vector(madvector);
	madvector = NULL;
}
