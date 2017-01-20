#include <stdio.h>
#include <cs50.h>
#include <string.h>

// main() accepts command-line arguments
int main (int argc, string argv[])
{
  // if user did not provide enough arguments
  if (argc < 2)
  {
    printf("Error: not enough command-line arguments!");
    return 1;
  }
  
  // print argument count
  printf("The argument count is: %i\n", argc);
  
  // iterate through the arguments
  for (int i = 0; i < argc; i++)
  {
    printf("argv[%i]:  ", i);
    // iterate through each argument string char
    for (int j = 0, sl = strlen(argv[i]); j < sl; j++)
    {
      // print each char followed by a space
      printf("%c ", argv[i][j]);
    }
    // end of argument string
    printf("\n");
  }
  
  return 0;
}