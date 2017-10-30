#include "hpl.h"

void HPL_fprintf(FILE* STREAM, const char* FORM, ...) {
  /*
   * Purpose
   * =======
   *
   * HPL_fprintf is a wrapper around fprintf flushing the output stream.
   *
   *
   * Arguments
   * =========
   *
   * STREAM  (local input)                 FILE *
   *         On entry, STREAM specifies the output stream.
   *
   * FORM    (local input)                 const char *
   *         On entry, FORM specifies the format, i.e., how the subsequent
   *         arguments are converted for output.
   *
   *         (local input)                 ...
   *         On entry,  ...  is the list of arguments to be printed within
   *         the format string.
   *
   * ---------------------------------------------------------------------
   */
  va_list argptr;
  char cline[256];
  va_start(argptr, FORM);
  (void)vsprintf(cline, FORM, argptr);
  va_end(argptr);

  (void)fprintf(STREAM, "%s", cline);
  (void)fflush(STREAM);
}
