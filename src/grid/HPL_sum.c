#include "hpl.h"

void HPL_sum(const int N, const void *IN, void *INOUT, const HPL_T_TYPE DTYPE) {
  register int i;
  if (DTYPE == HPL_INT) {
    const int *a = (const int *)(IN);
    int *b = (int *)(INOUT);
    for (i = 0; i < N; i++) b[i] += a[i];
  } else {
    const double *a = (const double *)(IN);
    double *b = (double *)(INOUT);
    for (i = 0; i < N; i++) b[i] += a[i];
  }
}
