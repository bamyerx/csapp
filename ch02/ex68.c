/*
 * Homework Problem 2.68 from CS:APP: Write code for a function with the
 * following prototype:
 *
 *     Mask with least significant n bits set to 1
 *     Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 *     Assume 1 <= n <= w
 *
 *     int lower_one_mask(int n);
 *
 * Your function should follow the bit-level integer coding rules. Be careful of
 * the case n = w.
 */

int lower_one_mask(int n)
{
	int w = sizeof(int) << 3;
	
	/* Start with the most significant bit set */
	int mask = 1 << (w - 1);

	/* (w - n) 1s followed by n 0s */
	mask >>= (w - n - 1);

	/* the n least significant bits are set */
	return ~mask;
}
