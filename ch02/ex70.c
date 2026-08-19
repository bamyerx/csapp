/*
 * Homework Problem 2.70 from CS:APP: Write code for the function with the
 * following prototype:
 *
 *     Return 1 when x can be represented as an n-bit, 2's complement
 *     number; 0 otherwise
 *     Assume 1 <= n <= w
 *
 *     int fits_bits(int x, int n);
 *
 * Your function should follow the bit-level integer coding rules.
 */

int fits_bits(int x, int n)
{
	/* Shift x left by n - 1 */
	x >>= (n - 1);

	/* If x fits, x is -1 or 0 */
	return (x == -1) || (x == 0);
}
