/*
 * Homework Problem 2.65 from CS:APP: Write code to implement the following
 * function:
 *
 *     * Return 1 when x contains an odd number of 1s; 0 otherwise. 
 *       Assume w=32 *
 *     int odd_ones(unsigned x);
 *
 * Your function should follow the bit-level integer coding rules, except that
 * it may assume that data type int has w = 32 bits. Your code should contain a
 * total of at most 12 arithmetic, bitwise, and logical operations.
 */

int odd_ones(unsigned x)
{
	/* Each pass, cancel bits from each half using XOR */
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	
	/* The least significant bit will be set if bit count is odd */
	return x & 1;
}
