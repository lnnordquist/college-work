/* 
 * CS:APP Data Lab 
 * 
 * Lars Nordquist
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  //if x is neg, this will be all 1s
  //if x is positive, this will be all 0s
  int isneg = x>>31;

  //XOR with all 0s (if pos) does nothing
  //XOR with all 1s (if neg) flips all bits
  int flipped = x ^ isneg;

  //now we add 1 if neg and 0 if pos
  return flipped+!!(isneg);
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  //checks if x and y have the same sign and x+y has a diff't one
  //returns 0 if inputs have different signs
  int samesign = !((x^y)>>31);
  //samesign true means x+y and x must have the same sign
  return !samesign | !(((x+y) ^ x)>>31);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {

  //base for mask is 1010 1010
  int m = 0xAA;
  //create full mask (01.. repeating for all of the 32 bits)
  int mask = m|(m<<8)|(m<<16)|(m<<24);
  //& with mask to make all 1s if ok and not all 1s if not
  //then flip to all 0s or not all 0s
  //and use ! to map the first to 1 and the second to 0
  return !(~(x|mask));
  }
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
  int m = 0xAA;
  int mask = m|(m<<8)|(m<<16)|(m<<24);
  return !!(x&mask);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  //compare x and -x; if same leading digit, will be all 1s
  //then flip to all 0s and & with 0x1
  return (~(((~x+1)|x)>>31)&0x1);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  //"x is true or y is true" is equivalent to 
  //"x and y cannot both untrue" 
  return ~(~x&~y);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  //get a mask of 16 1s
  int maska = (0xFF<<8)|0xFF;
  //shift x right by 16, xor, get just those last 16 digits
  int a = (x^(x>>16))&maska;

  //repeat for 8, then 4, then 2, then 1 digits
  int b = (a^(a>>8))&0xFF;
  int c = (b^(b>>4))&0xF;
  int d = (c^(c>>2))&0x3;
  int e = (d^(d>>1))&0x1;
  return e;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int mshift = m<<3;
  int nshift = n<<3;
  //gets bytes and m in the same way as getByte
  int mbyte = ((x>>mshift)&0xFF)<<nshift;
  int nbyte = ((x>>nshift)&0xFF)<<mshift;

  //filter to get rid of mth and nth bytes
  int emptymn = ~(0xFF<<(m<<3) | 0xFF<<(n<<3));
  return (x & emptymn)| mbyte | nbyte;
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  //shift right 31 then back to copy
  return (x<<31)>>31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //get a shift of 32-n
  int shift = 32 + ~n + 1;
  //check if lopping off all but least significant digits changes x
  return !(x^((x<<shift)>>shift));  

  //trivially works on positives. ok on negatives since to be ok w/ fewer bits 
  //they need to be >-2^n-1 which means having all 1s up to the nth bit, 
  //so if ok theyll keep at least 1 leading one to copy when rshifting
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  //shift left by 8n, then & with (0)...0 1111 1111
  return (x>>(n<<3))&0xFF;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  //flip x to ~x if negative, basically same way as absval above
  int isneg = x>>31;
  int newx = x ^ isneg;

  //find bias if 0; should be 0 if newx nonzero and 1 if 0
  int bias = !newx;
  int pos,z1,z2,z3,z4,z5;

  //now we search for the location of the leftmost 1

  //check if in first half of 32-bit or second half
  z1 = !!(newx>>16);
  pos = z1<<4;

  z2 = !!(newx >> (pos+8));
  pos = pos + (z2<<3);

  z3 = !!(newx >> (pos+4));
  pos = pos + (z3<<2);

  z4 = !!(newx>>(pos+2));
  pos = pos + (z4<<1);

  z5 = !!(newx>>(pos+1));
  pos = pos + z5;

  return pos + 2 + (~bias +1);
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
  //only false when x is true and y is false
  //OR is only false when both are false
    return (!x)|y;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  //checks if greater than 30
  int isless30 = ((x + (~0x30+1))>>31)&1;
  //checks if less than 39
  int isbigger39 = ((0x39+(~x+1))>>31)&1;
  //both must be true
  return !isless30 & !isbigger39;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  //XOR returns 0 when digits are identical, so x^y returns
  //0 if identical and a nonzero answer if not
  return !(x^y);
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  //tests if MSD is 1
  return (x>>31)&1;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  //make sure not negative
  int isneg = (x>>31)&1;
  //get x-1
  int xminus1 = x+(~1+1);
  //flip, add 1 and check if last digit is 0
  return !isneg & !!(x) & !(x&xminus1);
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  //checks if the sign of x+x and x match
  return !(x+x)&!!x;
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
  //-1 in (signed) 2s compl notation is all 1s
  //or also the conversion ~((-1)+1) is the same as ~0
  //so this takes 0 and flips all its bits
  return ~0;
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  //multiply by 5
  int five_x = (x<<2)+x;
  //need to offset by 7 if negative
  int isneg = ((x>>31)&1);
  int bias = isneg+(isneg<<1)+(isneg<<2);
  //add bias of 7, then div by 8
  return (five_x+bias)>>3;
}
/* 
 * rempwr2 - Compute x%(2^n), for 0 <= n <= 30
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {
  //bias of 1 if negative
  int isneg = ((x>>31)&1);
  //calculate 2^n -1 if isneg=1, 0 if isneg=0
  int bias = (isneg<<n)+(~isneg+1);

  int xover2n = (x+bias)>>n;
  //find 2^n(x/2^n)
  int factor = xover2n<<n;
  //remainder = x-factor
  return x+(~(factor)+1);
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  //mask to get just the last n digits of any number
  int mask = ~(~0<<n);
  //shift the first n digits to the end, then isolate with mask
  int firstn = (x>>(32+(~n+1)))&mask;
  //lop off first n digits, then add them to the end
  return (x<<n)|firstn;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
  //check sign of x
  int isneg = (x>>31)&1;
  //multiplies by 2, find sign
  int mult2 = x<<1;
  int sign_mult2 = (mult2>>31)&1;
  //get 3x, find sign
  int mult3 = mult2+x;
  int sign_mult3 = (mult3>>31)&1;
  //if x vs 2x, 2x vs 3x have difft signs (all 1s if yes, all 0s if no)
  int overflow = ~((isneg^sign_mult2)|(sign_mult2^sign_mult3))+1;

  int tmax = ~(1<<31);
  //if no overflow occurred, do nothing to mult3; if it did, wipe it to all 1s
  //if x neg, set to TMin=TMax+1; if x pos, set to TMax
  return (mult3 & ~overflow) | (overflow &(isneg+tmax));
}
