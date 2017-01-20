#include <stdio.h>
#include <cs50.h>

int main (void)
{
  // accept a user input of type string
  string s = get_string();
  // n represents the string length
  int n = 0;
  
  // check that the string is not NULL
  if (s != NULL)
  {
    // loop until the end of the string aka \0
    while (s[n] != '\0')
    {
      printf("%c\n", s[n]);
      // increment the string length
      n++;
    }
  }
  
  // print the total string length
  printf("Total string length is: %i\n", n);
  
  // return the string length (0 in case of NULL string)
  return n;
}