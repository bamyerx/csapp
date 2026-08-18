/*
 * Homework Problem 2.66 from CS:APP: Write code to implement the following
 * function:
 *
 *     * Generate mask indicating leftmost 1 in x. Assume w=32.
 *     * For example, 0xFF00 -> 0x8000, and 0x6600 -> 0x4000.
 *     * If x = 0, then return 0.
 *     int leftmost_one(unsigned x);
 *
 * Your function should follow the bit-level integer coding rules, except that
 * you may assume that data type int has w = 32 bits. Your code should contain
 * at most 15 arithmetic, bitwise, and logical operations.
 */

int leftmost_one(unsigned x)
{
	/* Use successive ORs to set every bit right of the leftmost 1 */
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	/* Set the leftmost bit to 1 and every other bit to 0 */
	return x ^ (x >> 1);
}
