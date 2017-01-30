/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

// upper limit on range of integers that can be generated
#define LIMIT 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // ensure value is a non negative int
    if (value < 0)
    {
        return false;
    }

    // keep track of the range of values to be checked in values[]
    int start = 0;
    int end = n - 1;
    int middle = end / 2;

    // binary search
    while (n > 0)
    {
        if (values[middle] == value)
        {
            return true;
        }
        // search left
        else if (values[middle] > value)
        {
            end = middle - 1;
            middle = start + (end - start) / 2;
        }
        // search right
        else if (values[middle] < value)
        {
            start = middle + 1;
            middle = start + (end - start) / 2;
        }

        // update n count
        n = end - start + 1;
    }

    // value not found
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // initialize the counting array
    int counting[ LIMIT + 1 ] = {0};

    // loop througn values[] and take note of each value in counting[]
    for (int i = 0; i < n; i++)
    {
        counting[values[i]]++;
    }

    // cursor for values[]
    int k = 0;

    // loop through counting[]
    for (int j = 0; j <= LIMIT; j++)
    {
        // store the ordered sequence of numbers to values[]
        while (counting[j])
        {
            values[k] = j;
            k++;

            counting[j]--;
        }
    }

    return;
}
