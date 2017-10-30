#include "hpl.h"

/*
 * Purpose
 * =======
 *
 * HPL_ptimer_cputime returns the cpu time. If HPL_USE_CLOCK is defined,
 * the  clock() function is used to return an approximation of processor
 * time used by the program.  The value returned is the CPU time used so
 * far as a clock_t;  to get the number of seconds used,  the result  is
 * divided by  CLOCKS_PER_SEC.  This function is part of the  ANSI/ISO C
 * standard library.  If  HPL_USE_TIMES is defined, the times() function
 * is used instead.  This  function  returns  the current process times.
 * times() returns the number of clock ticks that have elapsed since the
 * system has been up.  Otherwise and by default,  the  standard library
 * function getrusage() is used.
 *
 * ---------------------------------------------------------------------
 */

#if defined(HPL_USE_CLOCK)

#include <time.h>

double HPL_ptimer_cputime(void) {
  static double cps = CLOCKS_PER_SEC;
  double d;
  clock_t t1;
  static clock_t t0 = 0;

  if (t0 == 0) t0 = clock();
  t1 = clock() - t0;
  d = (double)(t1) / cps;
  return (d);
}

#elif defined(HPL_USE_TIMES)

#include <sys/times.h>
#include <unistd.h>

double HPL_ptimer_cputime(void) {
  clock_t t1;
  struct tms ts;
  static double ClockTick = HPL_rzero;

  if (ClockTick == HPL_rzero) ClockTick = (double)(sysconf(_SC_CLK_TCK));
  (void)times(&ts);
  return ((double)(ts.tms_utime) / ClockTick);
}

/* #elif defined( HPL_USE_GETRUSAGE ) */
#else

#include <sys/resource.h>
#include <sys/time.h>

double HPL_ptimer_cputime(void) {
  struct rusage ruse;

  (void)getrusage(RUSAGE_SELF, &ruse);
  return ((double)(ruse.ru_utime.tv_sec) +
          ((double)(ruse.ru_utime.tv_usec) / 1000000.0));
}

/*
#else

double HPL_ptimer_cputime( void )
{
   return( HPL_PTIMER_ERROR );
}
*/

#endif
