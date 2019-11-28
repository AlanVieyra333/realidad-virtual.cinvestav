#ifndef SPRING_H
#define SPRING_H

#include "figura.h"
#include "../utils/mra.h"
#include <vector>
#include <cmath>

#define BASE_NODES 7
#define RESOLUTION_LEVEL 3
#define MAX_NODES (((BASE_NODES>>1) << RESOLUTION_LEVEL) + 1)		// 25  -> 7 nodos y resolucion 3

using namespace std;

class Spring : public Figura
{
public:
	Spring(vector<float> v1, vector<float>  v2);
	void dibuja_figura(float t);
	void set_node_force(int node);
	void set_force(float force);
	void set_resolution(int val);

private:
	vector<float>  v_start, v_end;
	float nodes[MAX_NODES][3];
	MRA mra[MAX_NODES];
	int nodes_len, node_force;
	float d_nodes;
	float force;

	void init();
	void step_deformation();
	void apply_force();
	void quit_force();
	void replicate_force();
};

#endif // SPRING_H
