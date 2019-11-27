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

private:
	vector<float>  v_start, v_end;
	float nodes[MAX_NODES][3];
	MRA mra[MAX_NODES];
	int nodes_len, current_node;
	float d_nodes;

	void step_deformation();
};

#endif // SPRING_H
