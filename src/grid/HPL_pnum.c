#include "hpl.h"

int HPL_pnum(const HPL_T_grid* GRID, const int MYROW, const int MYCOL) {
  if (GRID->order == HPL_ROW_MAJOR)
    return (MYROW * GRID->npcol + MYCOL);
  else
    return (MYCOL * GRID->nprow + MYROW);
}
