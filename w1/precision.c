#include <cs50.h>
#include <stdio.h>

int main (void) {
  float num = 1.0 / 10;
  printf("%.64f", num);
}

// always be careful with precision!
// num is actually: 0.1000000014901161193847656250000000000000000000000000000000000000