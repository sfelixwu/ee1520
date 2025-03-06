
#include "stack_01.h"

void
foo
(void)
{
  int fx = 1;
  printf("fx = %d %p\n", fx, &fx);

  print_return_address(0, __FUNCTION__);
  bar();

  return;
}
