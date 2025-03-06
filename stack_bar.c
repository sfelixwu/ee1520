
#include "stack_01.h"

void
bar
(void)
{
  int bx = 2;
  printf("bx = %d %p\n", bx, &bx);
  
  print_return_address(0, __FUNCTION__);
  print_return_address(1, __FUNCTION__);
  baz();

  return;
}
