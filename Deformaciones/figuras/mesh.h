#ifndef MESH_H
#define MESH_H

#include "figura.h"
#include "spring.h"
#include <vector>

#define BASE_SPRINGS 7
#define MAX_SPRINGS (((BASE_SPRINGS>>1) << RESOLUTION_LEVEL) + 1)		// 25  -> 7 resortes y resolucion 3

using namespace std;

class Mesh : public Figura
{
public:
	Mesh(vector<float> v_start, vector<float>  v_end);
	void dibuja_figura(void* data);

private:
	vector<float> v_start, v_end;
	Spring *springs[2][MAX_SPRINGS];	// Vertical & Horizontal
	int springs_len;
	float d_spring;
	int resolution;

	void init_springs_position();
	void set_resolution(int resolution);
	void calculate_main_node(float *v_main_node);
};

#endif // MESH_H
