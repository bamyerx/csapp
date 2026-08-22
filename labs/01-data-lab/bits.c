/* 
 * CS:APP Data Lab 
 * 
 * Bennett A. Myers
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/* rewrite (x | y) & ~(x & y) in terms of ~ and & */
	return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* TMin is a 1 followed by 31 0s */
	return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	/* exploit that TMin = TMax + 1 and rule out that x = -1 */
	return !((x ^ (x + 1)) + 1) & !!(x + 1);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	/* mask each byte with that byte's odd bits */
	return !(0xAA ^
			((x        & 0xAA) & 
			((x >> 8)  & 0xAA) & 
			((x >> 16) & 0xAA) & 
			((x >> 24) & 0xAA)));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/* exploit the fact that x + ~x = -1 */
	return ~x + 1;
}
//3
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
	/* upper nibble must be 0x3 with no leading bits in x */
	int upper_nibble_is_3 = !((x >> 4) ^ 3);
	/* lower nibble must be 0-9 */
	int lower = x & 0xF;
	int lower_nibble_is_digit = !(lower & 8) | !(lower ^ 8) | !(lower ^ 9);
	
	return upper_nibble_is_3 & lower_nibble_is_digit;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* 0xFFFFFFFF if x != 0, 0 if x = 0 */
	int xmask = (!!x << 31) >> 31;
	
	return (xmask & y) | (~xmask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* 0xFFFFFFFF if negative, 0 otherwise */
	int xsign = x >> 31;
	int ysign = y >> 31;
	/* the additive inverse of y */
	int yneg = ~y + 1;
	/* the sign for x - y */
	int subsign = (x + yneg) >> 31;
	/* for x <= y to be true: */
	/* necessary: exclude the case that x is nonnegative and y is negative */
	int ncond1 = !(!xsign & ysign);
	/* sufficient: x and y are equal */
	int scond1 = !(x ^ y);
	/* sufficient: x is negative and y is nonnegative */
	int scond2 = (xsign & !ysign);
	/* sufficient: x and y both have the same sign and x - y is negative */
	int scond3 = !(xsign ^ ysign) & subsign;
	
	return ncond1 & (scond1 | scond2 | scond3);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/* 
	 * for x != 0, sign(x) | sign(-x) = 1, and 0 for x = 0
	 * so with sign extension, we have
	 *     x != 0 => -1 + 1 = 0
	 *     x == 0 =>  0 + 1 = 1
	 */
	return ((x | (~x + 1)) >> 31) + 1;
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
	/* 0xFFFFFFFF if x is negative, 0 otherwise */
	int sign = x >> 31;
	int nbits = 0;
	int b16, b8, b4, b2, b1;
	/* if x is negative, take the complement */
	x = (~sign & x) | (sign & ~x);
	/* 
	 * find the position of the most significant bit by binary search:
	 * - for each pass, check if the msb is in the upper or lower half
	 * - encode and accumulate the positional data in nbits
	 * - shift x based on where the msb was found
	 */
	b16 = !!(x >> 16);
	nbits += b16 << 4;
	x >>= b16 << 4;
	b8 = !!(x >> 8);
	nbits += b8 << 3;
	x >>= b8 << 3;
	b4 = !!(x >> 4);
	nbits += b4 << 2;
	x >>= b4 << 2;
	b2 = !!(x >> 2);
	nbits += b2 << 1;
	x >>= b2 << 1;
	b1 = !!(x >> 1);
	nbits += b1;
	x >>= b1;
	nbits += x;

	/* add an extra bit for the sign bit */
	return nbits + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	unsigned sign = uf >> 31;
	unsigned exp = (uf >> 23) & 0xFF;
	unsigned frac = uf & 0x7FFFFF;
	/* NaN or infinity */
	if (exp == 0xFF)
		return uf;
	/* normalized; overflow */
	if (exp == 0xFE)
		return (sign << 31) | (0xFF << 23);
	/* normalized; no overflow */
	if (exp != 0)
		return (sign << 31) | ((exp + 1) << 23) | frac;
	/* denormalized */
	return (sign << 31) | (frac << 1);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	unsigned sign = uf >> 31;
	unsigned exp = (uf >> 23) & 0xFF;
	unsigned frac = uf & 0x7FFFFF;
	/* Nan or infinity */
	if (exp == 0xFF)
		return 0x80000000;
	/* 0 <= uf < 1 */
	if (exp < 127)
		return 0;
	/* adjust exp by 8-bit bias of 127 and the 23 bits of frac*/
	exp -= 127;
	/* out of range */
	if (exp > 31 || (exp == 31 && !sign))
		return 0x80000000;
	/* combine frac with the "implied" leading 1 */
	frac |= 0x800000;
	/* shift frac to the correct order of magnitude */
	if (exp > 23)
		frac <<= (exp - 23);
	else
		frac >>= (23 - exp);
	/* return two's complement form */
	if (sign)
		return ~frac + 1;
	else
		return frac;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	/* 
	 * an explanation of the magic numbers:
	 * the largest normal value is 2^127 = 0x7F000000
	 *     - this has floating point representation 0x7F000000
	 *     - sign = 0, exp = 0xFE, frac = 0x000000
	 * the smallest normal value is 2^(-126): 0x00800000
	 *     - this has floating point representation 0x00800000
	 *     - sign = 0, exp = 0x01, frac = 0x000000
	 * the smallest denormal value is 2^(-126 - 23) = 2^(-149)
	 *     - this has floating point representation 0x00000001
	 *     - sign = 0, exp = 0x00, frac = 0x000001
	 */
    unsigned exp = 0;
	unsigned frac = 0;
	/* overflow */
	if (x > 127)
		return 0xFF << 23;
	/* underflow */
	if (x < -149)
		return 0;
	/* normalized: -126 <= x <= 127 */
	if (x > -127)
		exp = x + 127;
	/* denormalized: -149 <= x < -126 */
	else
		frac = 1 << (23 - (-x - 126));

	return (exp << 23) | frac;
}
