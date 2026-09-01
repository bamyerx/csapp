/*
 * Homework Problem 3.64 from CS:APP: Consider the following source code, where
 * R, S, and T are constants declared with #define:
 *
 *     long A[R][S][T];
 *
 *     long store_ele(long i, long j, long k, long *dest)
 *     {
 *         *dest = A[i][j][k];
 *         return sizeof(A);
 *     }
 *
 * In compiling this program, GCC generates the following assembly code:
 *
 *     long store_ele(long i, long j, long k, long *dest)
 *     i in %rdi, j in %rsi, k in %rdx, dest in %rcx
 *     store_ele:
 *       leaq    (%rsi,%rsi,2), %rax
 *       leaq    (%rsi,%rax,4), %rax
 *       movq    %rdi, %rsi
 *       salq    $6, %rsi
 *       addq    %rsi, %rdi
 *       addq    %rax, %rdi
 *       addq    %rdi, %rdx
 *       movq    A(,%rdx,8), %rax
 *       movq    %rax, (%rcx)
 *       movl    $3640, %eax
 *       ret
 *
 * A. Extend Equation 3.1 from two dimensions to three to provide a formula for
 *    the location of array element A[i][j][k].
 *
 *    &A[i][j][k] = x_A + L(STi + Tj + k)
 *
 * B. Use your reverse engineering skills to determine the values of R, S, and T
 *    based on the assembly code.
 *
 *    To start, I will annotate the assembly code:
 *
 *    leaq (%rsi,%rsi,2), %rax    j + 2j = 3j -> %rax
 *    leaq (%rsi,%rax,4), %rax    j+ 4*3j = 13j -> %rax
 *    movq %rdi, %rsi             i -> %rsi
 *    salq $6, %rsi               i << 6 = 64i -> %rsi
 *    addq %rsi, %rdi             i + 64i = 65i -> %rdi
 *    addq %rax, %rdi             65i + 13j -> %rdi
 *    addq %rdi, %rdx             65i + 13j + k -> %rdx
 *    movq A(,%rdx,8), %rax       A[65i+13j+k] -> %rax
 *    movq %rax, (%rcx)           *dest = A[65i+13j+k]
 *    movl $3640, %eax            sizeof(A) = 3640
 *    ret
 *
 *    It can be seen that the offset of A[i][j][k] is 8(65i + 13j + k), so
 *    ST = 65 and T = 13. Thus, S = 5. Additionally, since sizeof(A) = 3,640,
 *    R = 3,640 / (8ST) = 7.
 */
