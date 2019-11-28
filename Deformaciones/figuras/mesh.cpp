#include "mesh.h"
#include "../utils/geom_func.h"
#include <GL/glu.h>
#include <cmath>
#include <cstdio>

Mesh::Mesh(vector<float> v_start, vector<float> v_end)
{
	vector<float> v1, v2;

	this->v_start = v_start;
	this->v_end = v_end;

	springs_len = BASE_SPRINGS;
	current_spring = (springs_len / 2);
	d_spring = distance(v_start, {v_start[0], v_start[1], v_end[0]}) / (springs_len - 1);

	// Resortes horizontales
	for(int i = 0; i < springs_len; i++) {
		v1 = {v_start[0], v_start[1], v_start[2] + i * d_spring};
        v2 = {v_end[0], v_start[1], v_start[2] + i * d_spring};

		springs[0][i] = new Spring(v1, v2);
		//printf("Spring %f %f %f \t %f %f %f\n", v1[0], v1[1], v1[2], v2[0], v2[1], v2[2]);
	}

	// Resortes verticales
	for(int i = 0; i < springs_len; i++) {
		v1 = {v_start[0] + i * d_spring, v_start[1], v_start[2]};
        v2 = {v_start[0] + i * d_spring, v_start[1], v_end[2]};

		springs[1][i] = new Spring(v1, v2);
		//printf("Spring %f %f %f \t %f %f %f\n", v1[0], v1[1], v1[2], v2[0], v2[1], v2[2]);
	}
}

void Mesh::dibuja_figura(float t)
{
    // Resortes
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->dibuja_figura(t);
		springs[1][i]->dibuja_figura(t);
    }
}
