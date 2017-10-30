#include "hpl.h"

#ifdef HPL_NO_MPI_DATATYPE /* The user insists to not use MPI types */
#ifndef HPL_COPY_L         /* and also want to avoid the copy of L ... */
#define HPL_COPY_L         /* well, sorry, can not do that: force the copy */
#endif
#endif

int HPL_binit_2ring(HPL_T_panel *PANEL) {
#ifdef HPL_USE_MPI_DATATYPE
  int ierr;
#endif
  if (PANEL == NULL) {
    return (HPL_SUCCESS);
  }
  if (PANEL->grid->npcol <= 1) {
    return (HPL_SUCCESS);
  }
#ifdef HPL_USE_MPI_DATATYPE
#ifdef HPL_COPY_L
  /*
   * Copy the panel into a contiguous buffer
   */
  HPL_copyL(PANEL);
#endif
  /*
   * Create the MPI user-defined data type
   */
  ierr = HPL_packL(PANEL, 0, PANEL->len, 0);

  return ((ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE));
#else
  /*
   * Force the copy of the panel into a contiguous buffer
   */
  HPL_copyL(PANEL);

  return (HPL_SUCCESS);
#endif
}

#ifdef HPL_USE_MPI_DATATYPE

#define _M_BUFF PANEL->buffers[0]
#define _M_COUNT PANEL->counts[0]
#define _M_TYPE PANEL->dtypes[0]

#else

#define _M_BUFF (void *)(PANEL->L2)
#define _M_COUNT PANEL->len
#define _M_TYPE MPI_DOUBLE

#endif

int HPL_bcast_2ring(HPL_T_panel *PANEL, int *IFLAG) {
  MPI_Comm comm;
  int ierr, go, next, msgid, partner, rank, roo2, root, size;
  if (PANEL == NULL) {
    *IFLAG = HPL_SUCCESS;
    return (HPL_SUCCESS);
  }
  if ((size = PANEL->grid->npcol) <= 1) {
    *IFLAG = HPL_SUCCESS;
    return (HPL_SUCCESS);
  }
  /*
   * Cast phase: root process  send to its right neighbor and mid-process.
   * If I am not the root process,  probe for message.   If the message is
   * there,  then receive it,  and  if I am not the last process  of  both
   * rings, then forward it to the next. Otherwise, inform the caller that
   * the panel has still not been received.
   */
  rank = PANEL->grid->mycol;
  comm = PANEL->grid->row_comm;
  root = PANEL->pcol;
  msgid = PANEL->msgid;
  next = MModAdd1(rank, size);
  roo2 = ((size + 1) >> 1);
  roo2 = MModAdd(root, roo2, size);

  if (rank == root) {
    ierr = MPI_Send(_M_BUFF, _M_COUNT, _M_TYPE, next, msgid, comm);
    if ((ierr == MPI_SUCCESS) && (size > 2)) {
      ierr = MPI_Send(_M_BUFF, _M_COUNT, _M_TYPE, roo2, msgid, comm);
    }
  } else {
    partner = MModSub1(rank, size);
    if ((partner == root) || (rank == roo2)) partner = root;

    ierr = MPI_Iprobe(partner, msgid, comm, &go, &PANEL->status[0]);

    if (ierr == MPI_SUCCESS) {
      if (go != 0) {
        ierr = MPI_Recv(_M_BUFF, _M_COUNT, _M_TYPE, partner, msgid, comm,
                        &PANEL->status[0]);
        if ((ierr == MPI_SUCCESS) && (next != roo2) && (next != root)) {
          ierr = MPI_Send(_M_BUFF, _M_COUNT, _M_TYPE, next, msgid, comm);
        }
      } else {
        *IFLAG = HPL_KEEP_TESTING;
        return (*IFLAG);
      }
    }
  }
  /*
   * If the message was received and being forwarded,  return HPL_SUCCESS.
   * If an error occured in an MPI call, return HPL_FAILURE.
   */
  *IFLAG = (ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE);

  return (*IFLAG);
}

int HPL_bwait_2ring(HPL_T_panel *PANEL) {
#ifdef HPL_USE_MPI_DATATYPE
  int ierr;
#endif
  if (PANEL == NULL) {
    return (HPL_SUCCESS);
  }
  if (PANEL->grid->npcol <= 1) {
    return (HPL_SUCCESS);
  }
/*
 * Release the arrays of request / status / data-types and buffers
 */
#ifdef HPL_USE_MPI_DATATYPE
  ierr = MPI_Type_free(&PANEL->dtypes[0]);

  return ((ierr == MPI_SUCCESS ? HPL_SUCCESS : HPL_FAILURE));
#else
  return (HPL_SUCCESS);
#endif
}
