#include "hpl.h"

void HPL_warn(FILE* STREAM, int LINE, const char* SRNAME, const char* FORM,
              ...) {
  /*
   * Purpose
   * =======
   *
   * HPL_warn displays an error message.
   *
   *
   * Arguments
   * =========
   *
   * STREAM  (local input)                 FILE *
   *         On entry, STREAM specifies the output stream.
   *
   * LINE    (local input)                 int
   *         On entry,  LINE  specifies the line  number in the file where
   *         the  error  has  occured.  When  LINE  is not a positive line
   *         number, it is ignored.
   *
   * SRNAME  (local input)                 const char *
   *         On entry, SRNAME  should  be the name of the routine  calling
   *         this error handler.
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
  char cline[128];
  va_start(argptr, FORM);
  (void)vsprintf(cline, FORM, argptr);
  va_end(argptr);
  if (LINE <= 0)
    HPL_fprintf(STREAM, "%s %s:\n>>> %s <<<\n\n", "HPL ERROR in function",
                SRNAME, cline);
  else
    HPL_fprintf(STREAM, "%s %d %s %s:\n>>> %s <<<\n\n", "HPL ERROR on line",
                LINE, "of function", SRNAME, cline);
}
