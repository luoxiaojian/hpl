#ifndef HPL_GRID_H
#define HPL_GRID_H
/*
 * ---------------------------------------------------------------------
 * Include files
 * ---------------------------------------------------------------------
 */
#include "hpl_pmisc.h"
/*
 * ---------------------------------------------------------------------
 * #typedefs and data structures
 * ---------------------------------------------------------------------
 */
typedef enum { HPL_INT = 100, HPL_DOUBLE = 101 } HPL_T_TYPE;

typedef enum { HPL_ROW_MAJOR = 201, HPL_COLUMN_MAJOR = 202 } HPL_T_ORDER;

typedef struct HPL_S_grid {
  MPI_Comm all_comm; /* grid communicator */
  MPI_Comm row_comm; /* row communicator */
  MPI_Comm col_comm; /* column communicator */
  HPL_T_ORDER order; /* ordering of the procs in the grid */
  int iam;           /* my rank in the grid */
  int myrow;         /* my row number in the grid */
  int mycol;         /* my column number in the grid */
  int nprow;         /* the total # of rows in the grid */
  int npcol;         /* the total # of columns in the grid */
  int nprocs;        /* the total # of procs in the grid */
  int row_ip2;       /* largest power of two <= nprow */
  int row_hdim;      /* row_ip2 procs hypercube dimension */
  int row_ip2m1;     /* largest power of two <= nprow-1 */
  int row_mask;      /* row_ip2m1 procs hypercube mask */
  int col_ip2;       /* largest power of two <= npcol */
  int col_hdim;      /* col_ip2 procs hypercube dimension */
  int col_ip2m1;     /* largest power of two <= npcol-1 */
  int col_mask;      /* col_ip2m1 procs hypercube mask */
} HPL_T_grid;

/*
 * ---------------------------------------------------------------------
 * Data Structures
 * ---------------------------------------------------------------------
 */
typedef void (*HPL_T_OP)(const int, const void *, void *, const HPL_T_TYPE);
/*
 * ---------------------------------------------------------------------
 * #define macros definitions
 * ---------------------------------------------------------------------
 */
#define HPL_2_MPI_TYPE(typ) ((typ == HPL_INT ? MPI_INT : MPI_DOUBLE))
/*
 * The following macros perform common modulo operations;  All functions
 * except MPosMod assume arguments are < d (i.e., arguments are themsel-
 * ves within modulo range).
 */
/* increment with mod */
#define MModInc(I, d) \
  if (++(I) == (d)) (I) = 0
/* decrement with mod */
#define MModDec(I, d) \
  if (--(I) == -1) (I) = (d)-1
/* positive modulo */
#define MPosMod(I, d) ((I) - ((I) / (d)) * (d))
/* add two numbers */
#define MModAdd(I1, I2, d) \
  (((I1) + (I2) < (d)) ? (I1) + (I2) : (I1) + (I2) - (d))
/* add 1 to # */
#define MModAdd1(I, d) (((I) != (d)-1) ? (I) + 1 : 0)
/* subtract two numbers */
#define MModSub(I1, I2, d) (((I1) < (I2)) ? (d) + (I1) - (I2) : (I1) - (I2))
/* sub 1 from # */
#define MModSub1(I, d) (((I) != 0) ? (I)-1 : (d)-1)
/*
 * ---------------------------------------------------------------------
 * grid function prototypes
 * ---------------------------------------------------------------------
 */
int HPL_grid_init STDC_ARGS((MPI_Comm, const HPL_T_ORDER, const int, const int,
                             HPL_T_grid *));
int HPL_grid_exit STDC_ARGS((HPL_T_grid *));

int HPL_grid_info STDC_ARGS((const HPL_T_grid *, int *, int *, int *, int *));
int HPL_pnum STDC_ARGS((const HPL_T_grid *, const int, const int));
#endif
