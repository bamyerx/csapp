/*
 * Homework Problem 2.62 from CS:APP: Write a function 
 * int_shifts_are_arithmetic() that yields 1 when run on a machine that uses
 * arithmetic right shifts for data type int and yields 0 otherwise. Your code
 * should work on a machine with any word size.
 */

#include <stdio.h>

int int_shifts_are_arithmetic(void)
{
	return (-1 >> 8) == -1;
}

int main(void)
{
	if (int_shifts_are_arithmetic())
		printf("Int shifts are arithmetic\n");
	else
		printf("Int shifts are logical\n");

	return 0;
}
