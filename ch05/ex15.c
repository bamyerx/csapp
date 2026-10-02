/*
 * Homework Problem 5.15 from CS:APP: Write a version of the inner product
 * procedure described in Problem 5.13 that uses 6 x 6 loop unrolling. Our
 * measurements for this function with x86-64 give a CPE of 1.06 for integer
 * data and 1.01 for floating-point data.
 *
 * long i;
 * long length = vec_length(u);
 * long limit = length - 5;
 * data_t *udata = get_vec_start(u);
 * data_t *vdata = get_vec_start(v);
 * data_t sum0, sum1, sum2, sum3, sum4, sum5;
 *
 * sum0 = sum1 = sum2 = sum3 = sum4 = sum5 = (data_t) 0;
 *
 * for (i = 0; i < limit; i += 6) {
 *     sum0 += udata[i] * vdata[i];
 *     sum1 += udata[i+1] * vdata[i+1];
 *     sum2 += udata[i+2] * vdata[i+2];
 *     sum3 += udata[i+3] * vdata[i+3];
 *     sum4 += udata[i+4] * vdata[i+4];
 *     sum5 += udata[i+5] * vdata[i+5];
 * }
 *
 * sum0 += (sum1 + sum2 + sum3 + sum4 + sum5);
 *
 * for (; i < length; i++)
 *     sum0 += udata[i] * vdata[i];
 *
 * What factor limits the performance to a CPE of 1.00?
 *
 * The throughput bound of integer multiplication and floating-point addition
 * limit the performance to a CPE of 1.00 for integer values and floating-point
 * values, respectively.
 */
