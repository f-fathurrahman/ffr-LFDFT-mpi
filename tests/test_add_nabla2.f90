PROGRAM test_add_nabla2
  
  USE m_LF3d, ONLY : D2jl_x => LF3d_D2jl_x

  IMPLICIT NONE
  !
  INTEGER :: NN(3)
  REAL(8) :: hh(3)

  CALL Petsc_Start()

  NN = (/ 3, 3, 3 /)
  hh = (/ 0.3d0, 0.3d0, 0.3d0 /)

  CALL init_LF3d_sinc( NN, hh )
  CALL info_LF3d()

  CALL add_nabla2_x( NN(1), NN(2), NN(3), D2jl_x )

  CALL dealloc_LF3d()

  CALL Petsc_Stop()

END PROGRAM 
