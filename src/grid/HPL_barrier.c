#include "hpl.h"

int HPL_barrier(MPI_Comm COMM) {
  int i = 0;
  return (HPL_broadcast((void*)(&i), 1, HPL_INT, 0, COMM));
}
