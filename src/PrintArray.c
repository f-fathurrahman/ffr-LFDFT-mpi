#include <stdio.h>
#include "common.h"

//
// Print full double array
//
void PrintVector(double *V, int nelem)
{
  printf("nelem=%5d\n",nelem);
  for(int i=0; i<nelem; i++) {
    printf("%10.5f\n", V[i]);
  }
}

//
// Print full double matrix
//
void PrintMatrix(double *A, int NROW, int NCOL)
{
  printf("NROW=%5d, NCOL=%5d\n", NROW, NCOL);
  for(int i=1; i<=NROW; i++) {
    for(int j=1; j<=NCOL; j++) {
      printf("%10.5f ", A[IDX2F(i,j,NROW)]);
    }
    printf("\n");
  }
}
