#ifndef SPRING_H
#define SPRING_H

#include "shape.h"
#include "../utils/mra.h"
#include <vector>
#include <cmath>

#define BASE_NODES 7
#define RESOLUTION_LEVEL 3
#define MAX_NODES (((BASE_NODES>>1) << RESOLUTION_LEVEL) + 1)		// 25  -> 7 nodos y resolucion 3

using namespace std;

class Spring : public Shape
{
public:
	Spring(vector<float> v1, vector<float>  v2);
	void dibuja_figura(void* data);
	void set_resolution(int val);
	void set_dir(int dir);
	float nodes[MAX_NODES][3];
	MRA mra[MAX_NODES];

private:
	vector<float>  v_start, v_end;
	
	int nodes_len;
	float d_nodes;
	int resolution;
	vector<float> v_force, v_main_node;
	int dir = 0;

	void init_nodes_position();
	void step_deformation();
	void apply_force();
	void quit_force();
	void replicate_force();

	void set_v_force(float v_force[3]);
	void set_v_main_node(float v_main_node[3]);
	vector<float> calculate_force(vector<float> node);
};

#endif // SPRING_H
