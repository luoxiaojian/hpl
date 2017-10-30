#ifndef HPL_MISC_H
#define HPL_MISC_H
/*
 * ---------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdarg.h>
#define STDC_ARGS(p) p

#ifdef HPL_CALL_VSIPL
#include <vsip.h>
#endif
/*
 * ---------------------------------------------------------------------
 * #define macro constants
 * ---------------------------------------------------------------------
 */
#define HPL_rone 1.0
#define HPL_rtwo 2.0
#define HPL_rzero 0.0
/*
 * ---------------------------------------------------------------------
 * #define macros definitions
 * ---------------------------------------------------------------------
 */
#define Mabs(a_) (((a_) < 0) ? -(a_) : (a_))
#define Mmin(a_, b_) (((a_) < (b_)) ? (a_) : (b_))
#define Mmax(a_, b_) (((a_) > (b_)) ? (a_) : (b_))

#define Mfloor(a, b) (((a) > 0) ? (((a) / (b))) : (-(((-(a)) + (b)-1) / (b))))
#define Mceil(a, b) (((a) + (b)-1) / (b))
#define Miceil(a, b) (((a) > 0) ? ((((a) + (b)-1) / (b))) : (-((-(a)) / (b))))

#define Mupcase(C) (((C) > 96 && (C) < 123) ? (C)&0xDF : (C))
#define Mlowcase(C) (((C) > 64 && (C) < 91) ? (C) | 32 : (C))
/*
 * Mptr returns a pointer to a_( i_, j_ ) for readability reasons and
 * also less silly errors ...
 */
#define Mptr(a_, i_, j_, lda_) \
  ((a_) + (size_t)(i_) + (size_t)(j_) * (size_t)(lda_))
/*
 * Align pointer
 */
#define HPL_PTR(ptr_, al_) ((((size_t)(ptr_) + (al_)-1) / (al_)) * (al_))
#endif
/*
 * End of hpl_misc.h
 */
