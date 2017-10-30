#include "hpl.h"

int HPL_grid_info(const HPL_T_grid* GRID, int* NPROW, int* NPCOL, int* MYROW,
                  int* MYCOL) {
  /*
   * Purpose
   * =======
   *
   * HPL_grid_info returns  the grid shape and the coordinates in the grid
   * of the calling process.  Successful  completion  is  indicated by the
   * returned error code  MPI_SUCCESS. Other error codes depend on the MPI
   * implementation.
   *
   * Arguments
   * =========
   *
   * GRID    (local input)                 const HPL_T_grid *
   *         On entry,  GRID  points  to the data structure containing the
   *         process grid information.
   *
   * NPROW   (global output)               int *
   *         On exit,   NPROW  specifies the number of process rows in the
   *         grid. NPROW is at least one.
   *
   * NPCOL   (global output)               int *
   *         On exit,   NPCOL  specifies  the number of process columns in
   *         the grid. NPCOL is at least one.
   *
   * MYROW   (global output)               int *
   *         On exit,  MYROW  specifies my  row process  coordinate in the
   *         grid. MYROW is greater than or equal  to zero  and  less than
   *         NPROW.
   *
   * MYCOL   (global output)               int *
   *         On exit,  MYCOL specifies my column process coordinate in the
   *         grid. MYCOL is greater than or equal  to zero  and  less than
   *         NPCOL.
   *
   * ---------------------------------------------------------------------
   */
  *NPROW = GRID->nprow;
  *NPCOL = GRID->npcol;
  *MYROW = GRID->myrow;
  *MYCOL = GRID->mycol;
  return (MPI_SUCCESS);
}
