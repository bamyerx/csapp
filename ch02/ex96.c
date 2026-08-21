/*
 * Homework problem 2.96 from CS:APP: Following the bit-level floating-point 
 * coding rules, implement the function with the following prototype:
 *
 *     Compute (int) f. 
 *     If conversion causes overflow or f is NaN, return 0x80000000.
 *     int float_f2i(float_bits f);
 *
 * For floating-point number f, this function computes (int) f. Your function
 * should round toward zero. If f cannot be represented as an integer (e.g., it
 * is out of range, or it is NaN), then the function should return 0x80000000.
 * Test your function by evaluating it for all 2^32 values of argument f and
 * comparing the result to what would be obtained using your machine's floating-
 * point operations.
 */

typedef unsigned float_bits;

#include <stdio.h>

int float_f2i(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	/* NaN or infinity */
	if (exp == 0xFF)
		return 0x80000000;

	/* If exp < 127, then 0 <= f < 1, so return 0 */
	if (exp < 127)
		return 0;

	/* Compute E with bias = 127 for an 8-bit exponent */
	int e = exp - 127;

	/* If e is greater than 31 or is exactly 31 and f is positive, overflow */
	if (e > 31 || (e == 31 && !sign))
		return 0x80000000;

	/* Combine frac with the leading 1 */
	frac |= 0x800000;

	/* Adjust e to account for the 24 bits of frac with the leading 1 */
	e -= 23;

	/* Shift frac by e to arrive at the correct power of 2 */
	if (e > 0)
		frac <<= e;
	else if (e < 0)
		frac >>= -e;

	/* Return the correct two's complement form based on the sign bit of f */
	if (sign)
		return -frac;
	else
		return frac;
}

#include <math.h>
#include <limits.h>
#include <string.h>

float bits_to_float(float_bits bits)
{
	float f;
	memcpy(&f, &bits, sizeof(f));
	return f;
}

int main(void)
{
	unsigned long checked = 0;
	unsigned long wrong = 0;

	for (float_bits bits_in = 0; ; bits_in++) {
		float f_in = bits_to_float(bits_in);
		int result = float_f2i(bits_in);
		int expected = (int) f_in;
		if (!isnan(f_in) && f_in <= INT_MAX && f_in >= INT_MIN && expected != result)
			wrong++;
		checked++;
		if (bits_in == 0xFFFFFFFF)
			break;
	}

	printf("Values checked: %lu\n", checked);
	printf("Values incorrect: %lu\n", wrong);

	return 0;
}
