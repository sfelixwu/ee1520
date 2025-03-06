
#include <stdio.h>
#include <stdlib.h>

void
foo
(void)
{
  int fx;
  printf("fx = %d %p\n", fx, &fx);
  
  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  void *ptr2 = __builtin_extract_return_addr(__builtin_return_address(1));
  printf("ret_addr(0)=%p\nret_addr(1)=%p\n", ptr, ptr2);

  void **ret;
  ret = ((void **) (((long long) (&fx)) + 20));
  printf("ret_addr+20=%p\n", ((void *) (*ret)));
  return;
}

void
bar
(void)
{
  int bx;
  printf("bx = %d %p\n", bx, &bx);

  void *ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
  void *ptr2 = __builtin_extract_return_addr(__builtin_return_address(1));
  printf("ret_addr(0)=%p\nret_addr(1)=%p\n", ptr, ptr2);
  
  return;
}

int
main(void)
{
  printf("Foo address = %p\n", foo);
  foo();
  printf("Bar address = %p\n", bar);
  bar();
  printf("Foo address = %p AGAIN\n", foo);
  foo();
  return 0;
}
