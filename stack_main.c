
#include "stack_01.h"

int
main(void)
{
  print_return_address(0, __FUNCTION__);
  foo();
  return 0;
}
