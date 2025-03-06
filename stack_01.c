
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
  printf("ret_function = %p \n", *((void **) ptr));

  void *ptr2 = __builtin_extract_return_addr(__builtin_return_address(1));
  printf("ret_addr(1) = %p [%s]\n", ptr2, __FUNCTION__);
  printf("ret_function = %p \n", *((void **) ptr2));

  void *ptr3 = __builtin_extract_return_addr(__builtin_return_address(2));
  printf("ret_addr(2) = %p [%s]\n", ptr3, __FUNCTION__);
  printf("ret_function = %p \n", *((void **) ptr3));

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
main(void)
{
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  printf("ret_addr(0) = %p [%s]\n", ptr, __FUNCTION__);
  foo();
  return 0;
}
