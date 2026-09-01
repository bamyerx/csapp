/*
 * Homework Problem 3.59 from CS:APP: The following code computes the 128-bit
 * product of two 64-bit signed values x and y and stores the result in memory:
 *
 *     typedef __int128 int128_t;
 *
 *     void store_prod(int128_t, *dest, int64_t x, int64_t y) {
 *         *dest = x * (int128_t) y;
 *     }
 *
 * GCC generates the following assembly code implementing the computation:
 *
 *     store_prod
 *       movq	%rdx, %rax
 *       cqto
 *       movq	%rsi, %rcx
 *       sarq	$63, %rcx
 *       imulq	%rax, %rcx
 *       imulq	%rsi, %rdx
 *       addq	%rdx, %rcx
 *       mulq	%rsi
 *       addq	%rcx, %rdx
 *       movq	%rax, (%rdi)
 *       movq	%rdx, 8(%rdi)
 *       ret
 *
 * This code uses three multiplications for the multiprecision arithmetic
 * required to implement 128-bit arithmetic on a 64-bit machine. Describe the
 * algorithm used to compute the product, and annotate the assumbly code to show
 * how it realizes your algorithm.
 */

/*
 * store_prod takes advantage of the fact that when sign extending x and y to
 * 128-bits, they can be rewritten as
 *
 *     x = 2^64 * x_h + x_l
 *     y = 2^64 * y_h + y_l
 *
 * where x_h and y_h are -1 if the original value is negative or 0 otherwise.
 * Then, the product p is given by
 *
 *     p = x * y 
 *       = (2^64 * x_h + x_l)(2^64 * y_h + y_l)
 *       = 2^128 * x_h * y_h + 2^64(x_h * y_l + x_l * y_h) + x_l * y_l.
 * 
 * The first term falls out of the expression when considered modulo 2^128 so we
 * have p = 2^64 * p_h + p_l where
 * 
 *     p_h = x_h * y_l + x_l * y_h + high64(x_l * y_l)
 *     p_l = low64(x_l * y_l).
 *
 * Annotation of the assembly code:
 * 
 *     void store_prod(int128_t *dest, int64_t x, int64_t y)
 *     dest in %rdi, x in %rsi, y in %rdx
 *     store_prod
 *       movq	%rdx, %rax      Copy y to %rax
 *       cqto                   Sign extend y to oct word in %rdx:%rax:
 *                              y_h -> %rdx and y_l -> %rax where y_h is -1 or 0
 *       movq	%rsi, %rcx      Copy x to %rcx
 *       sarq	$63, %rcx       Obtain upper 8 bytes of x via sign extension (x_h -> %rcx)
 *                              At this point, the registers contain the following values:
 *                              %rsi: x_l, %rcx: x_h, %rax: y_l, %rdx: y_h
 *       imulq	%rax, %rcx      x_h * y_l -> %rcx
 *       imulq	%rsi, %rdx      y_h * x_l -> %rdx
 *       addq	%rdx, %rcx      x_h * y_l + y_h * x_l -> %rcx
 *       mulq	%rsi            Unsigned 128-bit multiplication of %rax by %rsi:
 *                              high64(x_l * y_l) -> %rdx, low64(x_l * y_l) = p_l -> %rax
 *       addq	%rcx, %rdx      high64(x_l * y_l) + x_h * y_l + x_l * y_h = p_h -> %rdx
 *       movq	%rax, (%rdi)    Store lower 8 bytes at dest: p_l -> *dest
 *       movq	%rdx, 8(%rdi)   Store upper 8 bytes at dest: p_h -> *(dest+8)
 *       ret
 */

