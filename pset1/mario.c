#include <stdio.h>
#include <cs50.h>

int main (void)
{
  int h;
  
  do
  {
    printf("Enter a non-negative integer < 24: ");
    h = get_int();
  }
  while (h < 0 || h > 23);
  
  if (h == 0)
     return 0;
  
  char *blocks = "#######################";
  char *spaces = "                       ";
  
  for (int i = 1; i <= h; i++)
  {
    printf("%.*s%.*s  %.*s\n", h - i, spaces, i, blocks, i, blocks);
  }

  return 0;
}