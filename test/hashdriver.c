#include "../include/hashdriver.h"
#include "../include/hash.h"

extern struct _hash *create_hash(int size);
extern void delete_hash(struct _hash*);
extern struct _hashnode *create_hashnode(void * v, int vt, void * k, int kt);
extern void add_to_hash(struct _hash *, void * v, int vt, void * k, int kt);
//extern void * get_value_for_key(struct _hash*, void* k, int kt);

int main(int argc, const char ** argv){
    struct _hash *h;
    
    h = create_hash(10);
    
    add_iitoh(h,&(int){42},&(int){5});
    add_iitoh(h,&(int){63},&(int){4});
    add_iitoh(h,&(int){87},&(int){7});
    add_iitoh(h,&(int){91},&(int){11});
    
    printf("%d\n", *(int*)value_from_int(h,&(int){7}));
    printf("%d\n", *(int*)value_from_int(h,&(int){7}));
    printf("%d\n", *(int*)value_from_int(h,&(int){5}));
    printf("%d\n", *(int*)value_from_int(h,&(int){4}));
    printf("%d\n", *(int*)value_from_int(h,&(int){7}));
    printf("%p\n", (void*)value_from_int(h,&(int){0}));
    printf("%d\n", *(int*)value_from_int(h,&(int){7}));
    printf("%d\n", *(int*)value_from_int(h,&(int){11}));
    printf("%d\n", *(int*)value_from_int(h,&(int){11}));
    
    add_cctoh(h,&(char){'K'},&(char){'y'});
    add_cctoh(h,&(char){'N'},&(char){'r'});
    add_cctoh(h,&(char){'U'},&(char){'5'});
    add_cctoh(h,&(char){'p'},&(char){'h'});
    add_cctoh(h,&(char){'8'},&(char){'n'});
    add_cctoh(h,&(char){'^'},&(char){'q'});
    add_cctoh(h,&(char){'@'},&(char){'3'});
    add_cctoh(h,&(char){'_'},&(char){'a'});
    
    printf("%c\n", *(char*)value_from_char(h,&(char){'a'}));
    add_cctoh(h,&(char){'g'},&(char){'a'});
    printf("%c\n", *(char*)value_from_char(h,&(char){'a'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'y'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'y'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'r'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'5'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'h'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'n'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'q'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'r'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'a'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'3'}));
    printf("%c\n", *(char*)value_from_char(h,&(char){'a'}));
/*    static char * bite = "bite me";
    static char * hi = "hello";
    static char * rem = "remember";
    static char * not = "nothing";
    add_sstoh(h,bite, hi);
    add_sstoh(h,not, rem);
    add_sstoh(h,bite, hi);
    add_sstoh(h,bite, hi);
    printf("%s\n", (char*)value_from_string(h,bite));
    printf("%s\n", (char*)value_from_string(h,hi));
    printf("%s\n", (char*)value_from_string(h,rem));
    printf("%s\n", (char*)value_from_string(h,not));
    printf("%s\n", (char*)value_from_string(h,rem));
 */
    print_hash(h);
    delete_hash(h);
    return 0;
}
