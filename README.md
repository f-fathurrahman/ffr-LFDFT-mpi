An attempt to parallelize `ffr-LFDFT`.

I decided to use PETSc and use its C API directly rather that using the
Fortran binding.
This means that I need to convert the Fortran codes to C.
Some Fortan codes from `ffr-LFDFT` are still used however.

