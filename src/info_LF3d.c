
#include <stdio.h>
#include "common.h"

void info_LF3d( LF3d_T LF3d )
{
  printf("NN = %5d %5d %5d\n", LF3d.NN[0], LF3d.NN[1], LF3d.NN[2] );
  printf("AA = %18.10f %18.10f %18.10f\n", LF3d.AA[0], LF3d.AA[1], LF3d.AA[2] );
  printf("BB = %18.10f %18.10f %18.10f\n", LF3d.BB[0], LF3d.BB[1], LF3d.BB[2] );
  printf("LL = %18.10f %18.10f %18.10f\n", LF3d.LL[0], LF3d.LL[1], LF3d.LL[2] );
  printf("hh = %18.10f %18.10f %18.10f\n", LF3d.hh[0], LF3d.hh[1], LF3d.hh[2] );

  int Nx = LF3d.NN[0];
  int Ny = LF3d.NN[1];
  int Nz = LF3d.NN[2];

  int i;

  printf("\ngrid_x = \n");
  for(i = 0; i < Nx; i++ ) {
    printf("%5d  %18.10f\n", i+1, LF3d.grid_x[i]);
  }

  printf("\ngrid_y = \n");
  for(i = 0; i < Ny; i++ ) {
    printf("%5d  %18.10f\n", i+1, LF3d.grid_y[i]);
  }

  printf("\ngrid_z = \n");
  for(i = 0; i < Nz; i++ ) {
    printf("%5d  %18.10f\n", i+1, LF3d.grid_z[i]);
  }

  PrintMatrix( LF3d.D1jl_x, Nx, Nx );

}

