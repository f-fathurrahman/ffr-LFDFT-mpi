!
! A subroutine to generate of G-vectors
! Not using minimal isotropic representation
!
SUBROUTINE init_gvec( Npoints, NN, LL, G2, Gv )
  IMPLICIT NONE
  !
  INTEGER :: Npoints, NN(3)
  REAL(8) :: LL(3)
  REAL(8) :: G2(Npoints)
  REAL(8) :: Gv(3,Npoints)
  !
  INTEGER :: i, j, k, ig, ii, jj, kk
	!
  REAL(8), PARAMETER :: PI = 4.d0*atan(1.d0)
  ! Function
  INTEGER :: mm_to_nn
  
  ig = 0
  DO k = 0, NN(3)-1
  DO j = 0, NN(2)-1
  DO i = 0, NN(1)-1
    !
    ig = ig + 1
    !
    ii = mm_to_nn( i, NN(1) )
    jj = mm_to_nn( j, NN(2) )
    kk = mm_to_nn( k, NN(3) )
    !
    Gv(1,ig) = ii * 2.d0*PI/LL(1)
    Gv(2,ig) = jj * 2.d0*PI/LL(2)
    Gv(3,ig) = kk * 2.d0*PI/LL(3)
    !
    G2(ig) = Gv(1,ig)**2 + Gv(2,ig)**2 + Gv(3,ig)**2
  ENDDO
  ENDDO
  ENDDO

END SUBROUTINE


