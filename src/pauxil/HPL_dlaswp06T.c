#include "hpl.h"
/*
 * Define default value for unrolling factor
 */
#ifndef HPL_LASWP06T_DEPTH
#define HPL_LASWP06T_DEPTH 32
#define HPL_LASWP06T_LOG2_DEPTH 5
#endif

void HPL_dlaswp06T(const int M, const int N, double* A, const int LDA,
                   double* U, const int LDU, const int* LINDXA) {
  /*
   * Purpose
   * =======
   *
   * HPL_dlaswp06T swaps  columns  of  U  with  rows  of  A  at  positions
   * indicated by LINDXA.
   *
   * Arguments
   * =========
   *
   * M       (local input)                 const int
   *         On entry, M  specifies the number of rows of A that should be
   *         swapped with columns of U. M must be at least zero.
   *
   * N       (local input)                 const int
   *         On entry, N specifies the length of the rows of A that should
   *         be swapped with columns of U. N must be at least zero.
   *
   * A       (local output)                double *
   *         On entry, A points to an array of dimension (LDA,N). On exit,
   *         the  rows of this array specified by  LINDXA  are replaced by
   *         columns of U.
   *
   * LDA     (local input)                 const int
   *         On entry, LDA specifies the leading dimension of the array A.
   *         LDA must be at least MAX(1,M).
   *
   * U       (local input/output)          double *
   *         On entry,  U  points  to an array of dimension (LDU,*).  This
   *         array contains the columns of  U  that are to be swapped with
   *         rows of A.
   *
   * LDU     (local input)                 const int
   *         On entry, LDU specifies the leading dimension of the array U.
   *         LDU must be at least MAX(1,N).
   *
   * LINDXA  (local input)                 const int *
   *         On entry, LINDXA is an array of dimension M that contains the
   *         local row indexes of A that should be swapped with U.
   *
   * ---------------------------------------------------------------------
   */
  double r;
  double *U0 = U, *a0, *u0;
  const int incA = (int)((unsigned int)(LDA) << HPL_LASWP06T_LOG2_DEPTH),
            incU = (1 << HPL_LASWP06T_LOG2_DEPTH);
  int nr, nu;
  register int i, j;
  if ((M <= 0) || (N <= 0)) return;

  nr = N - (nu = (int)(((unsigned int)(N) >> HPL_LASWP06T_LOG2_DEPTH)
                       << HPL_LASWP06T_LOG2_DEPTH));

  for (j = 0; j < nu; j += HPL_LASWP06T_DEPTH, A += incA, U0 += incU) {
    for (i = 0; i < M; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U0 + (size_t)(i) * (size_t)(LDU);

      r = *a0;
      *a0 = u0[0];
      u0[0] = r;
      a0 += LDA;
#if (HPL_LASWP06T_DEPTH > 1)
      r = *a0;
      *a0 = u0[1];
      u0[1] = r;
      a0 += LDA;
#endif
#if (HPL_LASWP06T_DEPTH > 2)
      r = *a0;
      *a0 = u0[2];
      u0[2] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[3];
      u0[3] = r;
      a0 += LDA;
#endif
#if (HPL_LASWP06T_DEPTH > 4)
      r = *a0;
      *a0 = u0[4];
      u0[4] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[5];
      u0[5] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[6];
      u0[6] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[7];
      u0[7] = r;
      a0 += LDA;
#endif
#if (HPL_LASWP06T_DEPTH > 8)
      r = *a0;
      *a0 = u0[8];
      u0[8] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[9];
      u0[9] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[10];
      u0[10] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[11];
      u0[11] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[12];
      u0[12] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[13];
      u0[13] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[14];
      u0[14] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[15];
      u0[15] = r;
      a0 += LDA;
#endif
#if (HPL_LASWP06T_DEPTH > 16)
      r = *a0;
      *a0 = u0[16];
      u0[16] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[17];
      u0[17] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[18];
      u0[18] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[19];
      u0[19] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[20];
      u0[20] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[21];
      u0[21] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[22];
      u0[22] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[23];
      u0[23] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[24];
      u0[24] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[25];
      u0[25] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[26];
      u0[26] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[27];
      u0[27] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[28];
      u0[28] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[29];
      u0[29] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[30];
      u0[30] = r;
      a0 += LDA;
      r = *a0;
      *a0 = u0[31];
      u0[31] = r;
      a0 += LDA;
#endif
    }
  }

  if (nr > 0) {
    for (i = 0; i < M; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U0 + (size_t)(i) * (size_t)(LDU);
      for (j = 0; j < nr; j++, a0 += LDA) {
        r = *a0;
        *a0 = u0[j];
        u0[j] = r;
      }
    }
  }
}
