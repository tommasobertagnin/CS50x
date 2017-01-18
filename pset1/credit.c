#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
  long long n; // will contain the CC number
  
  do
  {
    printf("Please write your credit card number: ");
    n = get_long_long();
  }
  while (n <= 0);
  
  int digits = log10(n) + 1, // get the number of digits, original formula: floor (log10 (abs (x))) + 1
      checksum = 0;

  long long digit;
  
  for (int i = 1; i <= digits; i++)
  {
    digit = (n % (long long) pow(10, i)) / (long long) pow(10, i - 1); // get digit one by one
    
    if (i % 2 == 0) // even digits starting from second-to-last
    {
      digit *= 2;
      
      if (digit >= 10) // split digits with two decimals
      {
        checksum += 1; // add second decimal
        digit = digit % 10; // set digit to first decimal (will be added below)
      }
    }
    
    checksum += (int) digit; // cast long to int and add to checksum
  }
  
  if (checksum % 10 == 0) // valid CC number
  {
    int id = (int) ((n % (long long) pow(10, digits)) / (long long) pow(10, digits - 2)); // get first two digits

    if      (id == 34 || id == 37)  printf("AMEX\n");
    else if (id >= 40 && id <= 49)  printf("VISA\n");
    else if (id >= 51 && id <= 55)  printf("MASTERCARD\n");
    else                            printf("VALID\n"); // bank not recognized
  }
  else // invalid CC number
  {
    printf("INVALID\n");
  }
  
  return 0;
}

// test against these CC nums:
// https://www.paypalobjects.com/en_US/vhelp/paypalmanager_help/credit_card_numbers.htm
