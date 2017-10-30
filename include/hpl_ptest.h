#ifndef HPL_PTEST_H
#define HPL_PTEST_H
/*
 * ---------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------
 */
#include "hpl_misc.h"
#include "hpl_blas.h"
#include "hpl_auxil.h"
#include "hpl_gesv.h"

#include "hpl_pmisc.h"
#include "hpl_pauxil.h"
#include "hpl_panel.h"
#include "hpl_pgesv.h"

#include "hpl_ptimer.h"
#include "hpl_pmatgen.h"
/*
 * ---------------------------------------------------------------------
 * Data Structures
 * ---------------------------------------------------------------------
 */
typedef struct HPL_S_test
{
   double              epsil;                      /* epsilon machine */
   double              thrsh;                            /* threshold */
   FILE *              outfp;       /* output stream (only in proc 0) */
   int                 kfail;                    /* # of tests failed */
   int                 kpass;                    /* # of tests passed */
   int                 kskip;                   /* # of tests skipped */
   int                 ktest;                /* total number of tests */
} HPL_T_test;

/*
 * ---------------------------------------------------------------------
 * #define macro constants for testing only
 * ---------------------------------------------------------------------
 */
#define    HPL_LINE_MAX         256
#define    HPL_MAX_PARAM         20
#define    HPL_ISEED            100
/*
 * ---------------------------------------------------------------------
 * global timers for timing analysis only
 * ---------------------------------------------------------------------
 */
#ifdef HPL_DETAILED_TIMING
#define    HPL_TIMING_BEG        11 /* timer 0 reserved, used by main */
#define    HPL_TIMING_N           6 /* number of timers defined below */
#define    HPL_TIMING_RPFACT     11 /* starting from here, contiguous */
#define    HPL_TIMING_PFACT      12
#define    HPL_TIMING_MXSWP      13
#define    HPL_TIMING_UPDATE     14
#define    HPL_TIMING_LASWP      15
#define    HPL_TIMING_PTRSV      16
#endif
/*
 * ---------------------------------------------------------------------
 * Function prototypes
 * ---------------------------------------------------------------------
 */
void                             HPL_pdinfo
STDC_ARGS( (
   HPL_T_test *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_ORDER *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_FACT *,
   int *,
   int *,
   int *,
   int *,
   int *,
   HPL_T_FACT *,
   int *,
   HPL_T_TOP *,
   int *,
   int *,
   HPL_T_SWAP *,
   int *,
   int *,
   int *,
   int *,
   int *
) );
void                             HPL_pdtest
STDC_ARGS( (
   HPL_T_test *,
   HPL_T_grid *,
   HPL_T_palg *,
   const int,
   const int
) );

#endif
