/*
 * Homework Problem 2.72 from CS:APP: You are given the task of writing a
 * function that will copy an integer val into a buffer buf, but it should 
 * do so only if enough space is available in the buffer.
 * Here is the code you write:
 *
 *     Copy integer into buffer if space is available
 *     WARNING: The following code is buggy
 *     void copy_int(int val, void *buf, int maxbytes) {
 *         if (maxbytes-sizeof(val) >= 0)
 *                 memcpy(buf, (void *) &val, sizeof(val));
 *     }
 *
 * This code makes use of the library function memcpy. Although its use is a
 * bit artificial here, where we simply want to copy an int, it illustrates an
 * approach commonly used to copy larger data structures.
 * You carefully test the code and discover that it always copies the value to
 * the buffer, even when maxbytes is too small.
 *
 * A. Explain why the conditional test in the code always succeeds.
 * 
 * The conditional test always succeeds because sizeof(val) has type size_t,
 * which is an unsigned integer type. maxbytes will be cast to size_t for the 
 * expression on the left side of the test, so when sizeof(val) > maxbytes,
 * maxbytes - sizeof(val) yields a large positive value instead of a negative
 * one.
 *
 * B. Show how you can rewrite the conditional test to make it work properly.
 *
 * We can simply remove the comparison to 0 and compare maxbytes and sizeof(val)
 * directly. As a side note, maxbytes should also probably have type size_t.
 */

void copy_int(int val, void *buf, int maxbytes) {
	if (maxbytes >= sizeof(val))
		memcpy(buf, (void *) &val, sizeof(val));
}
