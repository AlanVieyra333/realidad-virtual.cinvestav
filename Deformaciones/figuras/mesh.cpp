#include "mesh.h"
#include "../utils/geom_func.h"
#include "../utils/data_shape.h"
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

	force = 0.2;
	alpha = 0.0;
	beta = 90.0;
	resolution = 1;
	main_node_x = (springs_len / 2);
	main_node_y = (springs_len / 2);

	init_springs_position();
}

/**
 * Calcula la distancia entre cuerdas.
 * Inicializa la pocision de c/cuerda (v_estart, v_end).
*/
void Mesh::init_springs_position() {
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

void Mesh::dibuja_figura(void* data)
{
	dataMesh* data_mesh = (dataMesh*) data;

	if(data_mesh->resolution != this->resolution) set_resolution(data_mesh->resolution);
	this->alpha = data_mesh->alpha;
	this->beta = data_mesh->beta;
	this->force = data_mesh->force;
	set_3dMouse(data_mesh->mouse3d_x, data_mesh->mouse3d_y);

	//printf("%f %f %f %d\n", data_mesh->force, data_mesh->alpha, data_mesh->beta, data_mesh->resolution);

	// Especificar el nodo principal de cada resorte.
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->set_main_node(main_node_x);
		springs[1][i]->set_main_node(main_node_y);
    }

	replicate_force();

    // Dibuja resortes
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->dibuja_figura(data);
		springs[1][i]->dibuja_figura(data);
    }
}

void Mesh::set_main_node(int main_node_x, int main_node_y) {
	this->main_node_x = main_node_x;
	this->main_node_y = main_node_y;
}

void Mesh::replicate_force() {
	float delta = (BASE_NODES - 1.0)/(springs_len - 1.0);	// Distancia entre resortes
	float d = 0.0;

	for (int i = 0; i <= springs_len; i++)
    {
		double f = force / pow(2.0, d);

		// Arriba
		if (main_node_y - i >= 0)
			springs[0][main_node_y - i]->set_force(f);
		
		// Abajo
		if (main_node_y + i < springs_len)
			springs[0][main_node_y + i]->set_force(f);

		// Izquierda
		if (main_node_x - i >= 0)
			springs[1][main_node_x - i]->set_force(f);

		// Derecha
		if (main_node_x + i < springs_len)
			springs[1][main_node_x + i]->set_force(f);

		d += delta;
    }
}

/*	#########################################################	*/

/**
 * Recalcula el numero de cuerdas, el nodo principal (x,y), .
*/
void Mesh::set_resolution(int val) {
	int prev_resolution = this->resolution;
	this->resolution = val;
	
	switch (this->resolution)
	{
	case 1:
		springs_len = BASE_SPRINGS;
		if (prev_resolution == 2){
			set_main_node(main_node_x/2, main_node_y/2);
		} else if (prev_resolution == 3){
			set_main_node(main_node_x/4, main_node_y/4);
		}
		break;
	case 2:
		springs_len = (BASE_SPRINGS*2) - 1;
		if (prev_resolution == 1){
			set_main_node(main_node_x*2, main_node_y*2);
		} else if (prev_resolution == 3){
			set_main_node(main_node_x/2, main_node_y/2);
		}
		break;
	case 3:
		springs_len = (BASE_SPRINGS*4) - 3;
		if (prev_resolution == 1){
			set_main_node(main_node_x*4, main_node_y*4);
		} else if (prev_resolution == 2){
			set_main_node(main_node_x*2, main_node_y*2);
		}
		break;
	default:
		break;
	}

	init_springs_position();
}

void Mesh::set_3dMouse(short rx, short ry) {
	short min = -525;
	short max = 525;
	short total = max - min;
	short interval = total/springs_len;

	short nodes_move = rx / interval;
	short node_x = (springs_len / 2) - nodes_move;

	nodes_move = ry / interval;
	short node_y = (springs_len / 2) - nodes_move;

	//printf("mouse: %d %d\n", rx, ry);
	//printf("nodes: %d %d\n", node_x, node_y);
	
	if(main_node_x != node_x || main_node_y != node_y){
		main_node_x = node_x;
		main_node_y = node_y;
	}
}
