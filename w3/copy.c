#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
  printf("s: ");
  char * s = get_string();
  if (s == NULL)
  {
    return 1;
  }

  // allocate memory for this new variable
  char * t = malloc((strlen(s) + 1) * sizeof(char));
  // loop all the way to `\0` in `s`
  for (int c = 0, n = strlen(s); c <= n; c++)
  {
    // copy the chars to `t`
    t[c] = toupper(s[c]);
  }

  printf("str: %s\n", s);
  printf("cpy: %s\n", t);

  // all good
  return 0;
}
