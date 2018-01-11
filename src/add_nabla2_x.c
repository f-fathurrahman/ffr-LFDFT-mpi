#include <stdio.h>
#include <petsc.h>

#include "c_common.h"
#include "c_m_mpi.h"

void add_nabla2_x_( int *Nx, int *Ny, int *Nz, double *D2jl_x )
{
  
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

}


