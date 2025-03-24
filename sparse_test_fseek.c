
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void
create_file_with_hole
(FILE *_f, int _position, char *_str)
{
  if (_str == NULL)
    {
      fprintf(stderr, "null str pointer\n");
      return;
    }
  fseek(_f, _position, SEEK_SET); // Make a hole
  fwrite(_str, strlen(_str), 1, _f);
}

int
main
(void)
{
  FILE *f = fopen("./file.wohole", "w");
  create_file_with_hole(f, 0, "Hello");

  int i;
  for (i = 0; i < 5; i++)
    {
      create_file_with_hole(f, rand(), "Hello");
      if (i % 100 == 0) sleep(1);
    }
  fclose(f);
}
