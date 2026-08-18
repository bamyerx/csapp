/*
 * Homework Problem 2.60 from Chapter 2 of CS:APP: Write a procedure
 * is_little_endian that will return 1 when compiled and run on a little-endian
 * machine, and will return 0 when compiled and run on a big-endian machine.
 * This program should run on any machine, regardless of its word size.
 */

#include <stdio.h>

typedef unsigned char *byte_pointer;

int is_little_endian(void)
{
	int x = 0x11FF;
	byte_pointer bp = (byte_pointer) &x;

	return *bp == 0xFF;
}

int main(void)
{
	if (is_little_endian)
		printf("Little-endian\n");
	else
		printf("Big-endian\n");

	return 0;
}
