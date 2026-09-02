/*
 * Homework Problem 3.72 from CS:APP: Figure 3.54(a) shows the code for a
 * function that is similar to function vfunct (Figure 3.43(a)). We used vfunct
 * to illustrate the use of a frame pointer in managing variable-size stack
 * frames. The new function aframe allocates space for loca array p by calling
 * library function alloca. This function is similar to the more common used
 * function malloc, except that it allocates space on the run-time stack. The
 * space is automatically deallocated when the executing procedure returns.
 * Figure 3.54(b) shows the part of the assembly code that sets up the frame
 * pointer and allocates space for local variables i and p. It is very similar
 * to the corresponding code for vframe. let us use the same notation as in
 * Problem 3.49: The stack pointer is set to values s1 at line 4 and s2 at line
 * 7. The start address of array p is set to value p at line 9. Extra space e2
 * may arise between s2 and p, and extra space e1 may arise between the end of
 * array p and s1.
 *
 * The portion of assembly from Figure 3.54(b):
 *
 *     long aframe(long n, long idx, long *q)
 *     n in %rdi, idx in %rsi, q in %rdx
 *     aframe:
 *       pushq   %rbp
 *       movq    %rsp, %rbp
 *       subq    $16, %rsp            # Allocate space for i (%rsp = s1)
 *       leaq    30(,%rdi,8), %rax
 *       andq    $-16, %rax
 *       subq    %rax, %rsp           # Allocate space for array p (%rsp = s2)
 *       leaq    15(%rsp), %r8
 *       andq    $-16, %r8
 *       ...
 *
 * A. Explain, in mathematical terms, the logic in the computation of s2.
 *
 *    Line 5 computes 8n + 30 and then line 6 rounds this value down to the
 *    nearest multiple of 16. This results in 8n + 24 when n is odd and 8n + 16
 *    when n is even, and line 7 subtracts this value from s1 to compute s2.
 *
 * B. Explain, in mathematical terms, the logic in the computation of p.
 *
 *    Line 8 computes s2 + 15 and then line 9 rounds this value up to the next
 *    multiple of 16.
 *
 * C. Find values of n and s1 that lead to minimum and maximum values of e1.
 *
 *    n     s1      s2      p      e1    e2
 *    5    2065    2001    2016     1    15
 *    6    2064    1992    2000    16     8
 *
 * D. What alignment properties does this code guarantee for the values of s2
 *    and p?
 *
 *    This code guarantees that s2 and p have a 16-byte alignment.
 */
