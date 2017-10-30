#include "hpl.h"
 
/* 
 * Purpose
 * =======
 *
 * HPL_timer_walltime returns the elapsed (wall-clock) time.
 * 
 *
 * ---------------------------------------------------------------------
 */ 

#include <sys/time.h>
#include <sys/resource.h>

double HPL_timer_walltime( void )
{
   struct timeval             tp;
   static long                start=0, startu;

   if( !start )
   {
      (void) gettimeofday( &tp, NULL );
      start  = tp.tv_sec;
      startu = tp.tv_usec;
      return( HPL_rzero );
   }
   (void) gettimeofday( &tp, NULL );

   return( (double)( tp.tv_sec - start ) +
           ( (double)( tp.tv_usec-startu ) / 1000000.0 ) );
}                                                                               
