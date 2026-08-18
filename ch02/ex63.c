/*
 * Homework Problem 2.63 from CS:APP: Fill in code for the following C functions.
 * Function srl performs a logical right shift using an arithmetic right shift
 * (given by value xsra), followed by other operations not including right
 * shifts or division. Function sra performs an arithmetic right shift using 
 * using a logical right shift (given by xsrl), followed by other operations not
 * including right shifts or division. You may use the computation 8*sizeof(int)
 * to determine w, the number of bits in data type int. The shift amount k can
 * range from 0 to w - 1.
 */

unsigned srl(unsigned x, int k)
{
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	
	/* If unshifted, we are done */
	if (k == 0)
		return xsra;

	/* Create a mask of k ones followed by w-k zeroes */
	unsigned mask = ~0 << (8*sizeof(int) - k);

	/* Clear the k most significant bits and return */
	return xsra & ~mask;
}

int sra(int x, int k)
{
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;

	/* If unshifted, we are done */
	if (k == 0)
		return xsrl;

	/* If the original sign bit is zero, we are done */
	if (!(xsrl & (1u << (8*sizeof(int) - k - 1))))
		return xsrl;

	/* Create a mask of k ones followed by w-k zeroes */
	int mask = ~0 << (8*sizeof(int) - k);

	/* Set the k most significant bits and return */
	return xsrl | mask;
}
