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
	void dibuja_figura(void* data);
	void set_main_node(int node);
	void set_force(float force);
	void set_alpha(float alpha);
    void set_beta(float beta);
	void set_resolution(int val);

private:
	vector<float>  v_start, v_end;
	float nodes[MAX_NODES][3];
	MRA mra[MAX_NODES];
	int nodes_len, main_node;
	float d_nodes;
	int resolution;

	void init_nodes_position();
	void step_deformation();
	void apply_force();
	void quit_force();
	void replicate_force();
};

#endif // SPRING_H
