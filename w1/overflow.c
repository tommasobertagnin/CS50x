#include <cs50.h>
#include <stdio.h>

int main (void) {
  int intNum = 2;
  for (int i = 0; i < 64; i++) {
    intNum *= intNum;
    printf("%i\n", intNum);
  }
}

// this program will overflow an int returning this error:
// -> overflow.c:7:12: runtime error: signed integer overflow: 65536 * 65536 cannot be represented in type 'int'


// example of overflow

// 1 bit (8 bytes) represents number between 0-255
// 128 64  32  16  8   4   2   1
// 0   0   0   0   0   0   0   0

// bit representation of number: 31
// 128 64  32  16  8   4   2   1
// 0   0   0   1   1   1   1   1

// bit representation of number: 117
// 128 64  32  16  8   4   2   1
// 0   1   1   1   0   1   0   1

// bit representation of number: 117
// 128 64  32  16  8   4   2   1
// 0   1   1   1   0   1   0   1

// overflow: 256!! (you need 9 bytes to represents 256)
// 256 128 64  32  16  8   4   2   1
// 1   0   0   0   0   0   0   0   0   