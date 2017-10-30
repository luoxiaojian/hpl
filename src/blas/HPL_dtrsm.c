#include "hpl.h"

#ifndef HPL_dtrsm

#ifdef HPL_CALL_VSIPL

static void HPL_dtrsmLLNN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iaik, ibij, ibkj, j, jak, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = 0, jak = 0, ibkj = jbj; k < M; k++, jak += LDA, ibkj += 1) {
      B[ibkj] /= A[k + jak];
      for (i = k + 1, iaik = k + 1 + jak, ibij = k + 1 + jbj; i < M;
           i++, iaik += 1, ibij += 1) {
        B[ibij] -= B[ibkj] * A[iaik];
      }
    }
  }
}

static void HPL_dtrsmLLNU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iaik, ibij, ibkj, j, jak, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = 0, jak = 0, ibkj = jbj; k < M; k++, jak += LDA, ibkj += 1) {
      for (i = k + 1, iaik = k + 1 + jak, ibij = k + 1 + jbj; i < M;
           i++, iaik += 1, ibij += 1) {
        B[ibij] -= B[ibkj] * A[iaik];
      }
    }
  }
}

static void HPL_dtrsmLLTN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iaki, ibij, ibkj, j, jai, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = M - 1, jai = (M - 1) * LDA, ibij = M - 1 + jbj; i >= 0;
         i--, jai -= LDA, ibij -= 1) {
      t0 = ALPHA * B[ibij];
      for (k = i + 1, iaki = i + 1 + jai, ibkj = i + 1 + jbj; k < M;
           k++, iaki += 1, ibkj += 1) {
        t0 -= A[iaki] * B[ibkj];
      }
      t0 /= A[i + jai];
      B[ibij] = t0;
    }
  }
}

static void HPL_dtrsmLLTU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iaki, ibij, ibkj, j, jai, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = M - 1, jai = (M - 1) * LDA, ibij = M - 1 + jbj; i >= 0;
         i--, jai -= LDA, ibij -= 1) {
      t0 = ALPHA * B[ibij];
      for (k = i + 1, iaki = i + 1 + jai, ibkj = i + 1 + jbj; k < M;
           k++, iaki += 1, ibkj += 1) {
        t0 -= A[iaki] * B[ibkj];
      }
      B[ibij] = t0;
    }
  }
}

static void HPL_dtrsmLUNN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iaik, ibij, ibkj, j, jak, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = M - 1, jak = (M - 1) * LDA, ibkj = M - 1 + jbj; k >= 0;
         k--, jak -= LDA, ibkj -= 1) {
      B[ibkj] /= A[k + jak];
      for (i = 0, iaik = jak, ibij = jbj; i < k; i++, iaik += 1, ibij += 1) {
        B[ibij] -= B[ibkj] * A[iaik];
      }
    }
  }
}

static void HPL_dtrsmLUNU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iaik, ibij, ibkj, j, jak, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = M - 1, jak = (M - 1) * LDA, ibkj = M - 1 + jbj; k >= 0;
         k--, jak -= LDA, ibkj -= 1) {
      for (i = 0, iaik = jak, ibij = jbj; i < k; i++, iaik += 1, ibij += 1) {
        B[ibij] -= B[ibkj] * A[iaik];
      }
    }
  }
}

static void HPL_dtrsmLUTN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iaki, ibij, ibkj, j, jai, jbj, k;
  register double t0;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, jai = 0, ibij = jbj; i < M; i++, jai += LDA, ibij += 1) {
      t0 = ALPHA * B[ibij];
      for (k = 0, iaki = jai, ibkj = jbj; k < i; k++, iaki += 1, ibkj += 1) {
        t0 -= A[iaki] * B[ibkj];
      }
      t0 /= A[i + jai];
      B[ibij] = t0;
    }
  }
}

static void HPL_dtrsmLUTU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iaki, ibij, ibkj, j, jai, jbj, k;

  for (j = 0, jbj = 0; j < N; j++, jbj += LDB) {
    for (i = 0, jai = 0, ibij = jbj; i < M; i++, jai += LDA, ibij += 1) {
      t0 = ALPHA * B[ibij];
      for (k = 0, iaki = jai, ibkj = jbj; k < i; k++, iaki += 1, ibkj += 1) {
        t0 -= A[iaki] * B[ibkj];
      }
      B[ibij] = t0;
    }
  }
}

