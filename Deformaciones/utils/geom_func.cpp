#include "geom_func.h"
#include <cmath>

float distance(vector<float> v1, vector<float> v2) {
	return sqrt( pow(v2[0] - v1[0], 2) + pow(v2[1] - v1[1], 2) + pow(v2[2] - v1[2], 2));
}

float rad_to_deg(float rad) {
	return rad * 180.0 / M_PI;
}

float deg_to_rad(float deg) {
	return deg * M_PI / 180.0;
}

float vectors_angle(vector<float> v1, vector<float> v2) {
	return rad_to_deg(acos(point_product(v1, v2) / (mod_vector(v1) * mod_vector(v2))));
}

float point_product(vector<float> v1, vector<float> v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float mod_vector(vector<float> v) {
	return sqrt(point_product(v, v));
}

vector<float> vector_sub(vector<float> v1, vector<float> v2) {
	vector<float> res = {0,0,0};
	res[0] = v1[0] - v2[0];
	res[1] = v1[1] - v2[1];
	res[2] = v1[2] - v2[2];
	return res;
}