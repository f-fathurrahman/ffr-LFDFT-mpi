#include <stdlib.h>
#include "m_LF3d.h"

void dealloc_LF3d(LF3d_T LF3d)
{
  if( LF3d.grid_x != NULL ) free(LF3d.grid_x); LF3d.grid_x = NULL;
  if( LF3d.grid_y != NULL ) free(LF3d.grid_y); LF3d.grid_y = NULL;
  if( LF3d.grid_z != NULL ) free(LF3d.grid_z); LF3d.grid_z = NULL;
}
