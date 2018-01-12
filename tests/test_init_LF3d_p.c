#include "m_LF3d.h"
#include "common.h"

int main( int argc, char** argv)
{
  LF3d_T LF3d;
  int NN[3] = {3, 3, 3};
  double AA[3] = { 0.0, 0.0, 0.0 };
  double BB[3] = { 16.0, 16.0, 16.0 };
  
  init_LF3d_p( &LF3d, NN, AA, BB );
  info_LF3d( LF3d );

  return 0;
}
