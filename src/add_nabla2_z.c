#include <stdio.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"


//XXX This should be called only by master process 

void add_nabla2_z( int Nx, int Ny, int Nz, double *D2jl_z, Mat* nabla2 )
{
  PetscInt irow, ii, i;

  PetscInt* colGbl;
  PetscInt* colGbl_orig;

  PetscInt rowGbl, rowLoc;
  
  PetscErrorCode ierr;

  colGbl = malloc( Nz*sizeof(PetscInt) );
  colGbl_orig = malloc( Nz*sizeof(PetscInt) );

  for( ii = 1; ii <= Nz; ii++ ) {
    colGbl[ii-1] = ii;
    colGbl_orig[ii-1] = ii;
  }

  rowGbl = -1;
  for( irow = 1; irow <= Nx*Ny; irow++ ) {
    for( rowLoc = 1; rowLoc <= Nz; rowLoc++ ) {
      rowGbl = rowGbl + 1;
      for( i = 0; i < Nz; i++ ) {
        colGbl[i] = colGbl_orig[i] + (irow-1)*Nz - 1;
      }
      ierr = MatSetValues( *nabla2, 1, &rowGbl, Nz, colGbl, &D2jl_z[IDX2F(1,rowLoc,Nz)], ADD_VALUES );
      if(ierr){
        printf("Error in calling MatSetValues in add_nabla2_z\n");
      }
    }
  }

  free(colGbl); colGbl = NULL;
  free(colGbl_orig); colGbl_orig = NULL;

  PetscPrintf(PETSC_COMM_WORLD, "\nFinished calling add_nabla2_z\n");

}
