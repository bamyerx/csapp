/*
 * Homework Problem 5.14 from CS:APP: Write a version of the inner product
 * procedure described in Problem 5.13 that uses 6 x 1a loop unrolling to enable
 * greater parallelism. Our measurements for this function give a CPE of 1.10
 * for integer data and 1.05 for floating-point data.
 *
 * long i;
 * long length = vec_length(u);
 * long limit = length - 5;
 * data_t *udata = get_vec_start(u);
 * data_t *vdata = get_vec_start(v);
 * data_t sum = (data_t) 0;
 *
 * for (i = 0; i < limit; i += 6) {
 *     sum += (udata[i]*vdata[i] + udata[i+1]*vdata[i+1]) +
 *            ((udata[i+2]*vdata[i+2] + udata[i+3]*vdata[i+3]) +
 *            (udata[i+4]*vdata[i+4] + udata[i+5]*vdata[i+5])));
 * }
 *
 * for (; i < length; i++)
 *     sum += udata[i] * vdata[i];
 */
