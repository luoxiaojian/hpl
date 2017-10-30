#include "hpl.h"

int HPL_recv(double *RBUF, int RCOUNT, int SRC, int RTAG, MPI_Comm COMM) {
  MPI_Status status;
  int ierr;
  if (RCOUNT <= 0) return (HPL_SUCCESS);

  ierr = MPI_Recv((void *)(RBUF), RCOUNT, MPI_DOUBLE, SRC, RTAG, COMM, &status);
  return ((ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE));
}