static void HPL_dtrsmRLNN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

  for (j = N - 1, jaj = (N - 1) * LDA, jbj = (N - 1) * LDB; j >= 0;
       j--, jaj -= LDA, jbj -= LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = j + 1, iakj = j + 1 + jaj, jbk = (j + 1) * LDB; k < N;
         k++, iakj += 1, jbk += LDB) {
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= A[iakj] * B[ibik];
      }
    }
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] /= A[j + jaj];
    }
  }
}

static void HPL_dtrsmRLNU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

  for (j = N - 1, jaj = (N - 1) * LDA, jbj = (N - 1) * LDB; j >= 0;
       j--, jaj -= LDA, jbj -= LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = j + 1, iakj = j + 1 + jaj, jbk = (j + 1) * LDB; k < N;
         k++, iakj += 1, jbk += LDB) {
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= A[iakj] * B[ibik];
      }
    }
  }
}

static void HPL_dtrsmRLTN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

  for (k = 0, jak = 0, jbk = 0; k < N; k++, jak += LDA, jbk += LDB) {
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] /= A[k + jak];
    }
    for (j = k + 1, iajk = (k + 1) + jak, jbj = (k + 1) * LDB; j < N;
         j++, iajk += 1, jbj += LDB) {
      t0 = A[iajk];
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= t0 * B[ibik];
      }
    }
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] *= ALPHA;
    }
  }
}

static void HPL_dtrsmRLTU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

  for (k = 0, jak = 0, jbk = 0; k < N; k++, jak += LDA, jbk += LDB) {
    for (j = k + 1, iajk = (k + 1) + jak, jbj = (k + 1) * LDB; j < N;
         j++, iajk += 1, jbj += LDB) {
      t0 = A[iajk];
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= t0 * B[ibik];
      }
    }
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] *= ALPHA;
    }
  }
}

static void HPL_dtrsmRUNN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

  for (j = 0, jaj = 0, jbj = 0; j < N; j++, jaj += LDA, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = 0, iakj = jaj, jbk = 0; k < j; k++, iakj += 1, jbk += LDB) {
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= A[iakj] * B[ibik];
      }
    }
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] /= A[j + jaj];
    }
  }
}

static void HPL_dtrsmRUNU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  int i, iakj, ibij, ibik, j, jaj, jbj, jbk, k;

  for (j = 0, jaj = 0, jbj = 0; j < N; j++, jaj += LDA, jbj += LDB) {
    for (i = 0, ibij = jbj; i < M; i++, ibij += 1) {
      B[ibij] *= ALPHA;
    }
    for (k = 0, iakj = jaj, jbk = 0; k < j; k++, iakj += 1, jbk += LDB) {
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= A[iakj] * B[ibik];
      }
    }
  }
}

static void HPL_dtrsmRUTN(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

  for (k = N - 1, jak = (N - 1) * LDA, jbk = (N - 1) * LDB; k >= 0;
       k--, jak -= LDA, jbk -= LDB) {
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] /= A[k + jak];
    }
    for (j = 0, iajk = jak, jbj = 0; j < k; j++, iajk += 1, jbj += LDB) {
      t0 = A[iajk];
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= t0 * B[ibik];
      }
    }
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] *= ALPHA;
    }
  }
}

static void HPL_dtrsmRUTU(const int M, const int N, const double ALPHA,
                          const double* A, const int LDA, double* B,
                          const int LDB) {
  register double t0;
  int i, iajk, ibij, ibik, j, jak, jbj, jbk, k;

  for (k = N - 1, jak = (N - 1) * LDA, jbk = (N - 1) * LDB; k >= 0;
       k--, jak -= LDA, jbk -= LDB) {
    for (j = 0, iajk = jak, jbj = 0; j < k; j++, iajk += 1, jbj += LDB) {
      t0 = A[iajk];
      for (i = 0, ibij = jbj, ibik = jbk; i < M; i++, ibij += 1, ibik += 1) {
        B[ibij] -= t0 * B[ibik];
      }
    }
    for (i = 0, ibik = jbk; i < M; i++, ibik += 1) {
      B[ibik] *= ALPHA;
    }
  }
}

