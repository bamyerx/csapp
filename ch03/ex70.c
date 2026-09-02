/*
 * Homework Problem 3.70 from CS:APP: Consider the following union declaration:
 *     union ele {
 *         struct {
 *             long *p;
 *             long y;
 *         } e1;
 *         struct {
 *             long x;
 *             union ele *next;
 *         } e2;
 *     };
 *
 * This declaration illustrates that structures can be embedded within unions.
 * The following function (with some expressions omitted) operates on a linked
 * list having these unions as list elements:
 *
 *     void proc(union ele *up) {
 *         up->____ = *(____) - ____;
 *     }
 *
 * A. What are the offsets (in bytes) of the following fields:
 *
 *    e1.p     0
 *    e1.y     8
 *    e2.x     0
 *    e2.next  8
 *
 * B. How many total bytes does the structure require?
 * 
 *    16 bytes
 *
 * C. The compiler generates the following assembly code for proc:
 *     void proc (union ele *up)
 *     up in %rdi
 *     proc:
 *       movq    8(%rdi), %rax
 *       movq    (%rax), %rdx
 *       movq    (%rdx), %rdx
 *       subq    8(%rax), %rdx
 *       movq    %rdx, (%rdi)
 *       ret
 * 
 * On the basis of this information, fill in the missing expressions in the code
 * for proc. Hint: Some union references can have ambiguous interpretations.
 * These ambiguities get resolved as you see where the references lead. There
 * is only one answer that does not perform any casting and does not violate any
 * type constaints.
 */

void proc(union ele *up) 
{
	up->e2.x = *(up->e2.next->p) - up->e1.y;
}

