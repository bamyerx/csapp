/*
 * Homework Problem 3.71 from CS:APP: Write a function good_echo that reads a
 * line from standard input and writes it to standard output. Your implementa-
 * tion should work for an input line of arbitrary length. You may use the 
 * library function fgets, but you must make sure your function works correctly
 * even when the input line requires more space than you have allocated for your
 * buffer. Your code should also check for error conditions and return when one
 * is encountered.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 8

void good_echo(void)
{
	char buf[BUFSIZE];

	while (fgets(buf, BUFSIZE, stdin) != NULL) {
		if (fputs(buf, stdout) == EOF) {
			perror("good_echo");
			exit(1);
		}
		if (strchr(buf, '\n') != NULL)
			break;
	}

	if (ferror(stdin)) {
		perror("good_echo");
		exit(1);
	}
}
