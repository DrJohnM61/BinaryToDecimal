# BinaryToDecimal
Prints a binary held number as a decimal just using logical functions

This code was inspired by the description from Ben Eater on how to turn a binary integer number into a decimal output

I know that this seems trivial, you just use a print function, right?

But think back to the days of the first computers. How did they take a number held in binary and print out the digits, one by one to form the decimal version?

This code uses logic functions to progresivly divide the binary number by 10 (base 10) and store the remainder on a stack and then
print out the stack in reverse order. Note that the computations are all done with logical functions and bit shifting. No division takes place

The code uses a 64 bit integer to do the shifting but only the right half can be used for the initial initiger, so the maximum integer size can only be:
2^32-1 (4294967295)

Lots of comments in the code.

Enjoy
