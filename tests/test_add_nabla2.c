#include "m_LF3d.h"
#include "common.h"
#include "m_mpi.h"

int main( int argc, char** argv)
{

  petsc_start(argc, argv);
  
  LF3d_T LF3d;
  int NN[3] = {3, 3, 3};
  double AA[3] = { 0.0, 0.0, 0.0 };
  double BB[3] = { 16.0, 16.0, 16.0 };
  
  init_LF3d_p( &LF3d, NN, AA, BB );
  if( M_MPI_my_rank == 0 ) {
    info_LF3d( LF3d );
  }

  int Nx = NN[0];
  int Ny = NN[1];
  int Nz = NN[2];
  int Npoints = Nx*Ny*Nz;
  int i;
  int nnzc;
  int* nnz;

  // number of non-zeros per column
  nnzc = Nx + Ny + Nz - 2;
  //
  nnz = malloc( Npoints*sizeof(int) );
  for( i = 0; i < Npoints; i++ ) {
    nnz[i] = nnzc;
  }
  //
  Mat nabla2;
  PetscPrintf(PETSC_COMM_WORLD, "\nNumber of nonzeros = %10d\n", nnzc*Npoints);
  PetscPrintf(PETSC_COMM_WORLD, "Memory required for those nonzeros is %18.10f GB\n",
              nnzc*Npoints*8.0/1024.0/1024.0/1024.0);

  PetscErrorCode ierr;
  
  
  /* FIXME: Not needed ?
  int d_nz = nnzc/M_MPI_Nprocs; // local no. of diagonal elements
  int o_nz = (nnzc*Npoints)/(M_MPI_Nprocs*M_MPI_Nprocs) - d_nz;
  PetscPrintf( PETSC_COMM_WORLD, "d_nz = %d, o_nz = %d\n", d_nz, o_nz );
  */

  ierr = MatCreateAIJ( PETSC_COMM_WORLD, PETSC_DECIDE, PETSC_DECIDE, 
                       Npoints, Npoints, nnzc, NULL, nnzc, NULL, &nabla2 );
  
  if( M_MPI_my_rank == 0 ) {
    add_nabla2_z( Nx, Ny, Nz, LF3d.D2jl_z, &nabla2 );
    add_nabla2_y( Nx, Ny, Nz, LF3d.D2jl_y, &nabla2 );
    add_nabla2_x( Nx, Ny, Nz, LF3d.D2jl_x, &nabla2 );
  }

  ierr = MatAssemblyBegin( nabla2, MAT_FINAL_ASSEMBLY );
  ierr = MatAssemblyEnd( nabla2, MAT_FINAL_ASSEMBLY );

  int is_big = NN[0] > 4 || NN[1] > 4 || NN[2] > 4;
  if( !is_big ) {
    MatView( nabla2, PETSC_VIEWER_STDOUT_WORLD );
  }

  dealloc_LF3d(LF3d);

  petsc_stop();

  return 0;
}
