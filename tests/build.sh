#!/bin/bash

if [ "$#" -ne 3 ]; then
  echo
  echo "ERROR calling this dumb one-line build script"
  echo "Need two parameters: main file, compiler command, and version (opt or debug)"
  echo "Example:"
  echo "./build.sh myfile.c \"mpicc -O2\" debug"
  echo
  exit 1
fi

INC="-I../src/ -I../local/petsc-3.8.3_openmpi_gnu_$3/include"
LIB="../src/libmain.a ../local/petsc-3.8.3_openmpi_gnu_$3/lib/libpetsc.a -lblas -llapack -lfftw3 -lX11 -lm -lgfortran -ldl"

bas=`basename $1 .c`

# remove the previous executable
rm -vf ${bas}_$3.x

$2 $INC $1 $LIB -o ${bas}_$3.x

echo "Test executable: $bas.x"

