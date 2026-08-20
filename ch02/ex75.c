/*
 * Homework Problem 2.75 from CS:APP: Suppose we want to compute the 2w-bit
 * representation of x · y, where x and y are unsigned, on a machine for which
 * data type unsigned is w bits. The low-order w bits of the product can be
 * computed with the expression x*y, so we only require a procedure with
 * prototype:
 *
 *     unsigned unsigned_high_prod(unsigned x, unsigned y);
 *
 * that computes the high-order w bits of x · y for unsigned variables.
 * We have access to a library function with prototype
 *
 *     int signed_high_prod(int x, int y);
 *
 * that computes the high-order w bits of x · y for the case where x and y are
 * in two's complement form. Write code calling this procedure to implement the
 * function for unsigned arguments. Justify the correctness of your solution.
 */

/*
 * Justification: Let x, y, sx, and sy be defined as below. Then, for 
 * multiplication modulo 2^(2w), equation 2.18 shows that
 *
 *     (x · y) mod 2^(2w) = [(sx · sy) + (x_(w-1)y + y_(w-1)x)2^w] mod 2^(2w)
 *
 * x_(w-1) is the sign bit of x and y_(w-1) is the sign bit of y in their two's
 * complement representation. So, we simply add the value of y to the high-order
 * bits if sx < 0 and add the value of x if sy < 0.
 */
unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int sx = (int) x;
	int sy = (int) y;

	/* First, get the signed high-order w bits */
	unsigned u = (unsigned) signed_high_prod(sx, sy);

	/* If x's sign bit is 1, add y to the high-order bits */
	if (sx < 0)
		u += y;
	/* If y's sign bit is 1, add x to the high-order bits */
	if (sy < 0)
		u += x;

	return u;
}
