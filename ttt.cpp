
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
my_strdup(const char *s)
{
  size_t len = strlen(s) + 1;
  void *new1 = malloc(len);
  if (new1 == NULL) return NULL;
  return (char *) memcpy(new1, s, len);
}

int
main
(void)
{
  char aa[] = "test";
  printf("%s\n", my_strdup(aa));
  return 0;
}
