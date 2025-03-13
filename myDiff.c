
// mydiff.c
// author: S. Felix Wu (sfwu@ucdavis.edu)
// original: 06/21/2008 South Lake Tahoe
// updated:  06/25/2008 from IAD to SMF
// updated:  06/12/2023 for ecs36b s2023 final

// usage: $mydiff <first_file> <second_file>
// to compile: $gcc -g -Wall mydiff.c -o mydiff

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main
(int argc, char **argv)
{
  FILE *f1 = NULL;
  FILE *f2 = NULL;

  if (sizeof(unsigned long) != 8)
    {
      printf("this program assumes unsigned long is 8 bytes\n");
      return -1;
    }
  if (argc != 3)
    {
      printf("argc = %d => usage: mydiff <first> <second>>\n", argc);
      return -2;
    }

  f1 = fopen(argv[1], "r");
  f2 = fopen(argv[2], "r");
  
  if (f1 == NULL)
    {
      printf("file [%s] fopen failed\n", argv[1]);
      return -3;
    }
	
  if (f2 == NULL)
    {
      printf("file [%s] fopen failed\n", argv[2]);
      return -3;
    }

  while(1)
    {
      unsigned char byte_f1[8];
      unsigned char byte_f2[8];
      unsigned long *ptr_byte_f1 = (unsigned long *) (&byte_f1);
      unsigned long *ptr_byte_f2 = (unsigned long *) (&byte_f2);
	  
      int cr_f1;
      int cr_f2;
      cr_f1 = fread(byte_f1, 1, 8, f1);
      cr_f2 = fread(byte_f2, 1, 8, f2);
	  
      if ((cr_f1 == 0) && (cr_f2 == 0))
	{
	  fclose(f1);
	  fclose(f2);
	  printf("done... [%s] and [%s] are the same\n", argv[1], argv[2]);
	  return 0;
	}
      else
	{
	  if ((cr_f1 == 0) || (cr_f2 == 0) || (cr_f1 != cr_f2) ||
	      ((*ptr_byte_f1) != (*ptr_byte_f2)))
	    {
	      fclose(f1);
	      fclose(f2);
	      printf("done... [%s] and [%s] are different\n", argv[1], argv[2]);
	      return 0;
	    }
	}
    }
  printf("this should never be reached!\n");
  return -4;
}

char *
strdup(const char *s)
{
  size_t len = strlen(s);
  void *new = malloc(len);

  if (new == NULL)
    return NULL;
  
  return (char *) memcpy(new, s, len);
}
