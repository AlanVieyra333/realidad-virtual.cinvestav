#ifndef DATA_SHAPE_H
#define DATA_SHAPE_H

typedef struct _dataMesh {
  bool apply_force;
  float force;
  float alpha;
  float beta;
  int resolution;
} dataMesh;

typedef struct _dataRehilete {
  float angle;
} dataRehilete;

#endif // DATA_SHAPE_H