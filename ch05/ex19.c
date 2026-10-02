/*
 * Homework Problem 5.19 from CS:APP: In Problem 5.12, we were able to reduce
 * the CPE for the prefix-sum computation to 3.00, limited by the latency of
 * floating-point addition on this machine. Simple loop unrolling does not
 * improve things.
 * Using a combination of loop unrolling and reassociation, write code for a
 * prefix sum that achieves a CPE less than the latency of floating-point
 * addition on your machine. Doing this requires actually increasing the number
 * of additions performed. For example, our version with two-way unrolling
 * requires three additions per iteration, while our version with four-way
 * unrolling requires five. Our best implementation achieves a CPE of 1.67 on
 * our reference machine.
 * Determine how the throughput and latency limits of your machine limit the
 * minimum CPE you can achieve for the prefix-sum operation.
 */

/*
 * I attempted a number of combinations of loop unrolling and reassociation and
 * I found that the sweet spot for my machine was an implementation that used
 * 3-way loop unrolling, which achieved a CPE of 0.96 on my machine.
 *
 * Based on the specs and from what I've experimentally verified, my machine has
 * a floating point addition latency bound of 2.00 and throughput bound of 0.50.
 * My three best algorithms were a 2-way, 3-way, and 4-way unrolled versions
 * with three, four, and eight addition operations per iteration, respectively
 * (despite my best efforts, I could not figure out a five-addition version of
 * the 4-way unrolling that performed better than the eight-addition version).
 * The bounds on my machine would theoretically limit the CPE floor for these
 * implementation as follows:
 *
 * 2-way: 3 additions / 2 elements = 1.5 additions/element
 *        1.5 additions/element * 0.5 throughput per addition = 0.75 CPE
 *
 * 3-way: 5 additions / 3 elements = 1.67 additions/element
 *        1.67 additions/element * 0.5 throughput per addition = 0.83 CPE
 *
 * 4-way: 8 additions / 4 elements = 2 additions/element
 *        2 additions/element * 0.5 throughput per addition = 1 CPE
 *
 * In practice, however, the 2-way version was the farthest from its floor and
 * while the 4-way version was closest to its floor, its floor was higher than
 * what the 3-way version achieved.
 */

/* Prefix sum routine from Figure 5.1 (CPE = 13.32) */
void psum1(float a[], float p[], long n)
{
	long i;
	p[0] = a[0];
	for (i = 1; i < n; i++)
		p[i] = p[i-1] + a[i];
}

/* Prefix sum routine from Figure 5.1 (CPE = 7.77) */
void psum2(float a[], float p[], long n)
{
	long i;
	p[0] = a[0];
	for (i = 1; i < n-1; i+=2) {
		float mid_val = p[i-1] + a[i];
		p[i]   = mid_val;
		p[i+1] = mid_val + a[i+1];
	}
	/* For even n, finish remaining elements */
	if (i < n)
		p[i] = p[i-1] + a[i];
}

/* Solution for Problem 5.12 (CPE = 2.22) */
void psum1a(float a[], float p[], long n)
{
	long i;

	float last_val, val;
	last_val = p[0] = a[0];
	for (i = 1; i < n; i++) {
		val = last_val + a[i];
		p[i] = val;
		last_val = val;
	}
}

/* Optimized version with 2-way unrolling (CPE = 1.25) */
void psum2way(float a[], float p[], long n)
{
	long i, limit;
	float val0, val1;

	val0 = p[0] = a[0];
	if (n >= 1) val1 = p[1] = p[0] + a[1];

	limit = n - 2;
	for (i = 2; i < limit; i += 2) {
		val0 = val1 + a[i];
		val1 = val1 + (a[i] + a[i+1]);
		p[i] = val0;
		p[i+1] = val1;
	}

	for (; i < n; i++) {
		val0 = val1 + a[i];
		p[i] = val0;
		val1 = val0;
	}

}

/* Optimized version with 3-way unrolling (CPE = 0.96) */
void psum3way(float a[], float p[], long n)
{
	long i, limit;
	float val0, val1, val2, sum;

	val0 = p[0] = a[0];
	if (n >= 1) val1 = p[1] = a[1] + p[0];
	if (n >= 2) val2 = p[2] = a[2] + p[1];

	limit = n - 2;
	for (i = 3; i < limit; i += 3) {
		sum = a[i] + a[i+1];
		val0 = val2 + a[i];
		val1 = val2 + sum;
		val2 = val2 + (sum + a[i+2]);
		p[i] = val0;
		p[i+1] = val1;
		p[i+2] = val2;
	}

	for (; i < n; i++)
		p[i] = p[i-1] + a[i];
}

/* Optimized version with 4-way unrolling (CPE = 1.11) */
void psum4way(float a[], float p[], long n)
{
	long i, limit;
	float val0, val1, val2, val3, sum0, sum1;

	val0 = p[0] = a[0];
	if (n >= 1) val1 = p[1] = a[1] + p[0];
	if (n >= 2) val2 = p[2] = a[2] + p[1];
	if (n >= 3) val3 = p[3] = a[3] + p[2];

	limit = n - 3;
	for (i = 4; i < limit; i += 4) {
		sum0 = a[i] + a[i+1];
		sum1 = a[i+2] + a[i+3];
		val0 = val3 + a[i];
		val1 = val3 + sum0;
		val2 = val3 + (sum0 + a[i+2]);
		val3 = val3 + (sum0 + sum1);
		p[i] = val0;
		p[i+1] = val1;
		p[i+2] = val2;
		p[i+3] = val3;
	}

	for (; i < n; i++)
		p[i] = p[i-1] + a[i];
}
