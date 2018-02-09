#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo
  echo "ERROR calling this dumb one-line build script"
  echo "Need one parameter: main file"
  echo "mpicc will be used as compiler command"
  echo
  exit 1
fi

INC="-I../src/ -I/usr/local/petsc-3.8.3_openmpi_gnu/include"
LIB="../src/libmain.a -L/usr/local/petsc-3.8.3_openmpi_gnu/lib -lpetsc \
-lblas -llapack -lfftw3 -lm -lgfortran"

bas=`basename $1 .c`

# remove the previous executable
rm -vf ${bas}.x

mpicc $INC $1 $LIB -o ${bas}.x

echo "Test executable: $bas.x"

