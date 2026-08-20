/*
 * Homework Problem 2.78 from CS:APP: Write code for a function with the
 * following prototype:
 *
 *     Divide by power of 2. Assume 0 <= k < w-1
 *     int divide_power2(int x, int k);
 *
 * The function should compute x/2^k with correct rounding, and it should follow
 * the bit-level integer coding rules.
 */

int divide_power2(int x, int k)
{
	int w = sizeof(int) << 3;

	/* Bias is (1 << k) - 1 if x is negative, 0 otherwise */
	int bias = (x >> (w - 1)) & ((1 << k) - 1);

	/* Adding the bias ensures rounding toward zero */
	return (x + bias) >> k;
}
