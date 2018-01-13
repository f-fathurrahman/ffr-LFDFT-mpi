
#include <stdio.h>
#include "common.h"

void info_LF3d( LF3d_T LF3d )
{
  printf("NN = %5d %5d %5d\n", LF3d.NN[0], LF3d.NN[1], LF3d.NN[2] );
  printf("AA = %18.10f %18.10f %18.10f\n", LF3d.AA[0], LF3d.AA[1], LF3d.AA[2] );
  printf("BB = %18.10f %18.10f %18.10f\n", LF3d.BB[0], LF3d.BB[1], LF3d.BB[2] );
  printf("LL = %18.10f %18.10f %18.10f\n", LF3d.LL[0], LF3d.LL[1], LF3d.LL[2] );
  printf("hh = %18.10f %18.10f %18.10f\n", LF3d.hh[0], LF3d.hh[1], LF3d.hh[2] );

  // shortcuts
  int Nx = LF3d.NN[0];
  int Ny = LF3d.NN[1];
  int Nz = LF3d.NN[2];
  int Npoints = Nx*Ny*Nz;

  int i;

  int is_small = Nx < 8 && Ny < 8 && Nz < 8;

  if( is_small ) {
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
    
    if( LF3d.D1jl_x != NULL ) {
      printf("\nMatrix D1jl_x\n");
      PrintMatrix( LF3d.D1jl_x, Nx, Nx );
    }

    if( LF3d.D1jl_y != NULL ) {
      printf("\nMatrix D1jl_y\n");
      PrintMatrix( LF3d.D1jl_y, Ny, Ny );
    }

    if( LF3d.D1jl_z != NULL ) {
      printf("\nMatrix D1jl_z\n");
      PrintMatrix( LF3d.D1jl_z, Nz, Nz );
    }

    printf("\nMatrix D2jl_x\n");
    PrintMatrix( LF3d.D2jl_x, Nx, Nx );

    printf("\nMatrix D2jl_y\n");
    PrintMatrix( LF3d.D2jl_y, Ny, Ny );

    printf("\nMatrix D2jl_z\n");
    PrintMatrix( LF3d.D2jl_z, Nz, Nz );
  }

  printf("\nSome grid points in x, y and z directions:\n");
  printf(" %8d%10.5f%8d%10.5f%8d%10.5f\n",
          1, LF3d.grid_x[0], 1, LF3d.grid_y[0], 1, LF3d.grid_z[0]);
  printf(" %8d%10.5f%8d%10.5f%8d%10.5f\n",
          2, LF3d.grid_x[1], 2, LF3d.grid_y[1], 2, LF3d.grid_z[1]);
  printf("       ..   .......      ..   .......      ..   .......\n");
  printf(" %8d%10.5f%8d%10.5f%8d%10.5f\n",
          Nx-1, LF3d.grid_x[Nx-2], Ny-1, LF3d.grid_y[Ny-2], Nz-1, LF3d.grid_z[Nz-2]);
  printf(" %8d%10.5f%8d%10.5f%8d%10.5f\n",
          Nx, LF3d.grid_x[Nx-1], Ny, LF3d.grid_y[Ny-1], Nz, LF3d.grid_z[Nz-1]);

  printf("\nSome G2 values\n");
  printf(" %10d%10.5f\n", 1, LF3d.G2[0]);
  printf(" %10d%10.5f\n", 2, LF3d.G2[1]);
  printf("        ...   .......\n");
  printf(" %10d%10.5f\n", 1, LF3d.G2[0]);
  printf(" %10d%10.5f\n", Npoints-1, LF3d.G2[Npoints-2]);
  printf(" %10d%10.5f\n", Npoints, LF3d.G2[Npoints-1]);

}

