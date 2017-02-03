#include <cs50.h>
#include <stdio.h>

void swap (int * a, int * b);

int main (void)
{
  printf("a: ");
  int a = get_int();

  printf("b: ");
  int b = get_int();

  // passing the addresses of variables `a` and `b`
  swap(&a, &b);

  printf("new a: %i\n", a);
  printf("new b: %i\n", b);

  // all good
  return 0;
}

// swap requires pointers `*` to change the original variables
// and not the local copies
void swap (int * a, int * b)
{
  // in this context `*` means get the value at that address
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
