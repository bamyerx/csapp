/*
 * Homework Problem 2.67 from CS:APP: You are given the task of writing a
 * procedure int_size_is_32() that yields 1 when run on a machine for which an
 * int is 32 bits, and yields 0 otherwise. You are not allowed to use the
 * sizeof operator. Here is a first attempt:
 *
 *     int bad_int_size_is_32() {
 *         * Set most significant bit (msb) of 32-bit machine *
 *         int set_msb = 1 << 31;
 *         * Shift past msb of 32-bit word *
 *         int beyond_msb = 1 << 32;
 *
 *         * set_msb is nonzero when word size >= 32
 *         * beyond_msb is zero when word size <= 32
 *         return set_msb && !beyond_msb;
 *     }
 *
 * When compiled and run on a 32-bit SUN SPARC, however, this procedure returns
 * 0. The following compiler message gives us an indication of the problem:
 *
 *     warning: left shift count >= width of type
 *
 * A. In what way does our code fail to comply with the C standard?
 *
 * A left shift that is greater than or equal to the width of an integer type
 * causes undefined behavior and thus line 6 does not comply with the C
 * standard.
 *
 * B. Modify the code to run properly on any machine for which the data type int
 * is at least 32 bits.
 * C. Modify the code to run properly on any machine for which the data type int
 * is at least 16 bits.
 */

int int_size_is_32_1(void) {
	/* Set most significant bit of 32-bit machine */
	int set_msb = 1 << 31;

	/* Instead of using a 32-bit left shift, shift set_msb left by a bit */
	return set_msb && !(set_msb << 1);
}

int int_size_is_32_2(void) {
	/* We can similarly avoid shifts wider than 16 bits here */
	int set_msb = 1 << 15;
	set_msb <<= 15;
	set_msb <<= 1;

	/* The return value remains equivalent to the 32-bit machine version */
	return set_msb && !(set_msb <<1);
}
