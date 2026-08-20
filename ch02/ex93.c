/*
 * Homework problem 2.93 from CS:APP: Following the bit-level floating-point 
 * coding rules, implement the function with the following prototype:
 *
 *     Compute |f|. If f is NaN, then return f.
 *     float_bits float_absval(float_bits f);
 *
 * For floating-point number f, this function computes |f|. If f is NaN, your
 * function should simply return f.
 * Test your function by evaluating it for all 2^32 values of argument f and
 * comparing the result to what would be obtained using your machine's floating-
 * point operations.
 */

typedef unsigned float_bits;

float_bits float_absval(float_bits f)
{
	unsigned exp = (f >> 23) & 0xFF;
	unsigned frac = f & 0x7FFFFF;

	/* NaN */
	if (exp == 0xFF && frac != 0)
		return f;

	/* Ensure sign bit is 0 */
	return f & ~(1 << 31);
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
		float_bits bits_out = float_absval(bits_in);
		float f_out = bits_to_float(bits_out);
		float expected = fabsf(f_in);
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
