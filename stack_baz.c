
#include "stack_01.h"

void
baz
(void)
{
  int zx = 3;
  printf("zx = %d %p\n", zx, &zx);
  
  print_return_address(0, __FUNCTION__);
  print_return_address(1, __FUNCTION__);
  print_return_address(2, __FUNCTION__);

  return;
}
