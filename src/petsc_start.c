#include <stdlib.h>
#include <petsc.h>

void petsc_start_()
{
  PetscErrorCode ierr;
  //ierr = PetscInitialize( (char*)0, (char*)0, (char*)0, (char*)0 );
  ierr = PetscInitialize( NULL, NULL, NULL, NULL );

  if(ierr) {
    printf("Error when calling PetscInitialize\n");
    exit(1);
  }
}
