#include "hpl.h"
#ifndef HPL_LASWP04N_DEPTH
#define HPL_LASWP04N_DEPTH 32
#define HPL_LASWP04N_LOG2_DEPTH 5
#endif

void HPL_dlaswp04N(const int M0, const int M1, const int N, double* U,
                   const int LDU, double* A, const int LDA, const double* W0,
                   const double* W, const int LDW, const int* LINDXA,
                   const int* LINDXAU) {
  /*
   * Purpose
   * =======
   *
   * HPL_dlaswp04N copies M0 rows of U into A and replaces those rows of U
   * with columns of W. In addition M1 - M0 columns of  W  are copied into
   * rows of U.
   *
   * Arguments
   * =========
   *
   * M0      (local input)                 const int
   *         On entry, M0 specifies the number of rows of U that should be
   *         copied into  A  and replaced by columns of  W.  M0 must be at
   *         least zero.
   *
   * M1      (local input)                 const int
   *         On entry, M1 specifies the number of columns of W that should
   *         be copied into rows of U. M1 must be at least zero.
   *
   * N       (local input)                 const int
   *         On entry, N specifies the length of the rows of U that should
   *         be copied into A. N must be at least zero.
   *
   * U       (local input/output)          double *
   *         On entry,  U  points to  an array of dimension (LDU,N).  This
   *         array contains the rows that are to be copied into A.
   *
   * LDU     (local input)                 const int
   *         On entry, LDU specifies the leading dimension of the array U.
   *         LDU must be at least MAX(1,M1).
   *
   * A       (local output)                double *
   *         On entry, A points to an array of dimension (LDA,N). On exit,
   *         the  rows of this array specified by  LINDXA  are replaced by
   *         rows of U indicated by LINDXAU.
   *
   * LDA     (local input)                 const int
   *         On entry, LDA specifies the leading dimension of the array A.
   *         LDA must be at least MAX(1,M0).
   *
   * W0      (local input)                 const double *
   *         On entry,  W0  is an array of size (M-1)*LDW+1, that contains
   *         the destination offset  in U where the columns of W should be
   *         copied.
   *
   * W       (local input)                 const double *
   *         On entry, W  is an array of size (LDW,M0+M1),  that  contains
   *         data to be copied into U.  For i in [M0..M0+M1),  the entries
   *         W(:,i) are copied into the row W0(i*LDW) of U.
   *
   * LDW     (local input)                 const int
   *         On entry, LDW specifies the leading dimension of the array W.
   *         LDW must be at least MAX(1,N+1).
   *
   * LINDXA  (local input)                 const int *
   *         On entry, LINDXA  is an array of dimension  M0 containing the
   *         local row indexes A into which rows of U are copied.
   *
   * LINDXAU (local input)                 const int *
   *         On entry, LINDXAU  is an array of dimension M0 that  contains
   *         the local  row indexes of  U that should be copied into A and
   *         replaced by the columns of W.
   *
   * ---------------------------------------------------------------------
   */
  /*
   * .. Local Variables ..
   */
  const double *w = W, *w0;
  double *a0, *u0;
  const int incA = (int)((unsigned int)(LDA) << HPL_LASWP04N_LOG2_DEPTH),
            incU = (int)((unsigned int)(LDU) << HPL_LASWP04N_LOG2_DEPTH);
  int nr, nu;
  register int i, j;
  /* ..
   * .. Executable Statements ..
   */
  if (((M0 <= 0) && (M1 <= 0)) || (N <= 0)) return;

  nr = N - (nu = (int)(((unsigned int)(N) >> HPL_LASWP04N_LOG2_DEPTH)
                       << HPL_LASWP04N_LOG2_DEPTH));

  for (j = 0; j < nu;
       j += HPL_LASWP04N_DEPTH, A += incA, U += incU, w += HPL_LASWP04N_DEPTH) {
    for (i = 0; i < M0; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U + (size_t)(LINDXAU[i]);
      w0 = w + (size_t)(i) * (size_t)(LDW);

      *a0 = *u0;
      *u0 = w0[0];
      a0 += LDA;
      u0 += LDU;
#if (HPL_LASWP04N_DEPTH > 1)
      *a0 = *u0;
      *u0 = w0[1];
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 2)
      *a0 = *u0;
      *u0 = w0[2];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[3];
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 4)
      *a0 = *u0;
      *u0 = w0[4];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[5];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[6];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[7];
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 8)
      *a0 = *u0;
      *u0 = w0[8];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[9];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[10];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[11];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[12];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[13];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[14];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[15];
      a0 += LDA;
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 16)
      *a0 = *u0;
      *u0 = w0[16];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[17];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[18];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[19];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[20];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[21];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[22];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[23];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[24];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[25];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[26];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[27];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[28];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[29];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[30];
      a0 += LDA;
      u0 += LDU;
      *a0 = *u0;
      *u0 = w0[31];
      a0 += LDA;
      u0 += LDU;
