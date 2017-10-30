#include "hpl.h"

int HPL_pdpanel_disp(HPL_T_panel** PANEL) {
  /*
   * Purpose
   * =======
   *
   * HPL_pdpanel_disp deallocates  the  panel  structure  and  resources  and
   * stores the error code returned by the panel factorization.
   *
   * Arguments
   * =========
   *
   * PANEL   (local input/output)          HPL_T_panel * *
   *         On entry,  PANEL  points  to  the  address  of the panel data
   *         structure to be deallocated.
   *
   * ---------------------------------------------------------------------
   */
  int mpierr;
  /*
   * Deallocate the panel resources and panel structure
   */
  mpierr = HPL_pdpanel_free(*PANEL);
  if (*PANEL) free(*PANEL);
  *PANEL = NULL;

  return (mpierr);
}
