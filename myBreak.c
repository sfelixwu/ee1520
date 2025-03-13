
// mybreak.c
// author: S. Felix Wu (wu@cs.ucdavis.edu)
// original: 06/21/2008 South Lake Tahoe
// updated:  06/25/2008 from IAD to SMF

// usage: $mybreak <source_file> <break_prefix> <size of each chunk in 1K>
// to compile: $gcc -g -Wall mybreak.c -o mybreak

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_NAME 8192

int
main
(int argc, char **argv)
{
  FILE *f = NULL;
  FILE *tf = NULL;
  int chunk_size;
  char *fname = NULL;

  if (argc != 4)
    {
      printf("argc = %d => usage: mybreak <source> <prefix> <chunk size (K)>\n", argc);
      exit(1);
    }

  chunk_size = 1024 * atoi(argv[3]);
  if ((chunk_size <= 0) || (chunk_size > (1024 * 1024 * 1024)))
    {
      printf("chunk size error [%d]: size needs to be between 1 (1K) and %d (1G) \n",
	     atoi(argv[3]), 1024*1024);
      exit(1);
    }
	
  f = fopen(argv[1], "r");
  if (f != NULL)
    {
      int i,j;
      for (i = 0;; i++)
	{
	  fname = malloc(MAX_NAME);
	  bzero((void *) fname, MAX_NAME);
	  sprintf(fname, "%s.%032d", argv[2], i);

	  tf = fopen(fname, "w");
	  if (tf != NULL)
	    {
	      printf(" starting %s\n", fname);
	    }
	  else
	    {
	      printf(" can not open %s\n", fname);
	      exit(1);
	    }

	  for (j = 0; j < (chunk_size / 8); j++)
	    {
	      unsigned char ccc[8];
	      int cr, cw;

	      cr = fread(ccc, 1, 8, f);
	      if (cr == 0)
		{
		  fclose(f);
		  fclose(tf);
		  free(fname);
		  printf("done... [%d] chunks produced for %s\n", (i+1), argv[1]);
		  exit(0);
		}

	      cw = fwrite(ccc, 1, cr, tf);
	      if (cr != cw)
		{
		  printf("cr = %d, cw = %d\n", cr, cw);
		  exit(1);
		}
	    }
	  fclose(tf);
	  free(fname);
	}
    }
  else
    {
      printf("file {%s} can not be open...\n", argv[1]);
      exit(1);
    }
  return 1;
}
