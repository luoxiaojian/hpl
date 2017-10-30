#include "hpl.h"
#ifndef HPL_LASWP00N_DEPTH
#define HPL_LASWP00N_DEPTH 32
#define HPL_LASWP00N_LOG2_DEPTH 5
#endif

void HPL_dlaswp00N(const int M, const int N, double* A, const int LDA,
                   const int* IPIV) {
  /*
   * Purpose
   * =======
   *
   * HPL_dlaswp00N performs a series of local row interchanges on a matrix
   * A. One row interchange is initiated for rows 0 through M-1 of A.
   *
   * Arguments
   * =========
   *
   * M       (local input)                 const int
   *         On entry, M specifies the number of rows of the array A to be
   *         interchanged. M must be at least zero.
   *
   * N       (local input)                 const int
   *         On entry, N  specifies  the number of columns of the array A.
   *         N must be at least zero.
   *
   * A       (local input/output)          double *
   *         On entry, A  points to an array of dimension (LDA,N) to which
   *         the row interchanges will be  applied.  On exit, the permuted
   *         matrix.
   *
   * LDA     (local input)                 const int
   *         On entry, LDA specifies the leading dimension of the array A.
   *         LDA must be at least MAX(1,M).
   *
   * IPIV    (local input)                 const int *
   *         On entry,  IPIV  is  an  array of size  M  that  contains the
   *         pivoting  information.  For  k  in [0..M),  IPIV[k]=IROFF + l
   *         implies that local rows k and l are to be interchanged.
   *
   * ---------------------------------------------------------------------
   */
  /*
   * .. Local Variables ..
   */
  register double r;
  double *a0, *a1;
  const int incA = (int)((unsigned int)(LDA) << HPL_LASWP00N_LOG2_DEPTH);
  int ip, nr, nu;
  register int i, j;
  /* ..
   * .. Executable Statements ..
   */
  if ((M <= 0) || (N <= 0)) return;

  nr = N - (nu = (int)(((unsigned int)(N) >> HPL_LASWP00N_LOG2_DEPTH)
                       << HPL_LASWP00N_LOG2_DEPTH));

  for (j = 0; j < nu; j += HPL_LASWP00N_DEPTH, A += incA) {
    for (i = 0; i < M; i++) {
      if (i != (ip = IPIV[i])) {
        a0 = A + i;
        a1 = A + ip;

        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#if (HPL_LASWP00N_DEPTH > 1)
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#endif
#if (HPL_LASWP00N_DEPTH > 2)
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#endif
#if (HPL_LASWP00N_DEPTH > 4)
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#endif
#if (HPL_LASWP00N_DEPTH > 8)
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#endif
#if (HPL_LASWP00N_DEPTH > 16)
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
        r = *a0;
        *a0 = *a1;
        *a1 = r;
        a0 += LDA;
        a1 += LDA;
#endif
      }
    }
  }

  if (nr > 0) {
    for (i = 0; i < M; i++) {
      if (i != (ip = IPIV[i])) {
        a0 = A + i;
        a1 = A + ip;
        for (j = 0; j < nr; j++, a0 += LDA, a1 += LDA) {
          r = *a0;
          *a0 = *a1;
          *a1 = r;
        }
      }
    }
  }
}