static void HPL_dtrsm0(const enum HPL_SIDE SIDE, const enum HPL_UPLO UPLO,
                       const enum HPL_TRANS TRANS, const enum HPL_DIAG DIAG,
                       const int M, const int N, const double ALPHA,
                       const double* A, const int LDA, double* B,
                       const int LDB) {
  int i, j;

  if ((M == 0) || (N == 0)) return;

  if (ALPHA == HPL_rzero) {
    for (j = 0; j < N; j++) {
      for (i = 0; i < M; i++) *(B + i + j * LDB) = HPL_rzero;
    }
    return;
  }

  if (SIDE == HplLeft) {
    if (UPLO == HplUpper) {
      if (TRANS == HplNoTrans) {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmLUNN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmLUNU(M, N, ALPHA, A, LDA, B, LDB);
        }
      } else {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmLUTN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmLUTU(M, N, ALPHA, A, LDA, B, LDB);
        }
      }
    } else {
      if (TRANS == HplNoTrans) {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmLLNN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmLLNU(M, N, ALPHA, A, LDA, B, LDB);
        }
      } else {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmLLTN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmLLTU(M, N, ALPHA, A, LDA, B, LDB);
        }
      }
    }
  } else {
    if (UPLO == HplUpper) {
      if (TRANS == HplNoTrans) {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmRUNN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmRUNU(M, N, ALPHA, A, LDA, B, LDB);
        }
      } else {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmRUTN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmRUTU(M, N, ALPHA, A, LDA, B, LDB);
        }
      }
    } else {
      if (TRANS == HplNoTrans) {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmRLNN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmRLNU(M, N, ALPHA, A, LDA, B, LDB);
        }
      } else {
        if (DIAG == HplNonUnit) {
          HPL_dtrsmRLTN(M, N, ALPHA, A, LDA, B, LDB);
        } else {
          HPL_dtrsmRLTU(M, N, ALPHA, A, LDA, B, LDB);
        }
      }
    }
  }
}

#endif

