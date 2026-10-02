/*
 * Homework Problem 5.18 from CS:APP: We considered the task of polynomial eval-
 * uation in Practice Problems 5.5 and 5.6, with both a direct evaluation and an
 * evaulation by Horner's method. Try to write faster versions of the function
 * using the optimization techniques we have explored, including loop unrolling,
 * parallel accumulation, and reassociation. You will find many different ways
 * of mixing together Horner's scheme and direct evaluation with these optimi-
 * zation techniques.
 * Ideally, you should be able to reach a CPE close to the throughput limit of
 * your machine. Our best version achieves a CPE of 1.07 on our reference
 * machine.
 */

/*
 * Rather than combining direct evaluation and Horner's method in a single
 * optimized function, I instead wrote two functions: one that optimizes direct
 * evaluation and another that optimizes Horner's method. I ran some tests to
 * try to ascertain the sweet spot with regard to the number of factors for
 * loop unrolling and the factors that gave me the best results were 8x8
 * unrolling for direct evaluation and 13x13 unrolling for Horner's method.
 * On my AMD Zen 5 (Ryzen 7 9800X3D) machine, this resulted in a CPE of 0.44 for
 * the optimized direct evaluation, a 8.25x increase in speed, and a CPE of 0.88
 * for the optimized Horner's method, a 11.8x increase in speed.
 */

/* original direct evaluation function (CPE = 3.63) */
double poly(double a[], double x, long degree)
{
	long i;
	double result = a[0];
	double xpwr = x;
	for (i = 1; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
}

/* original Horner's method function (CPE = 5.21) */
double polyh(double a[], double x, long degree)
{
	long i;
	double result = a[degree];
	for (i = degree-1; i >= 0; i--)
		result = a[i] + x*result;
	return result;
}

/* an optimized version of direct evaluation using 8 x 8 loop unrolling (CPE = 0.88) */
double poly_optimized(double a[], double x, long degree)
{
	long i, limit;
	double result;
	double xpwr0, xpwr1, xpwr2, xpwr3, xpwr4, xpwr5, xpwr6, xpwr7, x8;
	double acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7;

	/* initialize each power of x */
	xpwr0 = x;
	xpwr1 = xpwr0 * x;
	xpwr2 = xpwr1 * x;
	xpwr3 = xpwr2 * x;
	xpwr4 = xpwr3 * x;
	xpwr5 = xpwr4 * x;
	xpwr6 = xpwr5 * x;
	xpwr7 = xpwr6 * x;

	/* x^8 */
	x8 = xpwr7;

	/* initialize each accumulator */
	acc0 = a[0];
	acc1 = acc2 = acc3 = acc4 = acc5 = acc6 = acc7 = 0;

	/* 8x8 loop unrolling */
	i = 1;
	limit = degree - 7;
	while (i <= limit) {
		acc0 += a[i]   * xpwr0;
		acc1 += a[i+1] * xpwr1;
		acc2 += a[i+2] * xpwr2;
		acc3 += a[i+3] * xpwr3;
		acc4 += a[i+4] * xpwr4;
		acc5 += a[i+5] * xpwr5;
		acc6 += a[i+6] * xpwr6;
		acc7 += a[i+7] * xpwr7;
		xpwr0 *= x8;
		xpwr1 *= x8;
		xpwr2 *= x8;
		xpwr3 *= x8;
		xpwr4 *= x8;
		xpwr5 *= x8;
		xpwr6 *= x8;
		xpwr7 *= x8;
		i += 8;
	}

	result = acc0 + acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7;

	/* compute remaining terms */
	while (i <= degree) {
		result += a[i++] * xpwr0;
		xpwr0 *= x;
	}

	return result;
}

/* an optimized version of Horner's method using 13 x 13 loop unrolling (CPE = 0.44) */
double polyh_optimized(double a[], double x, long degree)
{
	long i;
	long r = degree % 13;
    double result, acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10, acc11, acc12;

	double x2 = x * x;
	double x3 = x * x2;
	double x4 = x * x3;
	double x5 = x * x4;
	double x6 = x * x5;
	double x7 = x * x6;
	double x8 = x * x7;
	double x9 = x * x8;
	double x10 = x * x9;
	double x11 = x * x10;
	double x12 = x * x11;
	double x13 = x * x12;

	/* initialize the accumulators with the highest term modulo 13 */
	i = degree - r;
	acc0 = a[i];
	acc1 = r >= 1 ? a[i+1] : 0;
	acc2 = r >= 2 ? a[i+2] : 0;
	acc3 = r >= 3 ? a[i+3] : 0;
	acc4 = r >= 4 ? a[i+4] : 0;
	acc5 = r >= 5 ? a[i+5] : 0;
	acc6 = r >= 6 ? a[i+6] : 0;
	acc7 = r >= 7 ? a[i+7] : 0;
	acc8 = r >= 8 ? a[i+8] : 0;
	acc9 = r >= 9 ? a[i+9] : 0;
	acc10 = r >= 10 ? a[i+10] : 0;
	acc11 = r >= 11 ? a[i+11] : 0;
	acc12 = r >= 12 ? a[i+12] : 0;
	i -= 13;

	/* decomposed 13-way Horner's method */
    while (i >= 0) {
        acc0 = a[i]   + x13 * acc0;
		acc1 = a[i+1] + x13 * acc1;
		acc2 = a[i+2] + x13 * acc2;
		acc3 = a[i+3] + x13 * acc3;
		acc4 = a[i+4] + x13 * acc4;
		acc5 = a[i+5] + x13 * acc5;
		acc6 = a[i+6] + x13 * acc6;
		acc7 = a[i+7] + x13 * acc7;
		acc8 = a[i+8] + x13 * acc8;
		acc9 = a[i+9] + x13 * acc9;
		acc10 = a[i+10] + x13 * acc10;
		acc11 = a[i+11] + x13 * acc11;
		acc12 = a[i+12] + x13 * acc12;
		i -= 13;
	}

	result = acc0 + x*acc1 + x2*acc2 + x3*acc3 + x4*acc4 + x5*acc5 + x6*acc6 + 
		x7*acc7 + x8*acc8 + x9*acc9 + x10*acc10 + x11*acc11 + x12*acc12;

    return result;
}

