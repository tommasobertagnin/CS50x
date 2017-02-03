#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
  printf("s: ");
  char *s = get_string();
  if (s == NULL)
  {
    return 1;
  }

  // loop all the way to the end of `s`
  for (int c = 0, n = strlen(s); c < n; c++)
  {
    // `s[c]` is synctactic sugar for `*(s + c)`
    printf("%c\n", *(s + c));
  }

  // all good
  return 0;
}
