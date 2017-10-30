#include "hpl.h"

int HPL_reduce(void *BUFFER, const int COUNT, const HPL_T_TYPE DTYPE,
               const HPL_T_OP OP, const int ROOT, MPI_Comm COMM) {
  MPI_Status status;
  void *buffer = NULL;
  int hplerr = MPI_SUCCESS, d = 1, i, ip2 = 1, mask = 0, mpierr, mydist,
      partner, rank, size, tag = MSGID_BEGIN_COLL;
  if (COUNT <= 0) return (MPI_SUCCESS);
  mpierr = MPI_Comm_size(COMM, &size);
  if (size == 1) return (MPI_SUCCESS);
  mpierr = MPI_Comm_rank(COMM, &rank);
  i = size - 1;
  while (i > 1) {
    i >>= 1;
    d++;
  }

  if (DTYPE == HPL_INT)
    buffer = (void *)((int *)malloc((size_t)(COUNT) * sizeof(int)));
  else
    buffer = (void *)((double *)malloc((size_t)(COUNT) * sizeof(double)));

  if (!(buffer)) {
    HPL_pabort(__LINE__, "HPL_reduce", "Memory allocation failed");
  }

  if ((mydist = MModSub(rank, ROOT, size)) == 0) {
    do {
      mpierr = MPI_Recv(buffer, COUNT, HPL_2_MPI_TYPE(DTYPE),
                        MModAdd(ROOT, ip2, size), tag, COMM, &status);
      if (mpierr != MPI_SUCCESS) hplerr = mpierr;
      OP(COUNT, buffer, BUFFER, DTYPE);
      ip2 <<= 1;
      d--;
    } while (d);
  } else {
    do {
      if ((mydist & mask) == 0) {
        partner = mydist ^ ip2;

        if (mydist & ip2) {
          partner = MModAdd(ROOT, partner, size);
          mpierr = MPI_Send(BUFFER, COUNT, HPL_2_MPI_TYPE(DTYPE), partner, tag,
                            COMM);
        } else if (partner < size) {
          partner = MModAdd(ROOT, partner, size);
          mpierr = MPI_Recv(buffer, COUNT, HPL_2_MPI_TYPE(DTYPE), partner, tag,
                            COMM, &status);
          OP(COUNT, buffer, BUFFER, DTYPE);
        }
        if (mpierr != MPI_SUCCESS) hplerr = mpierr;
      }
      mask ^= ip2;
      ip2 <<= 1;
      d--;
    } while (d);
  }
  if (buffer) free(buffer);

  return (hplerr);
}
