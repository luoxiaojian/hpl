#include "hpl.h"

int HPL_sdrv(double *SBUF, int SCOUNT, int STAG, double *RBUF, int RCOUNT,
             int RTAG, int PARTNER, MPI_Comm COMM) {
  MPI_Request request;
  MPI_Status status;
  int ierr;
  if (RCOUNT > 0) {
    if (SCOUNT > 0) {
      ierr = MPI_Irecv((void *)(RBUF), RCOUNT, MPI_DOUBLE, PARTNER, RTAG, COMM,
                       &request);
      if (ierr == MPI_SUCCESS)
        ierr =
            MPI_Send((void *)(SBUF), SCOUNT, MPI_DOUBLE, PARTNER, STAG, COMM);
      if (ierr == MPI_SUCCESS) ierr = MPI_Wait(&request, &status);
    } else {
      ierr = MPI_Recv((void *)(RBUF), RCOUNT, MPI_DOUBLE, PARTNER, RTAG, COMM,
                      &status);
    }
  } else if (SCOUNT > 0) {
    ierr = MPI_Send((void *)(SBUF), SCOUNT, MPI_DOUBLE, PARTNER, STAG, COMM);
  } else {
    ierr = MPI_SUCCESS;
  }

  return ((ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE));
}
