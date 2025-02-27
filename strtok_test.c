
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char test[80], blah[80];
  char *sep = "\\/:;=-. ";
  char *word, *phrase, *brkt, *brkb;

  int count = 0;
  char *tokarray[1024];
  
  // strcpy(test, "This;is.a:test:of=the/string\\tokenizer-function.");

  strcpy(test, "This is a test of the string tokenizer function.");

  for (word = strtok_r(test, sep, &brkt);
       word;
       word = strtok_r(NULL, sep, &brkt))
    {
      tokarray[count] = strdup(word);
      count++;
      
      strcpy(blah, "blah:blat:blab:blag");

      for (phrase = strtok_r(blah, sep, &brkb);
	   phrase;
	   phrase = strtok_r(NULL, sep, &brkb))
	{
	  printf("So far we're at %s:%s\n", word, phrase);
	}
    }
  int i;
  for (i = 0; i < count; i++)
    {
      printf("=> %s %d\n", tokarray[i], i);
    }
}
