#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
  // prompt the user for input
  string s = get_string();
  
  // check that the input is not null
  if (s == NULL)
  {
    printf("String should not be NULL");
    return 1;
  }
  
  // keep track of the last character value (default to a space for s[0])
  char lastChar = ' ';
  
  // iterate through the string characters
  for (int i = 0, slen = strlen(s); i < slen; i++)
  {
    // if this is a letter following a space char
    if (isalpha(s[i]) && isspace(lastChar))
    {
      // print the uppercase letter
      printf("%c", toupper(s[i]));
    }
    
    // update lastChar with the current one for the next loop
    lastChar = s[i];
  }
  printf("\n");
  
  return 0;
}