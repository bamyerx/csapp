/*
 * Homework Problem 3.65 from CS:APP: The following code transposes the elements
 * of an M x M array, where M is a constant defined by #define:
 *
 *     void transpose(long A[M][M])
 *     {
 *         long i, j;
 *         for (i = 0; i < M; i++)
 *             for (j = 0; j < i; j++)
 *                 long t = A[i][j];
 *                 A[i][j] = A[j][i];
 *                 A[j][i] = t;
 *             }
 *     }
 *
 * When compiled with optimization level -O1, GCC generates the following code
 * for the inner loop of the function:
 *
 *     .L6:
 *       movq    (%rdx), %rcx
 *       movq    (%rax), %rsi
 *       movq    %rsi, (%rdx)
 *       movq    %rcx, (%rax)
 *       addq    $8, %rdx
 *       addq    $120, %rax
 *       cmpq    %rdi, %rax
 *       jne     .L6
 * 
 * We can see that GCC has converted the array indexing to pointer code.
 *
 * A. Which register holds a pointer to array element A[i][j]?
 *
 *    %rdx
 *
 * B. Which register holds a pointer to array element A[j][i]?
 *
 *    %rax
 *
 * C. What is the value of M?
 *
 *    We see that %rax is incremented by 120 in order to move the pointer from
 *    A[j][i] to A[j+1][i+1]. After dividing by the scaling factor of 8 and sub-
 *    tracting 1 (since we must advance by a row plus an extra element), we have
 *    that M = 14.
 */
