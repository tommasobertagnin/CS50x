#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
  // get first string
  printf("s: ");
  char * s = get_string();
  if (s == NULL)
  {
    return 1;
  }

  // second..
  printf("t: ");
  char * t = get_string();
  if (t == NULL)
  {
    return 1;
  }

  // compare and print result
  if (strcmp(s, t) == 0)
  {
    printf("same\n");
  }
  else
  {
    printf("different!\n");
  }

  // all good
  return 0;
}
