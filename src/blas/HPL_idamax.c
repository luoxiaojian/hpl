#include "hpl.h"

#ifndef HPL_idamax

int HPL_idamax(const int N, const double* X, const int INCX) {
/*
 * Purpose
 * =======
 *
 * HPL_idamax returns  the index in an n-vector  x  of the first element
 * having maximum absolute value.
 *
 * Arguments
 * =========
 *
 * N       (local input)                 const int
 *         On entry, N specifies the length of the vector x. N  must  be
 *         at least zero.
 *
 * X       (local input)                 const double *
 *         On entry,  X  is an incremented array of dimension  at  least
 *         ( 1 + ( n - 1 ) * abs( INCX ) )  that  contains the vector x.
 *
 * INCX    (local input)                 const int
 *         On entry, INCX specifies the increment for the elements of X.
 *         INCX must not be zero.
 *
 * ---------------------------------------------------------------------
 */
#ifdef HPL_CALL_CBLAS
  return ((int)(cblas_idamax(N, X, INCX)));
#endif
#ifdef HPL_CALL_VSIPL
  register double absxi, smax = HPL_rzero, x0, x1, x2, x3, x4, x5, x6, x7;
  const double* StX;
  register int imax = 0, i = 0, j;
  int nu;
  const int incX2 = 2 * INCX, incX3 = 3 * INCX, incX4 = 4 * INCX,
            incX5 = 5 * INCX, incX6 = 6 * INCX, incX7 = 7 * INCX,
            incX8 = 8 * INCX;

  if (N > 0) {
    if ((nu = (N >> 3) << 3) != 0) {
      StX = X + nu * INCX;

      do {
        x0 = (*X);
        x4 = X[incX4];
        x1 = X[INCX];
        x5 = X[incX5];
        x2 = X[incX2];
        x6 = X[incX6];
        x3 = X[incX3];
        x7 = X[incX7];

        absxi = Mabs(x0);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x1);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x2);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x3);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x4);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x5);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x6);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;
        absxi = Mabs(x7);
        if (absxi > smax) {
          imax = i;
          smax = absxi;
        }
        i += 1;

        X += incX8;

      } while (X != StX);
    }

    for (j = N - nu; j != 0; j--) {
      x0 = (*X);
      absxi = Mabs(x0);
      if (absxi > smax) {
        imax = i;
        smax = absxi;
      }
      i += 1;
      X += INCX;
    }
  }
  return (imax);
#endif
#ifdef HPL_CALL_FBLAS
#ifdef HPL_USE_F77_INTEGER_DEF
  const F77_INTEGER F77N = N, F77incx = INCX;
#else
#define F77N N
#define F77incx INCX
#endif
  int imax = 0;

  if (N > 0) imax = F77idamax(&F77N, X, &F77incx) - 1;
  return (imax);
#endif
}

#endif
