/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k;
	int t0, t1, t2, t3, t4, t5, t6, t7;

	/* for a 32x32 matrix, use an 8x8 block transpose */
	if (M == 32) {
		for (i = 0; i+7 < 32; i+=8) {
			for (j = 0; j+7 < 32; j+=8) {

				/* load and store 8 elements at a time */
				for (k = 0; k < 8; k++) {

					t0 = A[i+k][j];
					t1 = A[i+k][j+1];
					t2 = A[i+k][j+2];
					t3 = A[i+k][j+3];
					t4 = A[i+k][j+4];
					t5 = A[i+k][j+5];
					t6 = A[i+k][j+6];
					t7 = A[i+k][j+7];

					B[j  ][i+k] = t0;
					B[j+1][i+k] = t1;
					B[j+2][i+k] = t2;
					B[j+3][i+k] = t3;
					B[j+4][i+k] = t4;
					B[j+5][i+k] = t5;
					B[j+6][i+k] = t6;
					B[j+7][i+k] = t7;
				}
			}
		}
	}

	/* for a 64x64 matrix, use 8x8 blocking with 4x4 sub-tiles */
	if (M == 64) {
		for (i = 0; i+7 < 64; i += 8) {
			for (j = 0; j+7 < 64; j += 8) {

				/* top left quadrant and temporary storage */
				for (k = 0; k < 4; k++) {

					/* top left quadrant of A's block */
					t0 = A[i+k][j];
					t1 = A[i+k][j+1];
					t2 = A[i+k][j+2];
					t3 = A[i+k][j+3];

					/* bottom left quadrant of A's block */
					t4 = A[i+k][j+4];
					t5 = A[i+k][j+5];
					t6 = A[i+k][j+6];
					t7 = A[i+k][j+7];

					/* top left quadrant of B's block */
					B[j  ][k+i] = t0;
					B[j+1][k+i] = t1;
					B[j+2][k+i] = t2;
					B[j+3][k+i] = t3;

					/* top right quadrant of B's block (temporary storage) */
					B[j  ][k+i+4] = t4;
					B[j+1][k+i+4] = t5;
					B[j+2][k+i+4] = t6;
					B[j+3][k+i+4] = t7;
				}

				/* top right/bottom left quadrants */
				for (k = 0; k < 4; k++) {

					/* top right quadrant of A's block */
					t0 = A[i+4][j+k];
					t1 = A[i+5][j+k];
					t2 = A[i+6][j+k];
					t3 = A[i+7][j+k];

					/* move temporary values back to registers */
					t4 = B[j+k][i+4];
					t5 = B[j+k][i+5];
					t6 = B[j+k][i+6];
					t7 = B[j+k][i+7];

					/* top right quadrant of B's block */
					B[j+k][i+4] = t0;
					B[j+k][i+5] = t1;
					B[j+k][i+6] = t2;
					B[j+k][i+7] = t3;

					/* bottom left quadrant of B's block */
					B[j+k+4][i]   = t4;
					B[j+k+4][i+1] = t5;
					B[j+k+4][i+2] = t6;
					B[j+k+4][i+3] = t7;
				}

				/* bottom right quadrant */
				for (k = 0; k < 4; k++) 
				{
					/* bottom right quadrant of A's block */
					t0 = A[i+4+k][j+4];
					t1 = A[i+4+k][j+5];
					t2 = A[i+4+k][j+6];
					t3 = A[i+4+k][j+7];

					/* bottom right quadrant of B's block */
					B[j+4][i+4+k] = t0;
					B[j+5][i+4+k] = t1;
					B[j+6][i+4+k] = t2;
					B[j+7][i+4+k] = t3;
				}
			}
		}
	}

	/* for a 61x67 matrix, use a 16x16 block transpose */
	if (M == 61 && N == 67) {
		for (i = 0; i + 15 < 67; i += 16) {
			for (j = 0; j + 15 < 61; j += 16) {

				/* load and store 8 elements at a time */
				for (k = 0; k < 16; k++) {

					t0 = A[i+k][j];
					t1 = A[i+k][j+1];
					t2 = A[i+k][j+2];
					t3 = A[i+k][j+3];
					t4 = A[i+k][j+4];
					t5 = A[i+k][j+5];
					t6 = A[i+k][j+6];
					t7 = A[i+k][j+7];

					B[j  ][i+k] = t0;
					B[j+1][i+k] = t1;
					B[j+2][i+k] = t2;
					B[j+3][i+k] = t3;
					B[j+4][i+k] = t4;
					B[j+5][i+k] = t5;
					B[j+6][i+k] = t6;
					B[j+7][i+k] = t7;

					t0 = A[i+k][j+8];
					t1 = A[i+k][j+9];
					t2 = A[i+k][j+10];
					t3 = A[i+k][j+11];
					t4 = A[i+k][j+12];
					t5 = A[i+k][j+13];
					t6 = A[i+k][j+14];
					t7 = A[i+k][j+15];

					B[j+8 ][i+k] = t0;
					B[j+9 ][i+k] = t1;
					B[j+10][i+k] = t2;
					B[j+11][i+k] = t3;
					B[j+12][i+k] = t4;
					B[j+13][i+k] = t5;
					B[j+14][i+k] = t6;
					B[j+15][i+k] = t7;
				}
			}
		}

		/* transpose leftover columns and rows */
		for (; i < 67; i++)
			for (j = 0; j < 61; j++)
				B[j][i] = A[i][j];

		for (i = 0; i < 64; i++)
			for (j = 48; j < 61; j++)
				B[j][i] = A[i][j];
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * trans_4x4 - blocked transpose with a 4x4 kernel
 */
char trans_4x4_desc[] = "Blocked transpose with a 4x4 kernel";
void trans_4x4(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l;
	int t0, t1, t2, t3;

	for (i = 0; i+3 < N; i += 4) {
		for (j = 0; j+3 < M; j += 4) {
			for (k = 0; k < 4; k++) {

				t0 = A[i+k][j];
				t1 = A[i+k][j+1];
				t2 = A[i+k][j+2];
				t3 = A[i+k][j+3];

				B[j  ][i+k] = t0;
				B[j+1][i+k] = t1;
				B[j+2][i+k] = t2;
				B[j+3][i+k] = t3;
			}
		}
	}

	k = i;
	l = j;
	for (; i < N; i++)
		for (j = 0; j < M; j++)
			B[j][i] = A[i][j];

	for (i = 0; i < k; i++)
		for (j = l; j < M; j++)
			B[j][i] = A[i][j];
}

/*
 * trans_8x4 - blocked transpose with a 8x4 kernel
 */
char trans_8x4_desc[] = "Blocked transpose with a 8x4 kernel";
void trans_8x4(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l;
	int t0, t1, t2, t3;

	for (i = 0; i+7 < N; i += 8) {
		for (j = 0; j+3 < M; j += 4) {
			for (k = 0; k < 8; k++) {

				t0 = A[i+k][j];
				t1 = A[i+k][j+1];
				t2 = A[i+k][j+2];
				t3 = A[i+k][j+3];

				B[j  ][i+k] = t0;
				B[j+1][i+k] = t1;
				B[j+2][i+k] = t2;
				B[j+3][i+k] = t3;
			}
		}
	}

	k = i;
	l = j;
	for (; i < N; i++)
		for (j = 0; j < M; j++)
			B[j][i] = A[i][j];

	for (i = 0; i < k; i++)
		for (j = l; j < M; j++)
			B[j][i] = A[i][j];
}


/*
 * trans_8x8 - blocked transpose with an 8x8 kernel
 */
char trans_8x8_desc[] = "Blocked transpose with an 8x8 kernel";
void trans_8x8(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l;
	int t0, t1, t2, t3, t4, t5, t6, t7;

	for (i = 0; i+7 < N; i += 8) {
		for (j = 0; j+7 < M; j += 8) {
			for (k = 0; k < 8; k++) {

				t0 = A[i+k][j];
				t1 = A[i+k][j+1];
				t2 = A[i+k][j+2];
				t3 = A[i+k][j+3];
				t4 = A[i+k][j+4];
				t5 = A[i+k][j+5];
				t6 = A[i+k][j+6];
				t7 = A[i+k][j+7];

				B[j  ][i+k] = t0;
				B[j+1][i+k] = t1;
				B[j+2][i+k] = t2;
				B[j+3][i+k] = t3;
				B[j+4][i+k] = t4;
				B[j+5][i+k] = t5;
				B[j+6][i+k] = t6;
				B[j+7][i+k] = t7;
			}
		}
	}

	k = i;
	l = j;
	for (; i < N; i++)
		for (j = 0; j < M; j++)
			B[j][i] = A[i][j];

	for (i = 0; i < k; i++)
		for (j = l; j < M; j++)
			B[j][i] = A[i][j];
}

/*
 * trans_16x16 - blocked transpose with a 16x16 kernel
 */
char trans_16x16_desc[] = "Blocked transpose with a 16x16 kernel";
void trans_16x16(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, l;
    int t0, t1, t2, t3, t4, t5, t6, t7;

	for (i = 0; i + 15 < N; i += 16) {
		for (j = 0; j + 15 < M; j += 16) {
			for (k = 0; k < 16; k++) {

				t0 = A[i+k][j];
				t1 = A[i+k][j+1];
				t2 = A[i+k][j+2];
				t3 = A[i+k][j+3];
				t4 = A[i+k][j+4];
				t5 = A[i+k][j+5];
				t6 = A[i+k][j+6];
				t7 = A[i+k][j+7];

				B[j  ][i+k] = t0;
				B[j+1][i+k] = t1;
				B[j+2][i+k] = t2;
				B[j+3][i+k] = t3;
				B[j+4][i+k] = t4;
				B[j+5][i+k] = t5;
				B[j+6][i+k] = t6;
				B[j+7][i+k] = t7;

				t0 = A[i+k][j+8];
				t1 = A[i+k][j+9];
				t2 = A[i+k][j+10];
				t3 = A[i+k][j+11];
				t4 = A[i+k][j+12];
				t5 = A[i+k][j+13];
				t6 = A[i+k][j+14];
				t7 = A[i+k][j+15];

				B[j+8 ][i+k] = t0;
				B[j+9 ][i+k] = t1;
				B[j+10][i+k] = t2;
				B[j+11][i+k] = t3;
				B[j+12][i+k] = t4;
				B[j+13][i+k] = t5;
				B[j+14][i+k] = t6;
				B[j+15][i+k] = t7;
			}
		}
	}

	k = i;
	l = j;
	for (; i < N; i++)
		for (j = 0; j < M; j++)
			B[j][i] = A[i][j];

	for (i = 0; i < k; i++)
		for (j = l; j < M; j++)
			B[j][i] = A[i][j];
}

/*
 * trans_8x8_4x4 - 8x8 blocked transpose with 4x4 sub-tiles
 */
char trans_8x8_4x4_desc[] = "8x8 blocked transpose with 4x4 sub-tiles";
void trans_8x8_4x4(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, l;
	int t0, t1, t2, t3, t4, t5, t6, t7;
	
	for (i = 0; i+7 < 64; i += 8) {
		for (j = 0; j+7 < 64; j += 8) {

			/* top left quadrant and temporary storage */
			for (k = 0; k < 4; k++) {

				/* top left quadrant of A's block */
				t0 = A[i+k][j];
				t1 = A[i+k][j+1];
				t2 = A[i+k][j+2];
				t3 = A[i+k][j+3];

				/* bottom left quadrant of A's block */
				t4 = A[i+k][j+4];
				t5 = A[i+k][j+5];
				t6 = A[i+k][j+6];
				t7 = A[i+k][j+7];

				/* top left quadrant of B's block */
				B[j  ][k+i] = t0;
				B[j+1][k+i] = t1;
				B[j+2][k+i] = t2;
				B[j+3][k+i] = t3;

				/* top right quadrant of B's block (temporary storage) */
				B[j  ][k+i+4] = t4;
				B[j+1][k+i+4] = t5;
				B[j+2][k+i+4] = t6;
				B[j+3][k+i+4] = t7;
			}

			/* top right/bottom left quadrants */
			for (k = 0; k < 4; k++) {

				/* top right quadrant of A's block */
				t0 = A[i+4][j+k];
				t1 = A[i+5][j+k];
				t2 = A[i+6][j+k];
				t3 = A[i+7][j+k];

				/* move temporary values back to registers */
				t4 = B[j+k][i+4];
				t5 = B[j+k][i+5];
				t6 = B[j+k][i+6];
				t7 = B[j+k][i+7];

				/* top right quadrant of B's block */
				B[j+k][i+4] = t0;
				B[j+k][i+5] = t1;
				B[j+k][i+6] = t2;
				B[j+k][i+7] = t3;

				/* bottom left quadrant of B's block */
				B[j+k+4][i]   = t4;
				B[j+k+4][i+1] = t5;
				B[j+k+4][i+2] = t6;
				B[j+k+4][i+3] = t7;
			}

			/* bottom right quadrant */
			for (k = 0; k < 4; k++) 
			{
				/* bottom right quadrant of A's block */
				t0 = A[i+4+k][j+4];
				t1 = A[i+4+k][j+5];
				t2 = A[i+4+k][j+6];
				t3 = A[i+4+k][j+7];

				/* bottom right quadrant of B's block */
				B[j+4][i+4+k] = t0;
				B[j+5][i+4+k] = t1;
				B[j+6][i+4+k] = t2;
				B[j+7][i+4+k] = t3;
			}
		}
	}

	k = i;
	l = j;
	for (; i < N; i++)
		for (j = 0; j < M; j++)
			B[j][i] = A[i][j];

	for (i = 0; i < k; i++)
		for (j = l; j < M; j++)
			B[j][i] = A[i][j];
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans, trans_desc); 
	//registerTransFunction(trans_4x4, trans_4x4_desc);
	//registerTransFunction(trans_8x4, trans_8x4_desc);
	//registerTransFunction(trans_8x8, trans_8x8_desc);
	//registerTransFunction(trans_16x16, trans_16x16_desc);
	//registerTransFunction(trans_8x8_4x4, trans_8x8_4x4_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

