# For the moment, gfortran will used throughout because this is the default
# Fortran compiler used by Open MPI

#INC = -I/home/efefer/mysoftwares/petsc-3.7.5/include/
#INC = -I./local/petsc-3.8.3_openmpi_gnu_debug/include/

MAKE = make
AR = ar

CC = mpicc
PETSC_HOME = ../local/petsc-3.8.3_openmpi_gnu_debug
CC_INC = -I$(PETSC_HOME)/include
CC_OPTS = -Wall -O3

F90 = mpifort
F90_OPTS = -Wall -O3 $(INC)

LIB_LINALG = -lblas -llapack
LIB_FFTW3 = -lfftw3
LIBS = $(LIB_LINALG) $(LIB_FFTW3)


C_SRC = \
init_LF3d_p.c \
info_LF3d.c \
dealloc_LF3d.c \
add_nabla2_x.c \
add_nabla2_y.c \
add_nabla2_z.c \
petsc_start.c \
petsc_stop.c \
PrintArray.c

F90_SRC = \
init_grid_1d_p.f90 \
init_grid_1d_c.f90 \
init_grid_1d_sinc.f90 \
init_deriv_matrix_p.f90 \
init_deriv_matrix_c.f90 \
init_deriv_matrix_sinc.f90 \
init_gvec.f90 \
mm_to_nn.f90

OBJ = $(C_SRC:.c=.o) $(F90_SRC:.f90=.o)

#
# Suffix rule for Fortran 90
#
%.mod :
	@if [! -f $@ ]; then \
		rm $(*F).o; \
		fi
	$(MAKE) $<

%.o : %.c
	$(CC) $(CC_INC) $(CC_OPTS) -c -o $(*F).o $<

%.o : %.f90
	$(F90) $(F90_OPTS) -c -o $(*F).o $<

# Targets
lib: $(OBJ)
	ar rcs libmain.a *.o

clean:
	rm -rf *.o *.mod libmain.a *.x


