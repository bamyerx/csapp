/*
 * Homework Problem 3.66 from CS:APP: Consider the following source code, where
 * NR and NC are macro expressions declared with #define that compute the
 * dimensions of array A in terms of parameter n. This code computes the sum of
 * the elements of column j of the array.
 *
 *     long sum_col(long n, long A[NR(n)][NC(n)], long j) {
 *         long i;
 *         long result = 0;
 *         for (i = 0; i < NR(n); i++)
 *             result += A[i][j];
 *         return result;
 *     }
 *
 * In compiling this program, GCC generates the following assembly code:
 *
 *     long sum_col(long n, long A[NR(n)][NC(n)], long j)
 *     n in %rdi, A in %rsi, j in %rdx
 *     sum_col:
 *       leaq      1(,%rdi,4), %r8      5n -> %r8
 *       leaq      (%rdi,%rdi,2), %rax  3n -> %rax
 *       movq      %rax, %rdi           3n -> %rdi
 *       testq     %rax, %rax           test 3n
 *       jle       .L4                  done if 3n <= 0
 *       salq      $3, %r8              5n * 8 = 40n -> %r8
 *       leaq      (%rsi,%rdx,8), %rcx  A + 8j -> %rcx
 *       movl      $0, %eax             result = 0
 *       movl      $0, %edx             i = 0
 *     .L3:
 *       addq      (%rcx), %rax         result += A[i][j]
 *       addq      $1, %rdx             i++
 *       addq      %r8, %rcx            A + j + 40n -> %rcx
 *       cmpq      %rdi, %rdx           compare i and 3n
 *       jne       .L3                  loop if i != 3n
 *       rep; ret                       return
 *     .L4:
 *       movl      $0, %eax             result = 0
 *       ret                            return 0
 *
 * Use your reverse engineering skills to determine the definitions of NR and 
 * NC.
 *
 * #define NR(n) (3 * (n))
 * #define NC(n) (5 * (n))
 */
