void petsc_start_();
void petsc_stop_();
void test_add_nabla2_();

int main(int argc, char **argv)
{
  petsc_start_();

  test_add_nabla2_();

  petsc_stop_();
}

