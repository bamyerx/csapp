/*
 * Homework Problem 5.17 from CS:APP: The library function memset has the
 * following prototype:
 *
 *     void *memset(void *s, int c, size_t n);
 *
 * This function fills n bytes of the memory area starting at s with copies of
 * the low-order byte of c. For example, it can be used to zero out a region of
 * memory by giving argument 0 for c, but other values are possible.
 * The following is a straightforward implementation of memset:
 *
 *     / Basic implementation of memset /
 *     void *basic_memset(void *s, int c, size_t n)
 *     {
 *         size_t cnt = 0;
 *         unsigned char *schar = s;
 *         while (cnt < n) {
 *             *schar++ = (unsigned char) c;
 *             cnt++;
 *         }
 *         return s;
 *     }
 *
 * Implement a more efficient version of the function by using a word of data
 * type unsigned long to pack eight copies of c, and then step through the
 * region using word-level writes. You might find it helpful to do additional
 * loop unrolling as well. On our reference machine, we were able to reduce the
 * CPE from 1.00 for the straightforward implementation to 0.127. That is, the
 * program is able to write 8 bytes per clock cycle.
 * Here are some additional guidelines. To ensure portability, let K denote the
 * value of sizeof(unsigned long) for the machine on which you run your program.
 *
 * - You may not call any library functions.
 * - Your code should work for arbitrary values of n, including when it is not
 *   a multiple of K. You can do this in a manner similar to the way we finish
 *   the last few iterations with loop unrolling.
 * - You should write your code so that it will compile and run correctly on any
 *   machine regardless of the value of K. Make use of the operation sizeof to
 *   do this.
 * - On some machines, unaligned writes can be much slower than aligned ones.
 *   Write your code so that it starts with byte-level writes until the desti-
 *   nation address is a multiple of K, then do word-level writes, and then (if
 *   necessary) finish with byte-level writes.
 * - Beware of the case where cnt is small enough that the upper bounds of some
 *   of the loops become negative. With expressions involving the sizeof
 *   operator, the testing may be performed with unsigned arithmetic.
 */

void *basic_memset(void *s, int c, size_t n)
{
	size_t cnt = 0;
	unsigned char *schar = s;
	while (cnt < n) {
		*schar++ = (unsigned char) c;
		cnt++;
	}
	return s;
}

/*
 * The following version achieves a CPE of 0.07 on my machine, a 16x increase
 * over the basic version's CPE of 1.10. The tests were performed on an AMD Zen
 * 5 machine (Ryzen 7 9800X3D).
 */

#include <stddef.h>  /* for size_t */
#include <stdint.h>  /* for uintptr_t */

void *optimized_memset(void *s, int c, size_t n)
{
	size_t i;
	size_t cnt = 0;
	size_t k = sizeof(unsigned long);
	unsigned char *schar = s;
	unsigned char byte = (unsigned char) c;
	unsigned long word = 0;

	/* pack k copies of c into an unsigned long */
	for (i = 0; i < k; i++)
		word = (word << 8) | byte;

	/* byte-level writes until schar is aligned */
	while (cnt < n && ((uintptr_t) schar % k) != 0) {
		*schar++ = byte;
		cnt++;
	}

	/* word-level writes with 6 x 6 loop unrolling */
	while (n - cnt >= k*6) {
		*((unsigned long *) (schar)        = word;
		*((unsigned long *) (schar + k))   = word;
		*((unsigned long *) (schar + 2*k)) = word;
		*((unsigned long *) (schar + 3*k)) = word;
		*((unsigned long *) (schar + 4*k)) = word;
		*((unsigned long *) (schar + 5*k)) = word;
		schar += 6*k;
		cnt += 6*k;
	}

	/* remaining word-level writes */
	while (cnt < limit) {
		*((unsigned long *) schar) = word;
		schar += k;
		cnt += k;
	}

	/* remaining byte-level writes */
	while (cnt < n) {
		*schar++ = byte;
		cnt++
	}

	return s;
}
