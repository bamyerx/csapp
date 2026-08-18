/*
 * Homework Problem 2.61 from CS:APP: Write C expressions that evaluate to 1
 * when the following conditions are true and to 0 when they are false. Assume
 * x is of type int.
 *
 *     A. Any bit of x equals 1.
 *     B. Any bit of x equals 0.
 *     C. Any bit in the least significant byte of x equals 1.
 *     D. Any bit in the most significant byte of x equals 0.
 *
 * Your code should follow the bit-level integer coding rules, with the
 * additional that you may not use equality (==) or inequality (!=) tests.
 */

/* Check if x is non-zero */
!!x;

/* Check if the complement of x is zero */
!!~x;

/* Mask off all but the least significant byte and check if non-zero */
!!(x & 0xFF);

/* Shift x right by w-8, then check if  */
!((x >> ((sizeof(int)-1)<<3)) & 0xFF);
