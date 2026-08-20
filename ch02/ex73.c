/*
 * Homework Problem 2.73 from CS:APP: Write code for a function with the
 * following prototype:
 *
 *     Addition that saturates to TMin or TMax
 *     int saturating_add(int x, int y);
 *
 * Instead of overflowing the way normal two's complement addition does,
 * saturating addition returns TMax when there would be positive overflow, and
 * TMin when there would be negative overflow.
 * Your function should follow the bit-level integer coding rules.
 */

#include <limits.h>

int saturating_add(int x, int y)
{
	int w = sizeof(int) << 3;

	/* Determine the signs of x, y, and their sum */
	int x_sign = (x >> (w - 1)) & 1;
	int y_sign = (y >> (w - 1)) & 1;
	int sum_sign = ((x + y) >> (w - 1)) & 1;

	/* 
	 * Overflow occurs if and only if x and y have the same sign but their sum
	 * has a different sign from x (or equivalently from y).
	 */
	int overflow = !(x_sign ^ y_sign) & (x_sign ^ sum_sign);

	/* Mask of all ones for overflow, all zeros otherwise */
	int mask = ~overflow + 1;

	/*
	 * No overflow: mask = 0 so ~mask = -1 and will return x + y.
	 * Positive overflow: mask = -1 and sum_sign = 1 and will return
	 *                    INT_MIN - 1 = INT_MAX.
	 * Negative overflow: mask = -1 and sum_sign = 0 and will return INT_MIN.
	 */
	return ((x + y) & ~mask) | ((INT_MIN - sum_sign) & mask);
}
