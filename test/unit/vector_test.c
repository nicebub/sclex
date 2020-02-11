#include "basevector.h"
int main(){
	base_vector* madvector;
	madvector = new_vector(50);
	add_to_vector(NULL,madvector);
	display_vector(madvector);
	delete_vector(madvector);
	madvector = NULL;
	return 0;
}