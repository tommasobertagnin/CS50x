#include "struct.h"
#include <stdio.h>
#include <cs50.h>

#define N 3

int main (void)
{
  vector vectors[N];

  for (int i = 0; i < N; i++)
  {
    printf("x: ");
    vectors[i].x = get_int();

    printf("y: ");
    vectors[i].y = get_int();
  }

  int save;
  do
  {
    printf("save to file? (y/n) ");
    save = getchar();
  }
  while (save != 'y' && save != 'n');

  if (save == 'y')
  {
    // open a file in write mode
    FILE *fvec = fopen("vectors.csv", "w");

    // write a header in the CSV
    fprintf(fvec, "name,x,y\n");

    // write all the vectors data to the file
    for (int i = 0; i < N; i++)
    {
      fprintf(fvec, "vector%03i,%i,%i\n", i+1, vectors[i].x, vectors[i].y);
    }

    // all good!
    fclose(fvec);
    printf("Saved!\n");
  }
  else
  {
    for (int i = 0; i < N; i++)
    {
      printf("vector%03i: %i %i\n", i+1, vectors[i].x, vectors[i].y);
    }
  }

  // all good
  return 0;
}

