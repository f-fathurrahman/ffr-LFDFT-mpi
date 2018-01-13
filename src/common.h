#ifndef COMMON_H
#define COMMON_H

#include <petsc.h>
#include "m_LF3d.h"

#define IDX2F(i,j,DIM1) (((j)-1)*(DIM1) + ((i)-1))
#define IDX3F(i,j,k,DIM1,DIM2) (((k)-1)*(DIM1)*(DIM2) + ((j)-1)*(DIM1) + ((i)-1))
#define IDX4F(i,j,k,l,DIM1,DIM2,DIM3) (((l)-1)*(DIM1)*(DIM2)*(DIM3) + ((k)-1)*(DIM1)*(DIM2) + ((j)-1)*(DIM1) + ((i)-1))
#define IDX5F(i,j,k,l,m,DIM1,DIM2,DIM3,DIM4) (((m)-1)*(DIM1)*(DIM2)*(DIM3)*(DIM4) + ((l)-1)*(DIM1)*(DIM2)*(DIM3) + ((k)-1)*(DIM1)*(DIM2) + ((j)-1)*(DIM1) + ((i)-1))



void init_LF3d_p( LF3d_T* LF3d, int NN[3], double AA[3], double BB[3] );
void info_LF3d( LF3d_T LF3d );
void dealloc_LF3d(LF3d_T LF3d);

void petsc_start(int argc, char **argv);
void petsc_stop();
void add_nabla2_x( int Nx, int Ny, int Nz, double *D2jl_x, Mat* nabla2 );
void add_nabla2_y( int Nx, int Ny, int Nz, double *D2jl_y, Mat* nabla2 );
void add_nabla2_z( int Nx, int Ny, int Nz, double *D2jl_z, Mat* nabla2 );

//
// from F90
//
void init_deriv_matrix_p_( int *N, double* L, double* D1jl, double *D2jl );
void init_grid_1d_p_( int *N, double *A, double *B, double *grid_x );
void init_gvec_( int *Npoints, int *NN, double *LL, double *G2, double *Gv );


//
// Utilities
//
void PrintVector(double *V, int nelem);
void PrintMatrix(double *A, int NROW, int NCOL);

#endif

