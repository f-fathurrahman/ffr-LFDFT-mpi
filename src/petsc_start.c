#include <stdlib.h>
#include <petsc.h>

#include "m_mpi.h"

// This function is supposed to be called from Fortran as a subroutine.
void petsc_start_()
{
  PetscErrorCode ierr;

  // XXX: PetscInitialize needs argc and argv, and I don't know how to get argv
  // XXX: properly from Fortran. Probably repeated call to getarg and building
  // XXX: argv as arrays will do.
  // XXX: For the moment, we shall use NULLs
  ierr = PetscInitialize( NULL, NULL, NULL, NULL );

  if(ierr) {
    printf("Error when calling PetscInitialize\n");
    exit(1);
  }

  ierr = MPI_Comm_size( MPI_COMM_WORLD, &M_MPI_Nprocs );
  ierr = MPI_Comm_rank( MPI_COMM_WORLD, &M_MPI_my_rank );
}


// This function is supposed to be called from C as usual.
void petsc_start(int argc, char **argv)
{
  PetscErrorCode ierr;

  ierr = PetscInitialize( &argc, &argv, NULL, NULL );

  if(ierr) {
    printf("Error when calling PetscInitialize\n");
    exit(1);
  }

  ierr = MPI_Comm_size( MPI_COMM_WORLD, &M_MPI_Nprocs );
  ierr = MPI_Comm_rank( MPI_COMM_WORLD, &M_MPI_my_rank );
}


