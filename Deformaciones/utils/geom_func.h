#ifndef GEOM_FUNC_H
#define GEOM_FUNC_H

#include <vector>

using namespace std;

float distance(vector<float> v1, vector<float> v2);
float rad_to_deg(float rad);
float deg_to_rad(float deg);
float vectors_angle(vector<float> v1, vector<float> v2);
float point_product(vector<float> v1, vector<float> v2);
float mod_vector(vector<float> v);
vector<float> vector_sub(vector<float> v1, vector<float> v2);

#endif // GEOM_FUNC_H