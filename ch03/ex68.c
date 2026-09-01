/*
 * Homework Problem 3.68 from CS:APP: In the following code, A and B are
 * constants defined with #define:
 *
 *     typedef struct {
 *         int x[A][B];
 *         long y;
 *     } str1;
 *
 *     typedef struct {
 *         char array[B];
 *         int t;
 *         short s[A];
 *         long u;
 *     } str2;
 *
 *     void setVal(str1 *p, str2 *q) {
 *         long v1 = q->t;
 *         long v2 = q->u;
 *         p->y = v1+v2;
 *     }
 *
 * GCC generates the following code for setVal:
 *
 *     void setVal(str1 *p, str2 *q)
 *     p in %rdi, q in %rsi
 *     setVal:
 *       movsql  8(%rsi), %rax
 *       addq    32(%rsi), %rax
 *       movq    %rax, 184(%rdi)
 *       ret
 *
 * What are the values of A and B? (The solution is unique.)
 *
 *     We can see that q->t has offset 8; this implies that 4 < B < 9 since an
 *     ints require an alignment of 4 bytes. Since q->t has offset 8, q->s must 
 *     then have offset 12. Then, we see that q->u has an offset of 32; this
 *     implies that 6 < A < 11, since longs require an alignment of 8 bytes.
 *
 *     We see that p->y has offset 184, which means that x must be at least 177
 *     bytes and at most 184 bytes in size. Given this, x must be either 180 
 *     bytes or 184 bytes in size, since this number must be a multiple of 4. 
 *     This gives us two options: either A*B = 45 or A*B = 46. Given the bounds
 *     we have already established, A*B = 45 with A = 9 and B = 5.
 */
