#include "hpl.h"

int HPL_all_reduce(void* BUFFER, const int COUNT, const HPL_T_TYPE DTYPE,
                   const HPL_T_OP OP, MPI_Comm COMM) {
  int hplerr;
  hplerr = HPL_reduce(BUFFER, COUNT, DTYPE, OP, 0, COMM);
  if (hplerr != MPI_SUCCESS) return (hplerr);
  return (HPL_broadcast(BUFFER, COUNT, DTYPE, 0, COMM));
}
