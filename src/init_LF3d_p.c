#include <stdio.h>
#include "m_LF3d.h"

void init_LF3d_p( LF3d_T* LF3d, int NN[3], double AA[3], double BB[3] )
{
  int i;
  int ip;

  for( i = 0; i < 3; i++ ) {
    (*LF3d).NN[i] = NN[i];
    (*LF3d).AA[i] = AA[i];
    (*LF3d).BB[i] = BB[i];
  }
  (*LF3d).Npoints = NN[0]*NN[1]*NN[2];
}

