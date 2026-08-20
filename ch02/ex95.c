/*
 * Homework problem 2.95 from CS:APP: Following the bit-level floating-point 
 * coding rules, implement the function with the following prototype:
 *
 *     Compute 0.5*f. If f is NaN, then return f.
 *     float_bits float_half(float_bits f);
 *
 * For floating-point number f, this function computes 0.5 ⋅ f. If f is NaN, 
 * your function should simply return f.
 * Test your function by evaluating it for all 2^32 values of argument f and
 * comparing the result to what would be obtained using your machine's floating-
 * point operations.
 */

typedef unsigned float_bits;

float_bits float_half(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	unsigned lsb = frac & 1;

	/* NaN or infinity */
	if (exp == 0xFF)
		return f;

	/* Denormalized: halve frac and return */
	if (exp == 0) {
		frac >>= 1;
		/* Round up if both the old and new lsb are 1 */
		if (lsb && (frac & 1))
			frac += 1;
		return (sign << 31) | frac;
	}

	/* Normalized: decrementing exp results in denormalization */
	if (exp == 1) {
		frac = (frac | 0x800000) >> 1;
		/* Round up if both the old and new lsb are 1 */
		if (lsb && (frac & 1))
			frac += 1;
		return (sign << 31) | frac;
	}

	/* Normalized: decrement exp and return */
	return (sign << 31) | ((exp - 1) << 23) | frac;
}

#include <math.h>
#include <stdio.h>
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
		float_bits bits_out = float_half(bits_in);
		float f_out = bits_to_float(bits_out);
		float expected = 0.5f * f_in;
		if (!isnan(f_in) && expected != f_out)
			wrong++;
		checked++;
		if (bits_in == 0xFFFFFFFF)
			break;
	}

	printf("Values checked: %lu\n", checked);
	printf("Values incorrect: %lu\n", wrong);
	return 0;
}