void HPL_dtrsm(const enum HPL_ORDER ORDER, const enum HPL_SIDE SIDE,
               const enum HPL_UPLO UPLO, const enum HPL_TRANS TRANS,
               const enum HPL_DIAG DIAG, const int M, const int N,
               const double ALPHA, const double* A, const int LDA, double* B,
               const int LDB) {
/*
 * Purpose
 * =======
 *
 * HPL_dtrsm solves one of the matrix equations
 *
 *    op( A ) * X = alpha * B,   or  X * op( A ) = alpha * B,
 *
 * where alpha is a scalar, X and B are m by n matrices, A is a unit, or
 * non-unit, upper or lower triangular matrix and op(A) is one of
 *
 *    op( A ) = A   or   op( A ) = A^T.
 *
 * The matrix X is overwritten on B.
 *
 * No test for  singularity  or  near-singularity  is included  in  this
 * routine. Such tests must be performed before calling this routine.
 *
 * Arguments
 * =========
 *
 * ORDER   (local input)                 const enum HPL_ORDER
 *         On entry, ORDER  specifies the storage format of the operands
 *         as follows:
 *            ORDER = HplRowMajor,
 *            ORDER = HplColumnMajor.
 *
 * SIDE    (local input)                 const enum HPL_SIDE
 *         On entry, SIDE  specifies  whether  op(A) appears on the left
 *         or right of X as follows:
 *            SIDE==HplLeft    op( A ) * X = alpha * B,
 *            SIDE==HplRight   X * op( A ) = alpha * B.
 *
 * UPLO    (local input)                 const enum HPL_UPLO
 *         On  entry,   UPLO   specifies  whether  the  upper  or  lower
 *         triangular  part  of the array  A  is to be referenced.  When
 *         UPLO==HplUpper, only  the upper triangular part of A is to be
 *         referenced, otherwise only the lower triangular part of A is
 *         to be referenced.
 *
 * TRANS   (local input)                 const enum HPL_TRANS
 *         On entry, TRANSA  specifies the form of  op(A)  to be used in
 *         the matrix-matrix operation follows:
 *            TRANSA==HplNoTrans    : op( A ) = A,
 *            TRANSA==HplTrans      : op( A ) = A^T,
 *            TRANSA==HplConjTrans  : op( A ) = A^T.
 *
 * DIAG    (local input)                 const enum HPL_DIAG
 *         On entry,  DIAG  specifies  whether  A  is unit triangular or
 *         not. When DIAG==HplUnit,  A is assumed to be unit triangular,
 *         and otherwise, A is not assumed to be unit triangular.
 *
 * M       (local input)                 const int
 *         On entry,  M  specifies  the number of rows of the  matrix B.
 *         M must be at least zero.
 *
 * N       (local input)                 const int
 *         On entry, N  specifies the number of columns of the matrix B.
 *         N must be at least zero.
 *
 * ALPHA   (local input)                 const double
 *         On entry, ALPHA specifies the scalar alpha.   When  ALPHA  is
 *         supplied  as  zero then the elements of the matrix B need not
 *         be set on input.
 *
 * A       (local input)                 const double *
 *         On entry,  A  points  to an array of size equal to or greater
 *         than LDA * k,  where  k is m  when  SIDE==HplLeft  and  is  n
 *         otherwise.  Before  entry  with  UPLO==HplUpper,  the leading
 *         k by k upper triangular  part of the array A must contain the
 *         upper triangular  matrix and the  strictly  lower  triangular
 *         part of A is not referenced.  When  UPLO==HplLower on  entry,
 *         the  leading k by k lower triangular part of the array A must
 *         contain the lower triangular matrix  and  the  strictly upper
 *         triangular part of A is not referenced.
 *
 *         Note that  when  DIAG==HplUnit,  the  diagonal elements of  A
 *         not referenced  either,  but are assumed to be unity.
 *
 * LDA     (local input)                 const int
 *         On entry,  LDA  specifies  the  leading  dimension  of  A  as
 *         declared  in  the  calling  (sub) program.  LDA  must  be  at
 *         least MAX(1,m) when SIDE==HplLeft, and MAX(1,n) otherwise.
 *
 * B       (local input/output)          double *
 *         On entry,  B  points  to an array of size equal to or greater
 *         than LDB * n.  Before entry, the leading  m by n  part of the
 *         array B must contain the matrix  B, except when beta is zero,
 *         in which case B need not be set on entry.  On exit, the array
 *         B is overwritten by the m by n solution matrix.
 *
 * LDB     (local input)                 const int
 *         On entry,  LDB  specifies  the  leading  dimension  of  B  as
 *         declared  in  the  calling  (sub) program.  LDB  must  be  at
 *         least MAX(1,m).
 *
 * ---------------------------------------------------------------------
 */
#ifdef HPL_CALL_CBLAS
  cblas_dtrsm(ORDER, SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB);
#endif
#ifdef HPL_CALL_VSIPL
  if (ORDER == HplColumnMajor) {
    HPL_dtrsm0(SIDE, UPLO, TRANS, DIAG, M, N, ALPHA, A, LDA, B, LDB);
  } else {
    HPL_dtrsm0((SIDE == HplRight ? HplLeft : HplRight),
               (UPLO == HplLower ? HplUpper : HplLower), TRANS, DIAG, N, M,
               ALPHA, A, LDA, B, LDB);
  }
#endif
#ifdef HPL_CALL_FBLAS
  double alpha = ALPHA;
#ifdef StringSunStyle
#if defined(HPL_USE_F77_INTEGER_DEF)
  F77_INTEGER IONE = 1;
#else
  int IONE = 1;
#endif
#endif
#ifdef StringStructVal
  F77_CHAR fside;
  F77_CHAR fuplo;
  F77_CHAR ftran;
  F77_CHAR fdiag;
#endif
#ifdef StringStructPtr
  F77_CHAR fside;
  F77_CHAR fuplo;
  F77_CHAR ftran;
  F77_CHAR fdiag;
#endif
#ifdef StringCrayStyle
  F77_CHAR fside;
  F77_CHAR fuplo;
  F77_CHAR ftran;
  F77_CHAR fdiag;
#endif
#ifdef HPL_USE_F77_INTEGER_DEF
  const F77_INTEGER F77M = M, F77N = N, F77lda = LDA, F77ldb = LDB;
#else
#define F77M M
#define F77N N
#define F77lda LDA
#define F77ldb LDB
#endif
  char cside, cuplo, ctran, cdiag;

  if (TRANS == HplNoTrans)
    ctran = 'N';
  else if (TRANS == HplTrans)
    ctran = 'T';
  else
    ctran = 'C';
  cdiag = (DIAG == HplUnit ? 'U' : 'N');

  if (ORDER == HplColumnMajor) {
    cside = (SIDE == HplRight ? 'R' : 'L');
    cuplo = (UPLO == HplLower ? 'L' : 'U');
#ifdef StringSunStyle
    F77dtrsm(&cside, &cuplo, &ctran, &cdiag, &F77M, &F77N, &alpha, A, &F77lda,
             B, &F77ldb, IONE, IONE, IONE, IONE);
#endif
#ifdef StringCrayStyle
    fside = HPL_C2F_CHAR(cside);
    fuplo = HPL_C2F_CHAR(cuplo);
    ftran = HPL_C2F_CHAR(ctran);
    fdiag = HPL_C2F_CHAR(cdiag);
    F77dtrsm(fside, fuplo, ftran, fdiag, &F77M, &F77N, &alpha, A, &F77lda, B,
             &F77ldb);
#endif
#ifdef StringStructVal
    fside.len = 1;
    fside.cp = &cside;
    fuplo.len = 1;
    fuplo.cp = &cuplo;
    ftran.len = 1;
    ftran.cp = &ctran;
    fdiag.len = 1;
    fdiag.cp = &cdiag;
    F77dtrsm(fside, fuplo, ftran, fdiag, &F77M, &F77N, &alpha, A, &F77lda, B,
             &F77ldb);
#endif
#ifdef StringStructPtr
    fside.len = 1;
    fside.cp = &cside;
    fuplo.len = 1;
    fuplo.cp = &cuplo;
    ftran.len = 1;
    ftran.cp = &ctran;
    fdiag.len = 1;
    fdiag.cp = &cdiag;
    F77dtrsm(&fside, &fuplo, &ftran, &fdiag, &F77M, &F77N, &alpha, A, &F77lda,
             B, &F77ldb);
#endif
  } else {
    cside = (SIDE == HplRight ? 'L' : 'R');
    cuplo = (UPLO == HplLower ? 'U' : 'L');
#ifdef StringSunStyle
    F77dtrsm(&cside, &cuplo, &ctran, &cdiag, &F77N, &F77M, &alpha, A, &F77lda,
             B, &F77ldb, IONE, IONE, IONE, IONE);
#endif
#ifdef StringCrayStyle
    fside = HPL_C2F_CHAR(cside);
    fuplo = HPL_C2F_CHAR(cuplo);
    ftran = HPL_C2F_CHAR(ctran);
    fdiag = HPL_C2F_CHAR(cdiag);
    F77dtrsm(fside, fuplo, ftran, fdiag, &F77N, &F77M, &alpha, A, &F77lda, B,
             &F77ldb);
#endif
#ifdef StringStructVal
    fside.len = 1;
    fside.cp = &cside;
    fuplo.len = 1;
    fuplo.cp = &cuplo;
    ftran.len = 1;
    ftran.cp = &ctran;
    fdiag.len = 1;
    fdiag.cp = &cdiag;
    F77dtrsm(fside, fuplo, ftran, fdiag, &F77N, &F77M, &alpha, A, &F77lda, B,
             &F77ldb);
#endif
#ifdef StringStructPtr
    fside.len = 1;
    fside.cp = &cside;
    fuplo.len = 1;
    fuplo.cp = &cuplo;
    ftran.len = 1;
    ftran.cp = &ctran;
    fdiag.len = 1;
    fdiag.cp = &cdiag;
    F77dtrsm(&fside, &fuplo, &ftran, &fdiag, &F77N, &F77M, &alpha, A, &F77lda,
             B, &F77ldb);
#endif
  }
#endif
}

#endif
