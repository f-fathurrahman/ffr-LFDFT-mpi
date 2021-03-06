#include <stdio.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"


//XXX This should be called only by master process 


// probably nabla2 should be global ?

void add_nabla2_x( int Nx, int Ny, int Nz, double* D2jl_x, Mat* nabla2 )
{
  PetscInt* colGbl;
  PetscInt* colGbl_orig;
  PetscInt ix, irow;
  PetscErrorCode ierr;
  PetscInt rowGbl;

  colGbl = malloc( Nx*sizeof(int) );
  colGbl_orig = malloc( Nx*sizeof(int) );

  // Initialize pattern for column indices
  colGbl_orig[0] = 1;
  colGbl[0] = 1;
  for(ix = 2; ix <= Nx; ix++) {
    colGbl_orig[ix-1] = colGbl_orig[0] + Ny*Nz*(ix-1);
    colGbl[ix-1] = colGbl_orig[ix-1];
  }
  
  int i;
  for( rowGbl = 0; rowGbl < Nx*Ny*Nz; rowGbl++ ) {
    for( ix = 1; ix <=Nx; ix++ ) {
      irow = rowGbl + 1 - (ix-1)*Ny*Nz;
      printf("rowGbl = %d, irow = %d\n", rowGbl, irow);
      //
      // shift colGbl according to irow
      for( i = 0; i < Nx; i++ ) {
        colGbl[i] = colGbl_orig[i] + irow - 2;
      }
      //rowGbl = irow + (ix-1)*Ny*Nz - 1;
      printf("add_nabla2_x: rowGbl = %d\n", rowGbl);
      //
      ierr = MatSetValues( *nabla2, 1, &rowGbl, Nx, colGbl, &D2jl_x[IDX2F(1,ix,Nx)], ADD_VALUES );
      if( ierr ) {
        printf("Error when calling MatSetValues\n");
        exit(1);
      }
    }
  }
  
  free(colGbl); colGbl = NULL;
  free(colGbl_orig); colGbl_orig = NULL;

  PetscPrintf(PETSC_COMM_WORLD, "\nFinished calling add_nabla2_x\n");

/* 
  if( M_MPI_my_rank == 0 ) {
    printf("Hello from add_nabla2_x\n");
    printf("Nx = %d\n", *Nx);
    printf("Ny = %d\n", *Ny);
    printf("Nz = %d\n", *Nz);
  }

  int i, j;
  int idx;

  if( M_MPI_my_rank == 0 ) {
    printf("%f\n", D2jl_x[0]);
    for( i = 1; i <= *Nx; i++ ){
      for( j = 1; j <= *Ny; j++) {
        idx = IDX2F(i,j,*Nx);
        printf("%18.10f  ", D2jl_x[idx]);
      }
      printf("\n");
    }
  }
*/

}


