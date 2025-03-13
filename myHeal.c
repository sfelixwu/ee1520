
// myheal.c
// author: S. Felix Wu (wu@cs.ucdavis.edu)
// original: 06/21/2008 South Lake Tahoe
// updated:  06/25/2008 from IAD to SMF

// usage: $myheal <target_file> <break_prefix> <chunk size in 1K> <chunks>
// to compile: $gcc -g -Wall myheal.c -o myheal

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
  int chunks = 0;
  char *fname = NULL;

  if (argc != 5)
    {
      printf("argc = %d => usage: myheal <source> <prefix> <chunk size (K)> <chunks>\n", argc);
      exit(1);
    }

  chunk_size = 1024 * atoi(argv[3]);
  if ((chunk_size <= 0) || (chunk_size > (1024 * 1024 * 1024)))
    {
      printf("chunk size error [%d]: size needs to be between 1 (1K) and %d (1G) \n",
	     atoi(argv[3]), 1024*1024);
      exit(1);
    }

  chunks = atoi(argv[4]);
  if ((chunks <= 0) || (chunks > (8192 * 16)))
    {
      printf("chunks error [%d]: chunks needs to be between 1 and %d \n",
	     atoi(argv[4]), 8192*16);
      exit(1);
    }
	
  f = fopen(argv[1], "w");
  if (f != NULL)
    {
      int i,j;
      for (i = 0; i < chunks; i++)
	{
	  fname = malloc(MAX_NAME);
	  bzero((void *) fname, MAX_NAME);
	  sprintf(fname, "%s.%032d", argv[2], i);
	  tf = fopen(fname, "r");
	  if (tf != NULL)
	    {
	      printf(" putting %s\n", fname);
	    }
	  else
	    {
	      printf("fname %s failed to open\n", fname);
	      exit(1);
	    }

	  for (j = 0; j < (chunk_size / 8); j++)
	    {
	      unsigned char ccc[8];
	      int cr, cw;

	      cr = fread(ccc, 1, 8, tf);
	      if (cr == 0) break;

	      cw = fwrite(ccc, 1, cr, f);
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
  fclose(f);
  printf("done... [%d] chunks produced for %s\n", chunks, argv[1]);
  return 1;
}
