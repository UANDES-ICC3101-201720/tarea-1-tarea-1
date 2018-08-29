#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned int hola[10] = [1,2,3,4,5,6,7,8,9,10];
  unsigned int *actual = NULL;
  
  actual = (unsigned int *)&hola;
  printf("%u\n", actual[0]); *actual++;
  printf("%u\n", actual[0]); *actual++;
  printf("%u\n", actual[0]); *actual++;
  printf("%u\n", actual[0]); *actual++;

  printf( "    short int: %zd\n" , sizeof(short int) ) ;
  printf( "          int: %zd\n" , sizeof(int) ) ;
  printf( "     long int: %zd\n", sizeof(long int) ) ;
  printf( "long long int: %zd\n", sizeof(long long int) ) ;
  printf( "       size_t: %zd\n", sizeof(size_t) ) ;
  printf( "        void*: %zd\n\n", sizeof(void *) ) ;
  printf( " unsigned int: %zd\n\n", sizeof(unsigned int) ) ;

  return 0;
}

