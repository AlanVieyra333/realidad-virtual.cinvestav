#ifndef DATA_SHAPE_H
#define DATA_SHAPE_H

#include <vector>

using namespace std;

typedef struct _dataMesh {
  bool apply_force;
  int resolution;
  int mouse3d_x;
  int mouse3d_y;
  float v_force[3];
} dataMesh;

typedef struct _dataRehilete {
  float angle;
} dataRehilete;

#endif // DATA_SHAPE_H