/*
 * Homework Problem 2.71 from CS:APP: You just started working for a company
 * that is implementing a set of procedures to operate on a data structure where
 * 4 signed bytes are packed into a 32-bit unsigned. Bytes within the word are
 * numbered from 0 (least significant) to 3 (most significant). You have been
 * assigned the task of implementing a function for a machine using two's
 * complement arithmetic and arithmetic right shifts with the following proto-
 * type:
 *
 *     Declaration of data type where 4 bytes are packed into an unsigned
 *     typedef unsigned packed_t
 *
 *     Extract byte from word. Return as signed integer.
 *     int xbyte(packed_t word, int bytenum);
 *
 * That is, the function will extract the designated byte and sign extend it to
 * be a 32-bit int.
 * Your predecessor (who was fired for incompetence) wrote the following code:
 *
 *     Failed attempt at xbyte
 *     int xbyte(packed_t word, int bytenum)
 *     {
 *         return (word >> (bytenum << 3)) & 0xFF;
 *     }
 * 
 * A. What is wrong with this code?
 *
 * The code shifts the specified byte into position and clears the upper three
 * bytes but does not perform sign extension when the sign bit is set.
 *
 * B. Give a correct implementation of the function that uses only left and
 * right shifts, along with one subtraction.
 */

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
	/* Shift the desired byte all the way left first, then cast to int
	   This way, the arithmetic right shift will ensure sign extension */
	return (int) (word << (24 - (bytenum << 3))) >> 24;
}
