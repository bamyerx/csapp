/*
 * Homework problem 2.97 from CS:APP: Following the bit-level floating-point 
 * coding rules, implement the function with the following prototype:
 *
 *     Compute (float) i. 
 *     float_bits float_i2f(int i);
 *
 * For argument i, this function computes the bit-level representation of
 * (float) i.
 * Test your function by evaluating it for all 2^32 values of argument f and
 * comparing the result to what would be obtained using your machine's floating-
 * point operations.
 */

typedef unsigned float_bits;

#include <stdio.h>

float_bits float_i2f(int i)
{
	unsigned frac = i;
	unsigned sign = (frac >> 31);

	if (i == 0)
		return 0;

	/* Magnitude of frac */
	if (sign)
		frac = -frac;

	/* Find the msb of frac */
	unsigned msb = 0;
	for (unsigned tmp = frac; tmp != 1; msb++)
		tmp >>= 1;

	/* Truncate and round if frac is too long to fit in 23 bits */
	if (msb > 23) {
		/* Number of extra bits to truncate */
		unsigned extra = msb - 23;
		/* The most significant truncated bit */
		unsigned guard = (frac >> (extra - 1)) & 1;
		/* Any nonzero bits to the right of the guard bit */
		unsigned sticky = extra > 1 && (frac & ((1 << (extra - 1)) - 1));
		/* Shift frac to truncate */
		frac >>= extra;
		unsigned lsb = frac & 1;
		/* 
		 * Round to nearest, ties to even:
		 * If the guard bit is 0, round down.
		 * If the guard bit is 1 followed by any 1s, round up.
		 * If the guard bit is 1 followed by all 0s, round up only if lsb is 1.
		 * Otherwise, round down.
		 */
		frac += guard && (sticky || lsb);

		/* Rounding caused overflow */
		if (frac == 0x1000000) {
			frac >>= 1;
			msb++;
		}

	/* Otherwise, shift left to align with bit 23 */
	} else
		frac <<= 23 - msb;

	/* E = e - bias => e = E + bias */
	unsigned exp = msb + 127;

	return (sign << 31) | (exp << 23) | (frac & 0x7FFFFF);
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

	for (int i = INT_MIN; ; i++) {
		float result = bits_to_float(float_i2f(i));
		float expected = (float) i;
		if (expected != result)
			wrong++;
		checked++;
		if (i == INT_MAX)
			break;
	}

	printf("Values checked: %lu\n", checked);
	printf("Values incorrect: %lu\n", wrong);

	return 0;
	/*
	int i;
	for (;;) {
		printf("Enter int: ");
		scanf("%d", &i);
		printf("Result: %f\n", bits_to_float(float_i2f(i)));
		printf("Expected: %f\n", (float) i);
	}
	*/

	return 0;
}
