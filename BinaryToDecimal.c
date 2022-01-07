//
//  BinaryToDecimal.c
//
// This was inspired by the description from Ben Eater
//  
// The problem that this code is trying to solve, is how do you get decimal digits from a binary number.
// Computers store numbers in binary form. Efectivly, you could devide the number by 10 and find the remainder:
//
//				remainder = number - ((int(number/10))*10)
//
// This would give the low order decimal and you could place this on a stack and repeat until no more digits. Then output the stack.
// The issue with this is that the divide is a complex action to implement in logic gates. This code attempots to do the same thing 
// in effect by using long division by using bit shifting and subtraction.
//
// As C does not explicity allow access to the carry flag, I implement this by using a 64 bit word that is split into two 32 bit words.
// The low order (bit 1) of the left word is used as the carry for the substraction as the right word is rotated into the left word of the
// original number.
//
//  Created by John Maton on 15th October 2020
//

#include "BinaryToDecimal.h"

union SixtyFour {
  unsigned long all;
  unsigned int ab[2];
};

int main(void)
{
  union SixtyFour original, compute;
  int count, right=0, left=1, stackcount=0;
  char stack[10];
  
  original.all = 4294966295;                    // this number has to be less than 2^32-1 (4294967295) as we only can use the first 32 bits
  
  printf("all : %lu\n", original.all);
  printf("ab[right] : %u\n", original.ab[right]);
  printf("ab[left] : %i\n", original.ab[left]);

// This is where it happens
  
  while( original.ab[right] != 0 ) {		// keep going until we run out of number
    for (count=0; count<32; count++) {          // loop through the 32 bits of right side of the 64 bit original
      original.all <<= 1;                       // shift the number left one bit
      compute.ab[right] = original.ab[left];    // put the left word into the right word of the calculator
      compute.ab[left] = 1;                     // set the overflow bit by setting left side lower order bit (bit 33) to 1
      compute.all -= 10;                        // subtract 10 from the compute value and see if it causes the carry bit to be used
      if (compute.ab[left]==1) {                // if bit 33 did not clear then the subtraction in bits 0-32 worked ok
        original.ab[left] = compute.ab[right];  // put the remainder into the original left side
        original.ab[right] |= 1;                // OR the original to set bit 1 (that we rotated left above)
      }                                         // otherwise we do nothing and just loop round again
    }
    						// The right side of original contains the remainder of the division. 
						// The left side of the original contains the leading decimal character
    stack[stackcount++] = original.ab[left];	// put the number on the stack
    original.ab[left]=0;                        // Clear out the left side and go back and do it again until we run out of digits
  }

// Done - print out the number

  printf("The number is ");
  do {
    printf("%c", stack[--stackcount] + '0');    // print the stack in reverse order
  } while (stackcount!=0);
  printf("\n");
  return 0;
}
