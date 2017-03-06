#include <stdio.h>

void byTwo (int *);

int main (void)
{
  int a = 5;

  byTwo(&a); // & returns the address in memory of 'a'

  printf("the new value of 'a' is %i", a);
}

void byTwo (int * x)
{
  *x = *x * 2; // * returns the value at that address in memory
}
