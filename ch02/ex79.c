/*
 * Homework Problem 2.79 from CS:APP: Write code for a function mult3div4 that,
 * for integer argument x, computer 3 * x /4 but follows the bit-level integer
 * coding rules. Your code should replicate the fact that the computation 3 * x
 * can cause overflow.
 */

int mult3div4(int x)
{
	return ((x << 1) + x) >> 2;
}
