#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>

int main (int argc, string argv[])
{
  // return 1 in case no key argument (or more than one)
  if (argc != 2)
  {
    printf("You must pass a key argument\n");
    return 1;
  }
  
  int key = atoi(argv[1]); // store the key argument
  
  printf("plaintext: "); // prompt the user for input
  string s = get_string(); // get the user input string
  
  int i = 0; // keep track of string position
  int shift; // ASCII => Alphabet index shift (es. A: 65 => 0)
  
  // loop through the string chars
  while (s[i] != '\0')
  {
    // rotate the alphanumeric characters
    if (isalpha(s[i]))
    {
      // change shift according to letter case (upper 65, lower 97)
      shift = isupper(s[i]) ? 'A' : 'a';
      // rotate the char
      s[i] = (char) ((((int) s[i]) + key - shift) % 26 ) + shift;
    }
    i++;
  }
  
  printf("ciphertext: %s\n", s);
}