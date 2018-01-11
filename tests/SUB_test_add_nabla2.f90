SUBROUTINE test_add_nabla2()

  USE m_LF3d, ONLY : D2jl_x => LF3d_D2jl_x
  
  IMPLICIT NONE
  
  INCLUDE 'mpif.h'
  
  ! Parameter for initializing LF3d
  INTEGER :: NN(3)
  REAL(8) :: hh(3)
  !
  INTEGER :: ierr
  INTEGER :: Nprocs, my_rank

  CALL MPI_Comm_size( MPI_COMM_WORLD, Nprocs, ierr )
  CALL MPI_Comm_rank( MPI_COMM_WORLD, my_rank, ierr )

  NN = (/ 3, 3, 3 /)
  hh = (/ 0.3d0, 0.3d0, 0.3d0 /)

  CALL init_LF3d_sinc( NN, hh )

  IF( my_rank == 0 ) THEN 
    CALL info_LF3d()
  ENDIF 

  CALL add_nabla2_x( NN(1), NN(2), NN(3), D2jl_x )

  CALL dealloc_LF3d()

END SUBROUTINE 

