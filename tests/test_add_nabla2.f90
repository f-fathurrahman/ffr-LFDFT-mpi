PROGRAM test_add_nabla2

  IMPLICIT NONE
  !
  INTEGER :: NN(3)
  REAL(8) :: hh(3)

  NN = (/ 63, 63, 63 /)
  hh = (/ 0.3d0, 0.3d0, 0.3d0 /)

  CALL init_LF3d_sinc( NN, hh )
  CALL info_LF3d()
  CALL dealloc_LF3d()

END PROGRAM 
