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
	return rad_to_deg(acos(point_product(v1, v2) / (vector_mod(v1) * vector_mod(v2))));
}

float point_product(vector<float> v1, vector<float> v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float vector_mod(vector<float> v) {
	return sqrt(point_product(v, v));
}

vector<float> normalize_vector(vector<float> v) {
	vector<float> result = {0,0,0};

	float length = distance({0,0,0}, v);
    result[0] = v[0] / length;
    result[1] = v[1] / length;
    result[2] = v[2] / length;

	return result;
}

vector<float> escalar_product(vector<float> v, float k) {
	vector<float> result = {0,0,0};

    result[0] = v[0] * k;
    result[1] = v[1] * k;
    result[2] = v[2] * k;

	return result;
}

vector<float> vector_sub(vector<float> v1, vector<float> v2) {
	vector<float> res = {0,0,0};
	res[0] = v1[0] - v2[0];
	res[1] = v1[1] - v2[1];
	res[2] = v1[2] - v2[2];
	return res;
}

vector<float> to_vector_force(float force, float alpha_rad, float beta_rad) {
	vector<float> v_force = {0,0,0};
    v_force[0] = cos(beta_rad) * cos(alpha_rad);
    v_force[1] = sin(beta_rad);
    v_force[2] = sin(alpha_rad) * cos(beta_rad);

    // Normalize
    v_force = normalize_vector(v_force);
    // Establecer fuerza
    v_force = escalar_product(v_force, force);

	return v_force;
}