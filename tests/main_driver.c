void petsc_start();
void petsc_stop();
void test_add_nabla2_();

int main(int argc, char **argv)
{
  petsc_start( argc, argv );

  // Call a subroutine from Fortran
  test_add_nabla2_();

  petsc_stop();
}

