/*
 * Homework Problem 3.62 from CS:APP: The code that follows shows an example of
 * branching on an enumerated type value in a switch statement. Recall that
 * enumerated types in C are simply a way to introduce a set of names having
 * associated integer values. By default, the values assigned to the names count
 * from zero upward. In our code, the actions associated with the different case
 * labels have been omitted.
 *
 *     Enumerated type creates set of constants numbered 0 and upward
 *     typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;
 *
 *     long switch3(long *p1, long *p2, mode_t action)
 *     {
 *         long result = 0;
 *         switch(action) {
 *         case MODE_A:
 *
 *         case MODE_B:
 *
 *         case MODE_C:
 *
 *         case MODE_D:
 *
 *         case MODE_E:
 *
 *         default:
 *
 *         }
 *         return result;
 *     }
 *
 * The generated assembly code:
 *
 *     # p1 in %rdi, p2 in %rsi, action in %edx
 *     .L8:
 *       movl    $27, %eax
 *       ret
 *     .L3:
 *       movq    (%rsi), %rax
 *       movq    (%rdi), %rdx
 *       movq    %rax, (%rdi)
 *       ret
 *     .L5:
 *       movq    $59, (%rdi)
 *       addq    (%rsi), %rax
 *       ret
 *     .L7:
 *       movq    (%rsi), %rax
 *       movq    %rax, (%rdi)
 *       movl    $27, %eax
 *       ret
 *     .L9:
 *       movl    $12, %eax
 *       ret
 *
 * Fill in the missing parts of the C code. It contained one case that fell
 * through to another--try to reconstruct this.
 */

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
	long result = 0;
	switch(action) {
	case MODE_A:
		result = *p2;
		*p2 = *p1;
		break;
	case MODE_B:
		result = *p1 + *p2;
		break;
	case MODE_C:
		*p1 = 59;
		result = *p2;
		break;
	case MODE_D:
		result = *p2;
		*p1 = result;
	/* FALL THROUGH */
	case MODE_E:
		result = 27;
		break;
	default:
		result = 12;
	}
	return result;
}
