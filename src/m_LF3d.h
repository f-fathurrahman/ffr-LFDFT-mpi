#ifndef M_LF3D_H
#define M_LF3D_H


//const int LF3d_PERIODIC = 1;
//const int LF3d_CLUSTER  = 2;
//const int LF3d_SINC     = 3;

typedef struct {

  int type;
  int NN[3];
  double LL[3];
  double AA[3], BB[3];
  double hh[3];

  int Npoints;
  double dVol;
 
  double* grid_x;
  double* grid_y;
  double* grid_z;

  double grid_shift[3]; // shifts, periodic, to match FFT grid

  // interpreted as 2d-array
  double* D1jl_x;
  double* D1jl_y;
  double* D1jl_z;

  // interpreted as 2d-array
  double* D2jl_x;
  double* D2jl_y;
  double* D2jl_z;

  double *lingrid; // 2d array
  int* xyz2lin;
  int* lin2xyz;

  double* G2;
  double* Gv;

} LF3d_T;

#endif

