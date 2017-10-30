#include "hpl.h"
/*
 * Define default value for unrolling factor
 */
#ifndef HPL_LASWP06N_DEPTH
#define HPL_LASWP06N_DEPTH 32
#define HPL_LASWP06N_LOG2_DEPTH 5
#endif

void HPL_dlaswp06N(const int M, const int N, double* A, const int LDA,
                   double* U, const int LDU, const int* LINDXA) {
  /*
   * Purpose
   * =======
   *
   * HPL_dlaswp06N swaps rows of  U  with rows of A at positions
   * indicated by LINDXA.
   *
   * Arguments
   * =========
   *
   * M       (local input)                 const int
   *         On entry, M  specifies the number of rows of A that should be
   *         swapped with rows of U. M must be at least zero.
   *
   * N       (local input)                 const int
   *         On entry, N specifies the length of the rows of A that should
   *         be swapped with rows of U. N must be at least zero.
   *
   * A       (local output)                double *
   *         On entry, A points to an array of dimension (LDA,N). On exit,
   *         the  rows of this array specified by  LINDXA  are replaced by
   *         rows or columns of U.
   *
   * LDA     (local input)                 const int
   *         On entry, LDA specifies the leading dimension of the array A.
   *         LDA must be at least MAX(1,M).
   *
   * U       (local input/output)          double *
   *         On entry,  U  points  to an array of dimension (LDU,N).  This
   *         array contains the rows of U that are to be swapped with rows
   *         of A.
   *
   * LDU     (local input)                 const int
   *         On entry, LDU specifies the leading dimension of the array U.
   *         LDU must be at least MAX(1,M).
   *
   * LINDXA  (local input)                 const int *
   *         On entry, LINDXA is an array of dimension M that contains the
   *         local row indexes of A that should be swapped with U.
   *
   * ---------------------------------------------------------------------
   */
  double r;
  double *U0 = U, *a0, *u0;
  const int incA = (int)((unsigned int)(LDA) << HPL_LASWP06N_LOG2_DEPTH),
            incU = (int)((unsigned int)(LDU) << HPL_LASWP06N_LOG2_DEPTH);
  int nr, nu;
  register int i, j;
  if ((M <= 0) || (N <= 0)) return;

  nr = N - (nu = (int)(((unsigned int)(N) >> HPL_LASWP06N_LOG2_DEPTH)
                       << HPL_LASWP06N_LOG2_DEPTH));

  for (j = 0; j < nu; j += HPL_LASWP06N_DEPTH, A += incA, U0 += incU) {
    for (i = 0; i < M; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U0 + (size_t)(i);

      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#if (HPL_LASWP06N_DEPTH > 1)
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP06N_DEPTH > 2)
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP06N_DEPTH > 4)
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP06N_DEPTH > 8)
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP06N_DEPTH > 16)
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
      r = *a0;
      *a0 = *u0;
      *u0 = r;
      a0 += LDA;
      u0 += LDU;
#endif
    }
  }

  if (nr) {
    for (i = 0; i < M; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U0 + (size_t)(i);
      for (j = 0; j < nr; j++, a0 += LDA, u0 += LDU) {
        r = *a0;
        *a0 = *u0;
        *u0 = r;
      }
    }
  }
}
