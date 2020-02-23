01


int scanf( char *fmt, ... );
int printf( char *fmt, ... );

int
main( void )
{
  int i, j;

  scanf( "%d", &i );             
  j = 9 + i * 8;                   
  printf( "Result is %d\n", j );  
  return(0);
}
