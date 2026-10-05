#include "cachelab.h"
#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 16

struct cache_line {
	bool valid;
	uint64_t tag;
	int age;
};

void usage(void);
void free_cache(struct cache_line **cache, size_t nlines);

int main(int argc, char *argv[])
{
	int s, E, b;
	int hits, misses, evictions;
	bool sflag, Eflag, bflag, tflag, vflag;
	FILE *fp;

	sflag = Eflag = bflag = tflag = vflag = false;
	hits = misses = evictions = 0;

	/* supported options: -v, -s, -E, -b, -t */
	int c;
	while ((c = getopt(argc, argv, ":b:E:s:t:v")) != -1) {
		char *endptr;
		switch(c) {
		case 'b':
			b = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || b < 0) {
				fprintf(stderr, "csim: invalid value for b: '%s'\n", optarg);
				exit(1);
			}
			bflag = true;
			break;
		case 'E':
			E = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || E < 1) {
				fprintf(stderr, "csim: invalid value for E: '%s'\n", optarg);
				exit(1);
			}
			Eflag = true;
			break;
		case 's':
			s = strtol(optarg, &endptr, 10);
			if (*endptr != '\0' || s < 0) {
				fprintf(stderr, "csim: invalid value for s: '%s'\n", optarg);
				exit(1);
			}
			sflag = true;
			break;
		case 't':
			fp = fopen(optarg, "r");
			if (fp == NULL) {
				fprintf(stderr, "csim: %s: %s\n", optarg, strerror(errno));
				exit(1);
			}
			tflag = true;
			break;
		case 'v':
			vflag = true;
			break;
		case ':':
			fprintf(stderr, "csim: -%c requires an argument\n", optopt);
			exit(1);
			break;
		case '?':
			fprintf(stderr, "csim: unknown option -%c\n", optopt);
			usage();
			break;
		}
	}

	/* missing required arguments */
	if (!bflag || !Eflag || !sflag || !tflag) {
		usage();
		exit(1);
	}

	/* allocate cache */
	size_t nlines = ((size_t) 1 << s) * E;
	struct cache_line **cache = malloc(nlines * sizeof(struct cache_line *));
	if (cache == NULL) {
		fprintf(stderr, "csim: %s\n", strerror(errno));
		fclose(fp);
		exit(1);
	}
	for (int i = 0; i < nlines; i++) {
		/* allocate each cache line */
		if ((cache[i] = malloc(sizeof(struct cache_line))) == NULL) {
			fprintf(stderr, "csim: %s\n", strerror(errno));
			free(cache);
			fclose(fp);
			exit(1);
		}
		cache[i]->valid = false;
	}

	printf("nlines = %zu\n", nlines);

	/* parse tracefile */
	char trace[MAXLINE];
	while (fgets(trace, MAXLINE, fp) != NULL) {

		/* ignore memory access operations */
		if (trace[0] == 'I')
			continue;

		/* extract operation, set bits, and tag bits */
		char operation;
		uint64_t i, address, set, tag;
		int size;
		sscanf(trace, " %c %lx,%d", &operation, &address, &size);
		set = (address >> b) & (((uint64_t) 1 << s) - 1);
		tag = address >> (b + s);

		/* for modify operations, the store operation is always a hit */
		if (operation == 'M')
			hits++;

		/* search cache for requested data */
		bool hit = false;
		for (i = set * E; i < (set + 1) * E; i++) {
			
			/* ignore invalid cache lines */
			if (!cache[i]->valid)
				continue;

			/* cache hit */
			if (cache[i]->tag == tag) {
				hit = true;
				hits++;
				cache[i]->age = 0;
				if (vflag) {
					printf("%c %lx,%d hit%s\n", 
							operation, 
							address, 
							size,
							operation == 'M' ? " hit" : "");
				}
			/* increment age for any other valid cache line */
			} else
				cache[i]->age++;
		}
		/* if data was found, we are done */
		if (hit)
			continue;

		/* find an empty line in which to cache the data */
		misses++;
		for (i = set * E; i < (set + 1) * E && !hit; i++)
			/* empty cache line found */
			if (!cache[i]->valid) {
				hit = true;
				cache[i]->valid = true;
				cache[i]->tag = tag;
				cache[i]->age = 0;
				if (vflag)
					printf("%c %lx,%d miss%s\n", 
							operation, 
							address, 
							size, 
							operation == 'M' ? " hit" : "");
			}
		/* no eviction was necessary so we are done */
		if (hit)
			continue;

		/* find the least recently used cache line */
		evictions++;
		int oldest = set * E;
		for (i = set * E; i < (set + 1) * E; i++)
			if (cache[i]->age > cache[oldest]->age)
				oldest = i;
		/* evict least recently used cache line */
		cache[oldest]->tag = tag;
		cache[oldest]->age = 0;
		if (vflag)
			printf("%c %lx,%d miss eviction%s\n",
					operation,
					address,
					size,
					operation == 'M' ? " hit" : "");

	}
	if (ferror(fp)) {
		fprintf(stderr, "csim: %s\n", strerror(errno));
		free_cache(cache, nlines);
		fclose(fp);
		exit(1);
	}

    printSummary(hits, misses, evictions);

	free_cache(cache, nlines);
	fclose(fp);
    return 0;
}

void usage(void)
{
	fprintf(stderr, "Usage: ./csim [-v] -s <s> -E <E> -b <b> -t <tracefile>\n");
}

void free_cache(struct cache_line **cache, size_t nlines)
{
	for (int i = 0; i < nlines; i++)
		free(cache[i]);
	free(cache);
}
