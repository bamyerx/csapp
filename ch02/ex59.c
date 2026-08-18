/*
 * Homework Problem 2.59 from CS:APP: Write a C expression that will yield a
 * word consisting of the least significant byte of x and the remaining bytes
 * of y.
 */

#include <stdio.h>

int main(void)
{
	int x = 0x89ABCDEF;
	int y = 0x76543210;

	int result = (x & 0xFF) | (y & ~0xFF);

	printf("result = %x\n", result);
}
