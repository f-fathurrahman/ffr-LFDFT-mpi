#include <stdlib.h>
#include <petsc.h>

#include "c_m_mpi.h"

void petsc_start_()
{
  PetscErrorCode ierr;
  //ierr = PetscInitialize( (char*)0, (char*)0, (char*)0, (char*)0 );
  ierr = PetscInitialize( NULL, NULL, NULL, NULL );

  if(ierr) {
    printf("Error when calling PetscInitialize\n");
    exit(1);
  }

  ierr = MPI_Comm_size( MPI_COMM_WORLD, &M_MPI_Nprocs );
  ierr = MPI_Comm_rank( MPI_COMM_WORLD, &M_MPI_my_rank );

}
