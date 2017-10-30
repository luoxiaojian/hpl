#include "hpl.h"

int HPL_send(double *SBUF, int SCOUNT, int DEST, int STAG, MPI_Comm COMM) {
  int ierr;
  if (SCOUNT <= 0) return (HPL_SUCCESS);

  ierr = MPI_Send((void *)(SBUF), SCOUNT, MPI_DOUBLE, DEST, STAG, COMM);
  return ((ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE));
}
