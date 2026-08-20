/*
 * Homework Problem 2.80 from CS:APP: Write code for a function threefourths
 * that, for integer argument x, computes the value of (3/4)x, rounded toward
 * zero. It should not overflow. Your function should follow the bit-level
 * integer coding rules.
 */

int threefourths(int x)
{
	int w = sizeof(int) << 3;

	/* bias = 3 for negative x, 0 otherwise */
	int bias = (x >> (w - 1)) & 3;

	/* Divide x by 4 first to prevent overflow */
	int x_4 = (x + bias) >> 2;

	/* Subtract x/4 from x */
	return x - x_4;
}
