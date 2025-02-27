#include <stdio.h>

int main() {
    int i = 1;
    char* c = NULL; // declaration 0x0000000000000000
    c = (char*) (&i); // &i (int*) casting

    (*c) = (char) 87;
    
    if (*c)
      printf("LITTLE_ENDIAN [%c] \n", *c);
    else
        printf("BIG_ENDIAN\n");

    return 0;
}
