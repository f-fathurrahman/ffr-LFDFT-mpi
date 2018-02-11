#include <math.h>
#include <petsc.h>

#include "common.h"
#include "m_mpi.h"

void init_nabla2_sparse( int Nx, int Ny, int Nz,
                         double* D2jl_x, double* D2jl_y, double* D2jl_z,
                         Mat* nabla2 ) 
{
  
  int Npoints = Nx*Ny*Nz;
  int nnzc = Nx + Ny + Nz - 2;
  int NNZ = nnzc*Npoints;

  int* rowGbl_x_orig;
  int* rowGbl_y_orig;
  int* rowGbl_z_orig;
  int* rowGbl_x;
  int* rowGbl_y;
  int* rowGbl_z;

  rowGbl_x_orig = malloc( Nx*sizeof(int) ); 
  rowGbl_y_orig = malloc( Ny*sizeof(int) );
  rowGbl_z_orig = malloc( Nz*sizeof(int) );

  rowGbl_x = malloc( Nx*sizeof(int) ); 
  rowGbl_y = malloc( Ny*sizeof(int) );
  rowGbl_z = malloc( Nz*sizeof(int) );

  int ix, iy, iz;
  //
  rowGbl_x_orig[0] = 1;
  for( ix = 1; ix < Nx; ix++ ) {
    rowGbl_x_orig[ix] = rowGbl_x_orig[ix-1] + Ny*Nz;
  }
  //
  rowGbl_y_orig[0] = 1;
  for( iy = 1; iy < Ny; iy++ ) {
    rowGbl_y_orig[iy] = rowGbl_y_orig[iy-1] + Nz;
  }
  //
  for( iz = 1; iz <= Nz; iz++ ) {
    rowGbl_z_orig[iz] = iz;
  }

  
  int colLoc_x, colLoc_y, colLoc_z;
  int izz, yy;
  int colGbl, colGblm1;
  PetscErrorCode ierr;

  for( colGbl = 1; colGbl <= Npoints; colGbl++ ) {

    colLoc_x = ceil( ((double)colGbl)/(Ny*Nz) );
    //
    yy = colGbl - (colLoc_x - 1)*Ny*Nz;
    colLoc_y = ceil( ((double)yy)/Nz );
    //
    izz = ceil( ((double)colGbl)/Nz );
    colLoc_z = colGbl - (izz-1)*Nz;

    // rowGbl_x uses 0-based indexing
    for( ix = 1; ix <= Nx; ix++ ) {
      rowGbl_x[ix-1] = rowGbl_x_orig[ix-1] + colGbl - 1 - (colLoc_x - 1)*Ny*Nz - 1;
    }
    colGblm1 = colGbl - 1;
    ierr = MatSetValues( *nabla2, 1, rowGbl_x, Nx, &colGblm1, &D2jl_x[IDX2F(1,colLoc_x,Nx)], ADD_VALUES );
    if( ierr ) {
      printf("Error calling MatSetValues\n");
      exit(1);
    }

  }


}
