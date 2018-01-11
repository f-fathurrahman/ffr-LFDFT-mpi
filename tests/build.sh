#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo
  echo "ERROR"
  echo "Need two parameters: main file and compiler name (and or options)"
  echo "Example: ./build.sh myfile.f90 \"pgf90 -O2\""
  echo
  exit 1
fi

INC="-I../src/"
LIB="../src/libmain.a ../local/petsc-3.8.3_openmpi_gnu_debug/lib/libpetsc.a -lblas -llapack -lfftw3 -lX11 -ldl"

bas=`basename $1 .f90`

# remove the previous executable
rm -vf $bas.x

$2 $INC $1 $LIB -o $bas.x

echo "Test executable: $bas.x"

