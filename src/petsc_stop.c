#include <stdlib.h>
#include <petsc.h>

void petsc_stop()
{
  PetscErrorCode ierr;
  ierr = PetscFinalize();

  if(ierr) {
    printf("Error when calling PetscFinalize\n");
    exit(1);
  }
}

// This is supposed to be called from Fortran
void petsc_stop_()
{
  petsc_stop();
}



