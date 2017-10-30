#include "hpl.h"

/*
 * Purpose
 * =======
 *
 * HPL_ptimer_walltime returns the elapsed (wall-clock) time.
 *
 *
 * ---------------------------------------------------------------------
 */

#if defined(HPL_USE_GETTIMEOFDAY)

#include <sys/resource.h>
#include <sys/time.h>

double HPL_ptimer_walltime(void) {
  struct timeval tp;
  static long start = 0, startu;

  if (!start) {
    (void)gettimeofday(&tp, NULL);
    start = tp.tv_sec;
    startu = tp.tv_usec;
    return (HPL_rzero);
  }
  (void)gettimeofday(&tp, NULL);

  return ((double)(tp.tv_sec - start) +
          ((double)(tp.tv_usec - startu) / 1000000.0));
}

#else

double HPL_ptimer_walltime(void) { return (MPI_Wtime()); }

#endif
