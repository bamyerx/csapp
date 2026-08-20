/*
 * Homework Problem 2.74 from CS:APP: Write a function with the following
 * prototype:
 *
 *     Determine whether arguments can be subtracted without overflow
 *     int tsub_ok(int x, int y);
 *
 * This function should return 1 if the computation x-y does not overflow.
 */

int tsub_ok(int x, int y)
{
	return !(x > 0 && y < 0 && x - y < 0) &&
		   !(x < 0 && y > 0 && x - y > 0);
}
