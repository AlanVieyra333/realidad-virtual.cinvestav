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
	void dibuja_figura(float t);
	void set_node_force(int node_force_x, int node_force_y);
	void set_force(float force);
	void set_angle_alpha(float val);
	void set_angle_beta(float val);
	void set_resolution(int val);

private:
	vector<float> v_start, v_end;
	Spring *springs[2][MAX_SPRINGS];	// Vertical & Horizontal
	int springs_len;
	float d_spring;
	int node_force_x, node_force_y;
	float force;

	void init();
	void replicate_force();
};

#endif // MESH_H
