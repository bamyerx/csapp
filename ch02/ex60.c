/*
 * Homework Problem 2.60 from CS:APP: Suppose we number the bytes in a w-bit
 * word from 0 (least significant) to w/8 - 1 (most significant). Write code for
 * the following C function, which will return an unsigned value in which byte i
 * of argument x has been replaced by byte b:
 *
 *     unsigned replace_byte(unsigned x, int i, unsigned char b);
 */

#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	unsigned result = x;

	result &= ~(0xFF << (i * 8));
	result |= b << (i * 8);

	return result;
}

int main(void)
{
	printf("replace_byte(0x12345678, 2, 0xAB) --> %x\n",
			replace_byte(0x12345678, 2, 0xAB));
	printf("replace_byte(0x12345678, 0, 0xAB) --> %x\n",
			replace_byte(0x12345678, 0, 0xAB));

	return 0;
}
