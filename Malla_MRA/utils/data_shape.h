#ifndef DATA_SHAPE_H
#define DATA_SHAPE_H

#include <vector>

using namespace std;

typedef struct _dataMesh {
  bool apply_force;
  int resolution;
  float v_main_node[3];
  float v_force[3];
} dataMesh;

typedef struct _dataRehilete {
  float angle;
} dataRehilete;

#endif // DATA_SHAPE_H