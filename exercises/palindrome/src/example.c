#include "palindrome.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true if the product of a and b is a palindrome, false otherwise */
bool isPalindromeProduct(int a, int b)
{
   char number[10];
   int length;

   sprintf(number, "%d", a * b);
   length = strlen(number);

   for (int i = 0; i < length / 2; i++) {
      if (number[i] != number[length - i - 1]) {
         return false;
      }
   }
   return true;
}

/* return the factors of a palindrome */
Pair *getPalindromeFactors(int palindrome)
{
   Pair *tableP;
   int sizeTableP = 0, tablePcount = 0;

   /* Compute the size of the array */
   for (int i = 1; i <= palindrome; i++) {
      for (int j = 1; j <= palindrome; j++) {
         if (i * j == palindrome) {
            sizeTableP++;
         }
      }
   }
   assert((tableP = malloc(sizeTableP * sizeof(Pair))) != NULL);

   // for each possibility, if i*j is a product of the palindrome, add it to the return
   for (int i = 1; i <= palindrome; i++) {
      for (int j = 1; j <= palindrome; j++) {
         if (i * j == palindrome) {
            tableP[tablePcount].a = i;
            tableP[tablePcount].b = j;
            tablePcount++;
         }
      }
   }
   return tableP;
}

/* return a struct of PalindromeProduct, containing a palindrome and an array of his factor */
PalindromeProduct *getPalindromeProduct(int min, int max)
{
   // Creating an array
   PalindromeProduct *ret;
   assert((ret = malloc(2 * sizeof(PalindromeProduct))) != NULL);
   int ret_pos = 0;

   // for each possibility, verify if it's a palindrome
   for (int i = min; i <= max; i++) {
      for (int j = min; j <= max; j++) {
         if (isPalindromeProduct(i, j) == true) {
            ret[ret_pos].palindrome = i * j;
            ret[ret_pos].factors = getPalindromeFactors(i * j);

            // now searching for the largest palindrome
            ret_pos = 1;
         }
      }
   }
   return ret;
}
