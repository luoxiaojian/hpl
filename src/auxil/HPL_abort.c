#include "hpl.h"

void HPL_abort(int LINE, const char* SRNAME, const char* FORM, ...) {
  va_list argptr;
  char cline[128];
  va_start(argptr, FORM);
  (void)vsprintf(cline, FORM, argptr);
  va_end(argptr);
  /*
   * Display an error message
   */
  if (LINE <= 0)
    HPL_fprintf(stderr, "%s %s:\n>>> %s <<< Abort ...\n\n",
                "HPL ERROR in function", SRNAME, cline);
  else
    HPL_fprintf(stderr, "%s %d %s %s:\n>>> %s <<< Abort ...\n\n",
                "HPL ERROR on line", LINE, "of function", SRNAME, cline);
  exit(0);
}
