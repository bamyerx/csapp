/*
 * Homework problem 2.94 from CS:APP: Following the bit-level floating-point 
 * coding rules, implement the function with the following prototype:
 *
 *     Compute 2*f. If f is NaN, then return f.
 *     float_bits float_twice(float_bits f);
 *
 * For floating-point number f, this function computes 2.0 ⋅ f. If f is NaN, 
 * your function should simply return f.
 * Test your function by evaluating it for all 2^32 values of argument f and
 * comparing the result to what would be obtained using your machine's floating-
 * point operations.
 */

typedef unsigned float_bits;

float_bits float_twice(float_bits f)
{
	unsigned sign = f >> 31;
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	/* NaN or infinity */
	if (exp == 0xFF)
		return f;

	/* Denormalized: double frac and return */
	if (exp == 0)
		return (sign << 31) | (frac << 1);

	/* Normalized: incrementing exp results in infinity */
	if (exp == 0xFE)
		return (sign << 31) | (0xFF << 23);

	/* Normalized: increment exp and return */
	return f + (1 << 23);
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
		float_bits bits_out = float_twice(bits_in);
		float f_out = bits_to_float(bits_out);
		float expected = 2.0f * f_in;
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
