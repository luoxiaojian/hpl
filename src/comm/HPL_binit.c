#include "hpl.h"

int HPL_binit(HPL_T_panel* PANEL) {
  /*
   * Purpose
   * =======
   *
   * HPL_binit initializes  a  row  broadcast.  Successful  completion  is
   * indicated by the returned error code HPL_SUCCESS.
   *
   * Arguments
   * =========
   *
   * PANEL   (input/output)                HPL_T_panel *
   *         On entry,  PANEL  points to the  current panel data structure
   *         being broadcast.
   *
   * ---------------------------------------------------------------------
   */
  int ierr;
  HPL_T_TOP top;
  if (PANEL->grid->npcol <= 1) return (HPL_SUCCESS);
  /*
   * Retrieve the selected virtual broadcast topology
   */
  top = PANEL->algo->btopo;

  switch (top) {
    case HPL_1RING_M:
      ierr = HPL_binit_1rinM(PANEL);
      break;
    case HPL_1RING:
      ierr = HPL_binit_1ring(PANEL);
      break;
    case HPL_2RING_M:
      ierr = HPL_binit_2rinM(PANEL);
      break;
    case HPL_2RING:
      ierr = HPL_binit_2ring(PANEL);
      break;
    case HPL_BLONG_M:
      ierr = HPL_binit_blonM(PANEL);
      break;
    case HPL_BLONG:
      ierr = HPL_binit_blong(PANEL);
      break;
    default:
      ierr = HPL_SUCCESS;
  }

  return (ierr);
}
