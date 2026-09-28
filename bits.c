/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* De Morgan's law expresses XOR using only NOT and AND. */
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* Arithmetic right shift supplies either all zeros or all ones. */
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int sourceShift = src << 3;
  int destinationShift = dst << 3;
  int byte = (x >> sourceShift) & 255;
  int mask = 255 << destinationShift;
  return (x & ~mask) | (byte << destinationShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* This mask also works when n is zero; no shift by 32 is needed. */
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 15 | (15 << 8);
  mask = mask | (mask << 16);
  return ((x >> 4) & mask) | ((x & mask) << 4);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* Fill the first zero, then isolate the next zero. */
  int filled = x | (x + 1);
  return ~filled & (filled + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int shift = n & 31;
  int leftShift = (~shift + 1) & 31;
  int mask = ~(((1 << 31) >> shift) << 1);
  return ((x >> shift) & mask) | (x << leftShift);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int block = 1 << n;
  int half = block >> 1;
  int mask = block + ~0;
  int bias = half + ~0;
  int odd = (x >> n) & 1;
  /* Adding half minus one makes a tie round up only for an odd quotient. */
  return (x + bias + odd) & ~mask;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int different = x ^ y;
  int signDiff = different >> 31;
  int greater = (signDiff & ~(x >> 31)) |
                (~signDiff & ((y + ~x + 1) >> 31));
  int lower = (x & y) + (different >> 1);
  /* The floor midpoint is safe; an odd sum needs a step toward x if x > y. */
  return lower + (greater & different & 1);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sign = x >> 31;
  int differentA = x ^ a;
  int differentB = x ^ b;
  int signDiffA = differentA >> 31;
  int signDiffB = differentB >> 31;
  int lessA = (signDiffA & sign) |
              (~signDiffA & ((x + ~a + 1) >> 31));
  int lessB = (signDiffB & sign) |
              (~signDiffB & ((x + ~b + 1) >> 31));
  /* Opposite comparison results mean an interior point; include equality. */
  return ((lessA ^ lessB) & 1) | !differentA | !differentB;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int twice = x + x;
  int four = twice + twice;
  int five = four + x;
  int overflow = ((x ^ twice) | (twice ^ four) | (four ^ five)) >> 31;
  int limit = (1 << 31) ^ ~(x >> 31);
  return (overflow & limit) | (~overflow & five);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int firstSum = x + y;
  int total = firstSum + z;
  int firstOverflow = ((x ^ firstSum) & (y ^ firstSum)) >> 31;
  int secondOverflow = ((firstSum ^ total) & (z ^ total)) >> 31;
  int firstDirection = (x >> 31) | 1;
  int secondDirection = (firstSum >> 31) | 1;
  /* Opposite overflow corrections cancel when the exact final sum fits. */
  return (firstOverflow & firstDirection) +
         (secondOverflow & secondDirection);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exponent = (uf >> 23) & 255;
  unsigned fraction = uf & 0x7fffffu;
  unsigned product;
  unsigned significand;
  unsigned shift = 1;
  unsigned remainder;
  unsigned half;

  if (exponent == 255)
    return uf;
  if (exponent == 0) {
    /* The rounded integer also encodes a transition to the normal range. */
    product = fraction + (fraction << 1);
    significand = (product >> 1) + ((product & 3) == 3);
    return sign | significand;
  }

  significand = fraction | 0x800000u;
  product = significand + (significand << 1);
  if (product >= 0x2000000u) {
    shift = 2;
    exponent = exponent + 1;
  }
  remainder = product & ((1u << shift) - 1);
  significand = product >> shift;
  half = 1u << (shift - 1);
  if (remainder > half ||
      (remainder == half && (significand & 1)))
    significand = significand + 1;
  if (significand >= 0x1000000u) {
    significand = significand >> 1;
    exponent = exponent + 1;
  }
  if (exponent >= 255)
    return sign | 0x7f800000u;
  return sign | (exponent << 23) | (significand & 0x7fffffu);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000u;
  unsigned exponent = (uf >> 23) & 255;
  unsigned fraction = uf & 0x7fffffu;
  unsigned shift;
  unsigned mask;
  unsigned remainder;
  unsigned half;
  unsigned result;

  /* Large finite values are already integral; infinities and NaNs are kept. */
  if (exponent >= 150)
    return uf;
  if (exponent < 126)
    return sign;
  if (exponent == 126) {
    if (fraction == 0)
      return sign;
    return sign | 0x3f800000u;
  }

  shift = 150 - exponent;
  mask = (1u << shift) - 1;
  remainder = uf & mask;
  half = 1u << (shift - 1);
  result = uf & ~mask;
  if (remainder > half ||
      (remainder == half && ((result >> shift) & 1)))
    result = result + (1u << shift);
  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned sign = 0;
  unsigned magnitude = x;
  unsigned exponent;
  unsigned significand;
  unsigned shift;
  unsigned remainder;
  unsigned half;
  int highest = 31;

  if (x == 0)
    return 0;
  if (x < 0) {
    sign = 0x80000000u;
    magnitude = ~magnitude + 1;
  }
  while (!(magnitude >> highest))
    highest = highest - 1;
  exponent = highest + 127;
  if (highest <= 23)
    return sign | (exponent << 23) |
           ((magnitude << (23 - highest)) & 0x7fffffu);

  shift = highest - 23;
  significand = magnitude >> shift;
  remainder = magnitude & ((1u << shift) - 1);
  half = 1u << (shift - 1);
  if (remainder > half ||
      (remainder == half && (significand & 1)))
    significand = significand + 1;
  if (significand >> 24) {
    exponent = exponent + 1;
    significand = significand >> 1;
  }
  return sign | (exponent << 23) | (significand & 0x7fffffu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask4 = 15 | (15 << 8);
  int mask2;
  int mask1;
  mask4 = mask4 | (mask4 << 16);
  mask2 = mask4 ^ (mask4 << 2);
  mask1 = mask2 ^ (mask2 << 1);
  /* Add counts in groups of 2, 4, 8, 16 and finally 32 bits. */
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x + (x >> 4)) & mask4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 63;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask4 = 15 | (15 << 8);
  int mask2;
  int mask1;
  int byteMask = 255 << 8;
  mask4 = mask4 | (mask4 << 16);
  /* Deriving these masks saves four operations compared with building both. */
  mask2 = mask4 ^ (mask4 << 2);
  mask1 = mask2 ^ (mask2 << 1);
  x = ((x >> 1) & mask1) | ((x & mask1) << 1);
  x = ((x >> 2) & mask2) | ((x & mask2) << 2);
  x = ((x >> 4) & mask4) | ((x & mask4) << 4);
  return (x << 24) | ((x & byteMask) << 8) |
         ((x >> 8) & byteMask) | ((x >> 24) & 255);
}
