#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
  // accept user input as string
  string s = get_string();
  
  // if the string is valid
  if (s != NULL)
  {
    // iterate through the letters (note how n is initalized)
    for (int i = 0, n = strlen(s); i < n; i++)
    {
      // capitalize them
      s[i] = toupper(s[i]);
    }
    // print the capitalized string
    printf("%s\n", s);
  }
  
  return 0;
}