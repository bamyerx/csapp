/*
 * Homework Problem 3.69 from CS:APP: You are charged with maintaining a large C
 * program, and you come across the following code:
 *
 *     typedef struct {
 *         int first;
 *         a_struct a[CNT];
 *         int last;
 *     } b_struct;
 *
 *     void test(long i, b_struct *bp)
 *     {
 *         int n = bp->first + bp->last;
 *         a_struct *ap = &bp->a[i];
 *         ap->x[ap->idx] = n;
 *     }
 *
 * The declarations of the compile-time constant CNT and the structure a_struct
 * are in a file for which you do not have the necessary access privilege. For-
 * tunately, you have a copy of the .o version of code, which you are able to
 * disassemble with the OBJDUMP program, yielding the following disassembly:
 *
 *     void test(long i, b_struct *bp)
 *     i in %rdi, bp in %rsi
 *     0000000000000000 <test>:
 *         0:    8b 8e 20 01 00 00    mov    0x120(%rsi),%ecx
 *         6:    03 0e                add    (%rsi),%ecx
 *         8:    48 8d 04 bf          lea    (%rdi,%rdi,4),%rax
 *         c:    48 8d 04 c6          lea    (%rsi,%rax,8),%rax
 *         10:   48 8b 50 08          mov    0x8(%rax),%rdx
 *         14:   48 63 c9             movslq %ecx,%rcx
 *         17:   48 89 4c d0 10       mov    %rcx,0x10(%rax,%rdx,8)
 *         1c:   c3retq
 *
 * Using your reverse engineering skills, deduce the following:
 *
 * A. The value of CNT.
 *
 *    First, we annotate the assembly:
 *
 *    mov    0x120(%rsi),%ecx        *(bp+288) -> %ecx
 *    add    (%rsi),%ecx             *(bp+288) + *bp -> %ecx
 *    lea    (%rdi,%rdi,4),%rax      5i -> %rax
 *    lea    (%rsi,%rax,8),%rax      bp + 40i -> %rax
 *    mov    0x8(%rax),%rdx          *(bp + 40i + 8) -> %rdx
 *    movslq %ecx,%rcx               Sign extend %ecx to %rcx
 *    mov    %rcx,0x10(%rax,%rdx,8)  (long) n -> *((bp+40i) + 8*(bp+40i+8) + 16)
 *
 *    We can see that register %ecx is used for the local variable n and the
 *    first two lines correspond to the first line of test, demonstrating that
 *    the offset of last is 288. Next, we can see that the assembly computes the
 *    address of bp->a[i] as bp + 40i + 8. This implies that the offset of a is
 *    8 and that each a_struct occupies 40 bytes. Since the offset of last is
 *    288 bytes and each a_struct is 40 bytes, it follows that sizeof(a) = 280
 *    so CNT = sizeof(a) / sizeof(a[i]) = 280 / 40 = 7.
 *
 * B. A complete declaration of structure a_struct. Assume that the only fields
 *    in this structure are idx and x, and that both of these contain signed
 *    values.
 *
 *    We see that in settings ap->x[ap->idx] = n, the assembly uses movslq to
 *    sign extend n from a 32-bit int to a 64-bit long, so idx must have type
 *    long. Then, x must be an array of long and since sizeof(a_struct) = 10, 
 *    x must have length 4, and we have:
 *
 *    typedef struct {
 *        long idx;
 *        long x[4];
 *    } a_struct;
 */
