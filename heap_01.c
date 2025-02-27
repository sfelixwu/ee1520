
#include <stdio.h>
#include <stdlib.h>

void
baz
(void)
{
  int zx = 3;
  printf("zx = %d %p\n", zx, &zx);
  
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  printf("ret_addr(0) = %p [%s]\n", ptr, __FUNCTION__);

  void *ptr2 = __builtin_extract_return_addr(__builtin_return_address(1));
  printf("ret_addr(1) = %p [%s]\n", ptr2, __FUNCTION__);

  void *ptr3 = __builtin_extract_return_addr(__builtin_return_address(2));
  printf("ret_addr(2) = %p [%s]\n", ptr3, __FUNCTION__);

  return;
}

void
bar
(void)
{
  int bx = 2;
  printf("bx = %d %p\n", bx, &bx);
  
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  printf("ret_addr(0) = %p [%s]\n", ptr, __FUNCTION__);

  void *ptr2 = __builtin_extract_return_addr(__builtin_return_address(1));
  printf("ret_addr(1) = %p [%s]\n", ptr2, __FUNCTION__);

  baz();
  return;
}

void
foo
(void)
{
  int fx = 1;
  printf("fx = %d %p\n", fx, &fx);
  
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  printf("ret_addr(0) = %p [%s]\n", ptr, __FUNCTION__);

  bar();
  return;
}

int
power(int x,int y)
{
  return y?(y%2?x:1)*power(x*x,y>>1):1;
};

int
main(void)
{
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  printf("ret_addr(0) = %p [%s]\n", ptr, __FUNCTION__);
  foo();

  void *xyz = NULL;
  int i;
  for (i = 0; i < 8; i++)
    {
      unsigned int alloc_size =  sizeof(char) * 1024 * power(2,i);
      xyz = malloc(alloc_size);
      printf("heap chunk size = %10d address = %p\n", alloc_size, xyz); 
    }
  return 0;
}
