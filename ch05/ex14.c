/*
 * Homework Problem 5.14 from CS:APP: Write a version of the inner product
 * procedure described in Problem 5.13 that uses 6 x 1 loop unrolling. For
 * x86-64, our measurements of the unrolled version gives a CPE of 1.07 for
 * integer data but still 3.01 for both floating-point data.
 *
 * long i;
 * long length = vec_length(u);
 * long limit = length - 5;
 * data_t *udata = get_vec_start(u);
 * data_t *vdata = get_vec_start(v);
 * data_t sum = (data_t) 0;
 *
 * for (i = 0; i < limit; i += 6) {
 *     sum += udata[i] * vdata[i];
 *     sum += udata[i+1] * vdata[i+1];
 *     sum += udata[i+2] * vdata[i+2];
 *     sum += udata[i+3] * vdata[i+3];
 *     sum += udata[i+4] * vdata[i+4];
 *     sum += udata[i+5] * vdata[i+5];
 * }
 *
 * for (; i < length; i++)
 *     sum += udata[i] * vdata[i];
 *
 * A. Explain why any (scalar) version of an inner product procedure running on
 *    an Intel Core i7 Haswell processor cannot achieve a CPE less than 1.00.
 *
 *    Any scalar version of an inner product procedure requires both multipli-
 *    cation and addition per element per vector, which limits the CPE to the
 *    throughput bound the operation with fewer functional units; therefore,
 *    the inner product of integer values is limited by integer multiplication,
 *    whose throughput bound is 1.00, and the inner product of floating-point
 *    values is limited by floating-point addition, whose throughput bound is
 *    also 1.00.
 *
 * B. Explain why the performance for floating-point data did not improve with
 *    loop unrolling.
 *
 *    The performance for floating-point data did not improve because the
 *    floating-point addition must still be performed in sequence within each
 *    loop iteration.
 */
