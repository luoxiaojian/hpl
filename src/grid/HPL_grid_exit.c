#include "hpl.h"

int HPL_grid_exit(HPL_T_grid* GRID) {
  int hplerr = MPI_SUCCESS, mpierr;
  if (GRID->all_comm != MPI_COMM_NULL) {
    mpierr = MPI_Comm_free(&(GRID->row_comm));
    if (mpierr != MPI_SUCCESS) hplerr = mpierr;
    mpierr = MPI_Comm_free(&(GRID->col_comm));
    if (mpierr != MPI_SUCCESS) hplerr = mpierr;
    mpierr = MPI_Comm_free(&(GRID->all_comm));
    if (mpierr != MPI_SUCCESS) hplerr = mpierr;
  }

  GRID->order = HPL_COLUMN_MAJOR;

  GRID->iam = GRID->myrow = GRID->mycol = -1;
  GRID->nprow = GRID->npcol = GRID->nprocs = -1;

  GRID->row_ip2 = GRID->row_hdim = GRID->row_ip2m1 = GRID->row_mask = -1;
  GRID->col_ip2 = GRID->col_hdim = GRID->col_ip2m1 = GRID->col_mask = -1;

  return (hplerr);
}
