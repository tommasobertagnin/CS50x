#include <stdio.h>
#include <cs50.h>

double factorial (double n);

int main (void)
{
  printf("factorial of: ");
  printf("is: %.0lf\n", factorial(get_double()));
}

double factorial (double n)
{
  return n > 1 ? n * factorial(n-1) : 1; // call recursively factorial until n = 0
}
