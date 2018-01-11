#!/bin/bash

INC="-I./local/petsc-3.8.3_openmpi_gnu_debug/include/ "
LIB="libLFDFT_petsc.a -lblas -llapack -lfftw3 local/petsc-3.8.3_openmpi_gnu_debug/lib/libpetsc.a"

make

bas=`basename $1 .F`
# remove the previous executable
rm -vf $bas.x
mpifort -Wall -O3 -ffree-form $INC $1 $LIB -o $bas.x

# for
#mpifort -free $INC $1 $LIB -o $bas.x
