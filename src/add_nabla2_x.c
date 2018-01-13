#include <stdio.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"


//XXX This should be called only by master process 


// probably nabla2 should be global ?

void add_nabla2_x( int Nx, int Ny, int Nz, double *D2jl_x, Mat* nabla2 )
{
  int *colGbl;
  int *colGbl_orig;
  int ix, irow;
  PetscErrorCode ierr;
  PetscInt rowGbl;

  colGbl = (int*)malloc( Nx*sizeof(int) );
  colGbl_orig = (int*)malloc( Nx*sizeof(int) );

  // Initialize pattern for column indices
  colGbl_orig[0] = 1;
  colGbl[0] = 1;
  for(ix = 2; ix <= Nx; ix++) {
    colGbl_orig[ix-1] = colGbl_orig[0] + Ny*Nz*(ix-1);
    colGbl[ix-1] = colGbl_orig[ix-1];
  }
  
  int i;
  for( ix = 1; ix <= Nx; ix++ ) {
    for( irow = 1; irow <= Ny*Nz; irow++ ) {
      // shift colGbl according to irow
      for( i = 0; i < Nx; i++ ) {
        colGbl[i] = colGbl_orig[i] + irow - 2;
      }
      rowGbl = irow + (ix-1)*Ny*Nz - 1;
      //
      ierr = MatSetValues( *nabla2, 1, &rowGbl, Nx, colGbl, &D2jl_x[IDX2F(1,ix,Nx)], ADD_VALUES );
      if(ierr){
        printf("Error in calling MatSetValues\n");
      }
    }
  }
  

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


