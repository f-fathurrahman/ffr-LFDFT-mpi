#include <stdio.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"


//XXX This should be called only by master process 


// probably nabla2 should be global ?

void add_nabla2_x_( int *Nx, int *Ny, int *Nz, double *D2jl_x, Mat* nabla2 )
{
  int *colGbl;
  int *colGbl_orig;
  int ix, irow;

  colGbl = (int*)malloc( (*Nx)*sizeof(int) );
  colGbl_orig = (int*)malloc( (*Nx)*sizeof(int) );

  // pattern for column indices
  colGbl_orig[0] = 1;
  

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


