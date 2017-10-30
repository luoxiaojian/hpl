#include "hpl.h"

void HPL_copyL(HPL_T_panel* PANEL) {
  /*
   * Purpose
   * =======
   *
   * HPL_copyL copies  the  panel of columns, the L1 replicated submatrix,
   * the pivot array  and  the info scalar into a contiguous workspace for
   * later broadcast.
   *
   * The copy of this panel  into  a contiguous buffer  can be enforced by
   * specifying -DHPL_COPY_L in the architecture specific Makefile.
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
  int jb, lda;
  if (PANEL->grid->mycol == PANEL->pcol) {
    jb = PANEL->jb;
    lda = PANEL->lda;

    if (PANEL->grid->myrow == PANEL->prow) {
      HPL_dlacpy(PANEL->mp - jb, jb, Mptr(PANEL->A, jb, -jb, lda), lda,
                 PANEL->L2, PANEL->ldl2);
    } else {
      HPL_dlacpy(PANEL->mp, jb, Mptr(PANEL->A, 0, -jb, lda), lda, PANEL->L2,
                 PANEL->ldl2);
    }
  }
}
