#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, string argv[])
{
  // pointer where key will be stored
  int *key;
  
  // exit if arguments are not 2
  if (argc != 2)
  {
    printf("You provided the wrong number of arguments!\n");
    return 1;
  }
  // validate the key
  else
  {
    // allocate the memory based on string length
    key = (int *) malloc(strlen(argv[1]) * sizeof(int));
    
    // loop through the key chars
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
      // exit if key contains non alphabetic chars
      if (!isalpha(argv[1][i]))
      {
        printf("The key must contain only alphabetic characters!\n");
        return 1;
      }
      // set the key as int value
      key[i] = toupper(argv[1][i]) - 'A';
    }
  }
  
  // prompt the user with for a plaintext string
  printf("plaintext: ");
  string s = get_string();
  
  // keep track of ASCII shift and index of key
  int shift, iK = 0;
  
  // loop through the string chars
  for (int i = 0, n = strlen(s); i < n; i++)
  {
    // change only alphabet chars
    if (isalpha(s[i]))
    {
      // set ASCII shift based on upper/lower case
      shift = isupper(s[i]) ? 'A' : 'a';
      // rotate the char based on the current key[iK] value
      s[i] = (char) ((((int) s[i]) + key[iK] - shift) % 26) + shift;
      
      // increase iK or set it to zero in case it is larger than the key (array) size
      if ((iK++) == (int) sizeof(key) / sizeof(int))
      {
        iK = 0;
      }
    }
  }
  
  // print the resulting cipher and return 0
  printf("ciphertext: %s\n", s);
  return 0;
}