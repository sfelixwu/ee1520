
#include "stack_01.h"

void
print_return_address
(const int _level, const char _fname[5])
{
  void *_ptr = NULL;
  switch(_level)
    {
    case 0:
      _ptr  = __builtin_extract_return_addr(__builtin_return_address(0));
      break;
    case 1:
      _ptr  = __builtin_extract_return_addr(__builtin_return_address(1));
      break;
    case 2:
      _ptr  = __builtin_extract_return_addr(__builtin_return_address(2));
      break;
    case 3:
      _ptr  = __builtin_extract_return_addr(__builtin_return_address(3));
      break;
    default:
      _ptr  = __builtin_extract_return_addr(__builtin_return_address(4));
    }

  printf("ret_addr(%d) = %p [%s]\n", _level, _ptr, _fname);
  printf("ret_function = %p \n", *((void **) _ptr));
  return;
}
