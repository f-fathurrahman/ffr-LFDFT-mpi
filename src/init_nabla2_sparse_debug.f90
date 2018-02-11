!!>
!!> \section{Subroutine \texttt{init_nabla2_sparse()}}
!!>
!!> This subroutines initialize sparse Laplacian matrix elements in compressed sparse
!!> column format.
!!> There is code is derived by learning the structure of matrix which is quite regular
!!> compared to sparse matrices which are found in other application. Especially, the
!!> array sizes for CSR (or CSR, because the matrix is symmetric), namely:
!!> \texttt{nzval}, \texttt{rowval}, and \texttt{colptr} are known.
!!>

!!> DEBUG VERSION

SUBROUTINE init_nabla2_sparse_debug( Nx, Ny, Nz, D2jl_x, D2jl_y, D2jl_z )

  IMPLICIT NONE 
  
  INTEGER :: Nx, Ny, Nz
  REAL(8) :: D2jl_x(Nx,Nx)
  REAL(8) :: D2jl_y(Ny,Ny)
  REAL(8) :: D2jl_z(Nz,Nz)
  !
  REAL(8) :: nzval_ip
  INTEGER :: rowval_ip
  !
  INTEGER :: Npoints, nnzc, NNZ
  INTEGER, ALLOCATABLE :: rowGbl_x_orig(:), rowGbl_y_orig(:), rowGbl_z_orig(:)
  INTEGER :: ix, iy, iz, ip
  INTEGER :: yy, colLoc_x, colLoc_y, colLoc_z, izz
  INTEGER :: colGbl

  Npoints = Nx*Ny*Nz

!!> This is number of nonzeros per column.
!!>
  nnzc = Nx + Ny + Nz - 2

!!> This is total number of nonzeros.
!!>
  NNZ  = nnzc*Npoints

!!> Display some messages:
!!>
  WRITE(*,*)
  WRITE(*,*) 'Nx, Ny, Nz = ', Nx, Ny, Nz
  WRITE(*,*) 'Initializing nabla2_sparse'
  WRITE(*,'(1x,A,ES12.3,A)') 'Memory required for init_nabla2_sparse:', &
             ( NNZ*8d0 + (NNZ + Npoints + 1)*4.d0 )/1024.d0/1024.d0/1024.d0, &
             ' GB'
  flush(6)

!!>
!!> Initialize \texttt{rowGbl} pattern for x, y, and z components.
!!> For each \texttt{colGbl}, these arrays will vary according to some patterns.
!!>
  ALLOCATE( rowGbl_x_orig(Nx) )
  ALLOCATE( rowGbl_y_orig(Ny) )
  ALLOCATE( rowGbl_z_orig(Nz) )
  !
  rowGbl_x_orig(1) = 1
  DO ix = 2,Nx
    rowGbl_x_orig(ix) = rowGbl_x_orig(ix-1) + Ny*Nz
  ENDDO 
  !
  rowGbl_y_orig(1) = 1
  DO iy = 2,Ny
    rowGbl_y_orig(iy) = rowGbl_y_orig(iy-1) + Nz
  ENDDO 
  !
  DO iz = 1,Nz
    rowGbl_z_orig(iz) = iz
  ENDDO 

!!> Initialize counter for diagonal elements (should be the same as \texttt{Npoints}).
!!>
  ip = 0

!!> Loop over column to determine rowval and nzval.
!!> Because the matrix we are dealing with is symmetric, we can
!!> interchange index for row and column.
!!>
  DO colGbl = 1,Npoints

!!> Determine local column index for x, y, and z components
!!>
    colLoc_x = ceiling( real(colGbl)/(Ny*Nz) )
    !
    yy = colGbl - (colLoc_x - 1)*Ny*Nz
    colLoc_y = ceiling( real(yy)/Nz )
    !
    izz = ceiling( real(colGbl)/Nz )
    colLoc_z = colGbl - (izz-1)*Nz

!!> Diagonal element, which is only one element in any column/row,
!!> is calculated as sum of the corresponding local matrix elements in x, y, and z
!!>
    !ip = ip + 1
    !rowval(ip) = colGbl
    !nzval(ip) = D2jl_x(colLoc_x,colLoc_x) + D2jl_y(colLoc_y,colLoc_y) + D2jl_z(colLoc_z,colLoc_z)

!!> Non-diagonal elements.
!!>
    
    WRITE(*,*)
    WRITE(*,*)
    WRITE(*,*) 'colGbl = ', colGbl

    WRITE(*,*) 'rowval for x:'
    DO ix = 1,Nx
      !IF ( ix /= colLoc_x ) THEN 
        ip = ip + 1
        rowval_ip = rowGbl_x_orig(ix) + colGbl - 1 - (colLoc_x - 1)*Ny*Nz
        nzval_ip = D2jl_x(ix,colLoc_x)
        WRITE(*,'(I5)',advance='no') rowval_ip
      !ENDIF 
    ENDDO 
    WRITE(*,*)
    !
    WRITE(*,*) 'rowval for y:'
    DO iy = 1,Ny
      !IF ( iy /= colLoc_y ) THEN 
        ip = ip + 1
        rowval_ip = rowGbl_y_orig(iy) + colGbl - 1 - (izz-1)*Nz + (colLoc_x - 1)*Ny*Nz
        nzval_ip = D2jl_y(iy,colLoc_y)
        WRITE(*,'(I5)',advance='no') rowval_ip
      !ENDIF 
    ENDDO 
    WRITE(*,*)
    !
    WRITE(*,*) 'rowval for z:'
    DO iz = 1,Nz
!      IF ( iz /= colLoc_z ) THEN 
        ip = ip + 1
        rowval_ip = rowGbl_z_orig(iz) + (izz-1)*Nz
        nzval_ip = D2jl_z(iz,colLoc_z)
        WRITE(*,'(I5)',advance='no') rowval_ip
!      ENDIF 
    ENDDO 

  ENDDO 

  WRITE(*,*)

  DEALLOCATE( rowGbl_x_orig )
  DEALLOCATE( rowGbl_y_orig )
  DEALLOCATE( rowGbl_z_orig )

!! XXX: Sorting is not needed for current need.

  flush(6)

END SUBROUTINE 

