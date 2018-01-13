#include <stdio.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"


//XXX This should be called only by master process 

void add_nabla2_y( int Nx, int Ny, int Nz, double *D2jl_y, Mat* nabla2 )
{
  PetscInt ii, ix, iz, i;
  
  PetscInt* colGbl;
  PetscInt* colGbl_orig;
  
  PetscInt rowGbl, rowLoc;

  PetscErrorCode ierr;

  colGbl = malloc( Ny*sizeof(PetscInt) );
  colGbl_orig = malloc( Ny*sizeof(PetscInt) );

  colGbl_orig[0] = 1;
  colGbl[0] = 1;
  for( ii = 2; ii <= Ny; ii++ ) {
    colGbl_orig[ii-1] = colGbl_orig[ii-2] + Nz;
  }

  rowGbl = -1;
  for( ix = 1; ix <= Nx; ix++ ) {
    for( rowLoc = 1; rowLoc <= Ny; rowLoc++ ) {
      for( iz = 1; iz <= Nz; iz++ ) {
        rowGbl = rowGbl + 1;
        for( i = 0; i < Ny; i++ ) {
          colGbl[i] = colGbl_orig[i] + iz - 1 + (ix-1)*Ny*Nz - 1;
        }
        ierr = MatSetValues( *nabla2, 1, &rowGbl, Ny, colGbl, &D2jl_y[IDX2F(1,rowLoc,Ny)], ADD_VALUES );
        if(ierr){
          printf("Error in calling MatSetValues in add_nabla2_y\n");
        }
      }
    }
  }

  free(colGbl); colGbl = NULL;
  free(colGbl_orig); colGbl_orig = NULL;

}

