#include "mesh.h"
#include "../utils/geom_func.h"
#include <cmath>
#include <cstdio>

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#elif defined __linux__
    #include <GL/glu.h>
#endif 

Mesh::Mesh(vector<float> v_start, vector<float> v_end)
{
	this->v_start = v_start;
	this->v_end = v_end;

	springs_len = BASE_SPRINGS;
	node_force_x = (springs_len / 2);
	node_force_y = (springs_len / 2);

	force = 0.2;

	init();
}

void Mesh::init() {
	vector<float> v1, v2;

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
	// Especificar el nodo principal de cada resorte.
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->set_node_force(node_force_x);
		springs[1][i]->set_node_force(node_force_y);
    }

	replicate_force();

    // Dibuja resortes
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->dibuja_figura(t);
		springs[1][i]->dibuja_figura(t);
    }
}

void Mesh::set_node_force(int node_force_x, int node_force_y) {
	this->node_force_x = node_force_x;
	this->node_force_y = node_force_y;
}

void Mesh::set_force(float force) {
	this->force = force;
}

void Mesh::replicate_force() {
	float delta = (BASE_NODES - 1.0)/(springs_len - 1.0);	// Distancia entre resortes
	float d = 0.0;

	for (int i = 0; i <= springs_len; i++)
    {
		double f = force / pow(2.0, d);

		// Arriba
		if (node_force_y - i >= 0)
			springs[0][node_force_y - i]->set_force(f);
		
		// Abajo
		if (node_force_y + i < springs_len)
			springs[0][node_force_y + i]->set_force(f);

		// Izquierda
		if (node_force_x - i >= 0)
			springs[1][node_force_x - i]->set_force(f);

		// Derecha
		if (node_force_x + i < springs_len)
			springs[1][node_force_x + i]->set_force(f);

		d += delta;
    }
}

/*	#########################################################	*/

void Mesh::set_resolution(int val) {
	int val_anterior;
	if (springs_len == BASE_SPRINGS)
	{
		val_anterior = 1;
	} else if (springs_len == (BASE_SPRINGS*2) - 1)
	{
		val_anterior = 2;
	} else {
		val_anterior = 3;
	}
	
	switch (val)
	{
	case 1:
		springs_len = BASE_SPRINGS;
		if (val_anterior == 2){
			node_force_x = node_force_x/2;
			node_force_y = node_force_y/2;
		} else if (val_anterior == 3){
			node_force_x = node_force_x/4;
			node_force_y = node_force_y/4;
		}
		break;
	case 2:
		springs_len = (BASE_SPRINGS*2) - 1;
		if (val_anterior == 1){
			node_force_x = node_force_x*2;
			node_force_y = node_force_y*2;
		} else if (val_anterior == 3){
			node_force_x = node_force_x/2;
			node_force_y = node_force_y/2;
		}
		break;
	case 3:
		springs_len = (BASE_SPRINGS*4) - 3;
		if (val_anterior == 1){
			node_force_x = node_force_x*4;
			node_force_y = node_force_y*4;
		} else if (val_anterior == 2){
			node_force_x = node_force_x*2;
			node_force_y = node_force_y*2;
		}
		break;
	default:
		break;
	}

	init();

	// Nueva resolucion de resortes
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->set_resolution(val);
		springs[1][i]->set_resolution(val);
    }
}