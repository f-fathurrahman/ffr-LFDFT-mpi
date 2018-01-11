#include <stdlib.h>
#include <petsc.h>

void petsc_stop_()
{
  PetscErrorCode ierr;
  ierr = PetscFinalize();

  if(ierr) {
    printf("Error when calling PetscFinalize\n");
    exit(1);
  }
}
