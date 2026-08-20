/*
 * Homework Problem 2.76 from CS:APP: The library function calloc has the
 * following declaration:
 *
 *     void *calloc(size_t nmemb, size_t size);
 *
 * According to the library documentation, "The calloc function allocates memory
 * for an array of nmemb elements of size bytes each. The memory is set to zero.
 * If nmemb or size is zero, then calloc returns NULL."
 * Write an implementation of calloc that performs the allocation by a call to
 * malloc and sets the memory to zero via memset. Your code should not have any
 * vulnerabilities due to arithmetic overflow, and it should work correctly
 * regardless of the number of bits used to represent data of type size_t.
 * As a reference, functions malloc and memset have the following declarations:
 *
 *     void *malloc(size_t size);
 *     void *memset(void *s, int c, size_t n);
 */

#include <stdlib.h>
#include <string.h>

void *my_calloc(size_t nmemb, size_t size)
{
	void *p;
	size_t alloc = nmemb * size;

	/* Ensure nmemb nor size are 0 and that nmemb * size does not overflow */
	if (nmemb == 0 || size == 0 || alloc / nmemb != size)
		return NULL;
	
	/* Check for allocation failure */
	if ((p = malloc(alloc)) == NULL)
		return NULL;

	return memset(p, 0, alloc);
}
