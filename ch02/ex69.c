/*
 * Homework Problem 2.69 from CS:APP: Write code for a function with the 
 * following prototype:
 *
 *     Do rotating left shift. Assume 0 <= n < w.
 *     Examples when x = 0x12345678 and w = 32:
 *         n=4 -> 0x23456781, n=20 -> 0x67812345
 *
 *     unsigned rotate_left(unsigned x, int n);
 *
 * Your function should follow the bit-level integer coding rules. Be careful of
 * the case n = 0.
 */

unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(int) << 3;

	/* A mask for extracting the leftmost n bits of x, or 0 if n = 0 */
	unsigned mask = (~0 << (w - n - 1)) << 1;

	/* Extract the leftmost n bits of x and shift it right by n */
	unsigned left_bits = (x & mask) >> (w - n);

	/* Shift x left by n and add back the left n bits to the right */
	return (x << n) + left_bits;
}
