
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  int x = 1;
  unsigned char x_addr[8];
  
  int* xp;
  // int * xp;
  // int *xp;
  //(int *) xp;
  xp = &x;

  printf("the pointer of x is %16p\n", xp);
  printf("the address of x is %16p\n", &x);
  
  (*((int**) x_addr)) = xp; // the content of the ptr into the char array
  int i;
  for (i = 0; i < 8; i++)
    {
      printf("addr[%d] = %x\n", i, ((unsigned int) (x_addr[i])));
    }
  
  printf("the value of x   is %d\n", x);
  printf("the address of x is %16p\n", &x);
  printf("the address of x is %16lx\n", ((unsigned long) (&x)));
  
  printf("the size of unsigned char is %lu\n", sizeof(unsigned char));
  printf("the size of int       is %lu\n", sizeof(int));
  printf("the size of double    is %lu\n", sizeof(double));
  printf("the size of float     is %lu\n", sizeof(float));
  printf("the size of short     is %lu\n", sizeof(short));
  printf("the size of long      is %lu\n", sizeof(long));
  printf("the size of long long is %lu\n", sizeof(long long));
  printf("the size of void *    is %lu\n", sizeof(void *));
  return 0;
}
