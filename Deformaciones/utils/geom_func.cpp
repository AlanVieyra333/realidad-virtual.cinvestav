#include "geom_func.h"
#include <cmath>

float distance(vector<float> p_1, vector<float> p_2) {
	return sqrt( pow(p_2[0] - p_1[0], 2) + pow(p_2[1] - p_1[1], 2) + pow(p_2[2] - p_1[2], 2));
}
