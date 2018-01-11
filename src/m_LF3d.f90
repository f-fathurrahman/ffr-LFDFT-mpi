MODULE m_LF3d

  IMPLICIT NONE 

  INTEGER, PARAMETER :: LF3d_PERIODIC = 1
  INTEGER, PARAMETER :: LF3d_CLUSTER  = 2
  INTEGER, PARAMETER :: LF3d_SINC     = 3

  INTEGER :: LF3d_TYPE

  INTEGER :: LF3d_NN(3)
  REAL(8) :: LF3d_LL(3)
  REAL(8) :: LF3d_AA(3), LF3d_BB(3)
  REAL(8) :: LF3d_hh(3)

  INTEGER :: LF3d_Npoints
  REAL(8) :: LF3d_dVol
 
  REAL(8), ALLOCATABLE :: LF3d_grid_x(:)
  REAL(8), ALLOCATABLE :: LF3d_grid_y(:)
  REAL(8), ALLOCATABLE :: LF3d_grid_z(:)

  REAL(8) :: LF3d_GRID_SHIFT(3) ! shifts, periodic, to match FFT grid

  REAL(8), ALLOCATABLE :: LF3d_D1jl_x(:,:)
  REAL(8), ALLOCATABLE :: LF3d_D1jl_y(:,:)
  REAL(8), ALLOCATABLE :: LF3d_D1jl_z(:,:)

  REAL(8), ALLOCATABLE :: LF3d_D2jl_x(:,:)
  REAL(8), ALLOCATABLE :: LF3d_D2jl_y(:,:)
  REAL(8), ALLOCATABLE :: LF3d_D2jl_z(:,:)

  REAL(8), ALLOCATABLE :: LF3d_lingrid(:,:)
  INTEGER, ALLOCATABLE :: LF3d_xyz2lin(:,:,:)
  INTEGER, ALLOCATABLE :: LF3d_lin2xyz(:,:)

  REAL(8), ALLOCATABLE :: LF3d_G2(:)
  REAL(8), ALLOCATABLE :: LF3d_Gv(:,:)

END MODULE

