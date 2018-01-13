#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void init_LF3d_p( LF3d_T* LF3d, int NN[3], double AA[3], double BB[3] )
{
  int i, j, k;
  int ip;

  for( i = 0; i < 3; i++ ) {
    LF3d->NN[i] = NN[i];
    LF3d->AA[i] = AA[i];
    LF3d->BB[i] = BB[i];
    LF3d->LL[i] = BB[i] - AA[i];
    LF3d->hh[i] = (BB[i] - AA[i])/NN[i];
  }

  // Total number of points (equal to total number of basis set)
  LF3d->Npoints = NN[0]*NN[1]*NN[2];
  
  // element volume
  LF3d->dVol = LF3d->hh[0] * LF3d->hh[1] * LF3d->hh[2];

  // some shortcuts
  int Nx = NN[0];
  int Ny = NN[1];
  int Nz = NN[2];
  //
  double Lx = LF3d->LL[0];
  double Ly = LF3d->LL[1];
  double Lz = LF3d->LL[2];

  LF3d->grid_x = malloc( Nx*sizeof(double) );
  LF3d->grid_y = malloc( Ny*sizeof(double) );
  LF3d->grid_z = malloc( Nz*sizeof(double) );

  init_grid_1d_p_( &Nx, &(LF3d->AA[0]), &(LF3d->BB[0]), LF3d->grid_x );
  init_grid_1d_p_( &Ny, &(LF3d->AA[1]), &(LF3d->BB[1]), LF3d->grid_y );
  init_grid_1d_p_( &Nz, &(LF3d->AA[2]), &(LF3d->BB[2]), LF3d->grid_z );

  // shifts
  LF3d->grid_shift[0] = 0.5*( LF3d->grid_x[1] - LF3d->grid_x[0] );
  LF3d->grid_shift[1] = 0.5*( LF3d->grid_y[1] - LF3d->grid_y[0] );
  LF3d->grid_shift[2] = 0.5*( LF3d->grid_z[1] - LF3d->grid_z[0] );

  LF3d->D1jl_x = malloc( Nx*Nx*sizeof(double) );
  LF3d->D1jl_y = malloc( Ny*Ny*sizeof(double) );
  LF3d->D1jl_z = malloc( Nz*Nz*sizeof(double) );

  LF3d->D2jl_x = malloc( Nx*Nx*sizeof(double) );
  LF3d->D2jl_y = malloc( Ny*Ny*sizeof(double) );
  LF3d->D2jl_z = malloc( Nz*Nz*sizeof(double) );

  init_deriv_matrix_p_( &Nx, &Lx, LF3d->D1jl_x, LF3d->D2jl_x );
  init_deriv_matrix_p_( &Ny, &Ly, LF3d->D1jl_y, LF3d->D2jl_y );
  init_deriv_matrix_p_( &Nz, &Lz, LF3d->D1jl_z, LF3d->D2jl_z );

  LF3d->lingrid = malloc( 3*Nx*Ny*Nz*sizeof(double) );
  LF3d->xyz2lin = malloc( Nx*Ny*Nz*sizeof(double) );
  LF3d->lin2xyz = malloc( 3*Nx*Ny*Nz*sizeof(double) );
  ip = 0;

  for( k = 1; k <= Nz; k++ ) {
    for( j = 1; j <= Ny; j++ ) {
      for( i = 1; i <= Nx; i++) {
        ip = ip + 1;
        LF3d->lingrid[IDX2F(1,ip,3)] = LF3d->grid_x[i-1];
        LF3d->lingrid[IDX2F(2,ip,3)] = LF3d->grid_y[j-1];
        LF3d->lingrid[IDX2F(3,ip,3)] = LF3d->grid_z[k-1];
        //
        LF3d->xyz2lin[IDX3F(i,j,k,Nx,Ny)] = ip;
        LF3d->lin2xyz[IDX2F(1,ip,3)] = i;
        LF3d->lin2xyz[IDX2F(2,ip,3)] = j;
        LF3d->lin2xyz[IDX2F(3,ip,3)] = k;
      }
    }
  }

  // G-vectors
  LF3d->Gv = malloc( 3*Nx*Ny*Nz*sizeof(double) );
  LF3d->G2 = malloc( Nx*Ny*Nz*sizeof(double) );

  init_gvec_( &(LF3d->Npoints), NN, LF3d->LL, LF3d->G2, LF3d->Gv );

}