#endif
    }

    for (i = M0; i < M1; i++) {
      u0 = U + (size_t)(*(W0 + (size_t)(i) * (size_t)(LDW)));
      w0 = w + (size_t)(i) * (size_t)(LDW);

      *u0 = w0[0];
      u0 += LDU;
#if (HPL_LASWP04N_DEPTH > 1)
      *u0 = w0[1];
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 2)
      *u0 = w0[2];
      u0 += LDU;
      *u0 = w0[3];
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 4)
      *u0 = w0[4];
      u0 += LDU;
      *u0 = w0[5];
      u0 += LDU;
      *u0 = w0[6];
      u0 += LDU;
      *u0 = w0[7];
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 8)
      *u0 = w0[8];
      u0 += LDU;
      *u0 = w0[9];
      u0 += LDU;
      *u0 = w0[10];
      u0 += LDU;
      *u0 = w0[11];
      u0 += LDU;
      *u0 = w0[12];
      u0 += LDU;
      *u0 = w0[13];
      u0 += LDU;
      *u0 = w0[14];
      u0 += LDU;
      *u0 = w0[15];
      u0 += LDU;
#endif
#if (HPL_LASWP04N_DEPTH > 16)
      *u0 = w0[16];
      u0 += LDU;
      *u0 = w0[17];
      u0 += LDU;
      *u0 = w0[18];
      u0 += LDU;
      *u0 = w0[19];
      u0 += LDU;
      *u0 = w0[20];
      u0 += LDU;
      *u0 = w0[21];
      u0 += LDU;
      *u0 = w0[22];
      u0 += LDU;
      *u0 = w0[23];
      u0 += LDU;
      *u0 = w0[24];
      u0 += LDU;
      *u0 = w0[25];
      u0 += LDU;
      *u0 = w0[26];
      u0 += LDU;
      *u0 = w0[27];
      u0 += LDU;
      *u0 = w0[28];
      u0 += LDU;
      *u0 = w0[29];
      u0 += LDU;
      *u0 = w0[30];
      u0 += LDU;
      *u0 = w0[31];
      u0 += LDU;
#endif
    }
  }

  if (nr) {
    for (i = 0; i < M0; i++) {
      a0 = A + (size_t)(LINDXA[i]);
      u0 = U + (size_t)(LINDXAU[i]);
      w0 = w + (size_t)(i) * (size_t)(LDW);
      for (j = 0; j < nr; j++, a0 += LDA, u0 += LDU) {
        *a0 = *u0;
        *u0 = w0[j];
      }
    }
    for (i = M0; i < M1; i++) {
      u0 = U + (size_t)(*(W0 + (size_t)(i) * (size_t)(LDW)));
      w0 = w + (size_t)(i) * (size_t)(LDW);
      for (j = 0; j < nr; j++, u0 += LDU) {
        *u0 = w0[j];
      }
    }
  }
}
