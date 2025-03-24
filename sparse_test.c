
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void
create_file_with_hole
(int _fd, int _position, char *_str)
{
  if (_str == NULL)
    {
      fprintf(stderr, "null str pointer\n");
      return;
    }
  lseek(_fd, _position, SEEK_SET); // Make a hole
  write(_fd, _str, strlen(_str));
}

int
main
(void)
{
  int fd = open("file.hole", O_WRONLY|O_TRUNC|O_CREAT, 0600);
  write(fd, "Hello", 5);

  int i;
  for (i = 0; i < 5; i++)
    {
      create_file_with_hole(fd, rand(), "Hello");
      if (i % 100 == 0) sleep(1);
    }
  close(fd);
}
