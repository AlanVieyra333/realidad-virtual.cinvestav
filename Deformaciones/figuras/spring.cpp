#include "spring.h"
#include "../utils/geom_func.h"
#include "../utils/data_shape.h"
#include <cstdio>

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#elif defined __linux__
    #include <GL/glu.h>
#endif 

Spring::Spring(vector<float> v_start, vector<float> v_end)
{
	this->v_start = v_start;
	this->v_end = v_end;

	set_v_force({0,0.2,0});
	nodes_len = BASE_NODES;
	main_node = (nodes_len / 2);

	init_nodes_position();
}

/**
 * Calcula la distancia entre los nodos.
 * Calcula la dirección donde se pondran los nodos.
 * Calcula la posición x,y,z base (inicial, antes de aplicar la fuerza), de c/nodo.
*/
void Spring::init_nodes_position() {
	float x,y,z;
	d_nodes = distance(v_start, v_end) / (nodes_len - 1);

	vector<float> v_dir = vector_sub(v_end, v_start);
	float angle = vectors_angle(v_dir, {1,0,0});
	for(int i = 0; i < nodes_len; i++) {
		x = v_start[0] + i * d_nodes * cos(deg_to_rad(angle));
		y = v_start[1];
		z = v_start[2] + i * d_nodes * sin(deg_to_rad(angle));

		nodes[i][0] = x;
		nodes[i][1] = y;
		nodes[i][2] = z;
	}
}

void Spring::dibuja_figura(void* data)
{
	float x, y, z;
	dataMesh* data_mesh = (dataMesh*) data;

	if(data_mesh->resolution != this->resolution) set_resolution(data_mesh->resolution);
	//set_v_force(data_mesh->v_force);

	if (data_mesh->apply_force) {
		replicate_force();
		apply_force();
	} else {
		quit_force();
	}

	step_deformation();

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.0, 0.0);

		for (int i = 0; i < nodes_len; i++)
		{
			x = nodes[i][0] + mra[i].x;
			y = nodes[i][1] + mra[i].y;
			z = nodes[i][2] + mra[i].z;
			
			glVertex3d(x, y, z);
		}
	glEnd();
	glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 1.0);
		
		//glVertex3d(nodes[0][0], nodes[0][1], nodes[0][2]);

		x = nodes[main_node][0] + mra[main_node].x;
		y = nodes[main_node][1] + mra[main_node].y;
		z = nodes[main_node][2] + mra[main_node].z;
		glVertex3d(x, y, z);

		//glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	glEnd();
}

void Spring::step_deformation() {
	for( int i=0; i < nodes_len; i++ ) { 
		mra[i].step_deformation();
	}
}

void Spring::set_main_node(int node) {
	main_node = node;
}

void Spring::set_v_force(vector<float> v_force) {
	this->v_force = v_force;
}

void Spring::apply_force() {
	for (int i = 0; i < nodes_len; i++)
		mra[i].apply_force();
}

void Spring::quit_force() {
	for (int i = 0; i < nodes_len; i++)
		mra[i].quit_force();
}

void Spring::replicate_force() {
	float delta = (BASE_NODES - 1.0)/(nodes_len - 1.0);	// Distancia entre resortes
	float d = 0.0;

	for (int i = 0; i <= nodes_len; i++)
    {
		vector<float> v_new_force = escalar_product(v_force, 1.0 / pow(2.0, d));
		//printf("val: %f %f %f\n", v_new_force[0], v_new_force[1], v_new_force[2]);

		// Izquierda/Arriba
		if (main_node - i >= 0)
			mra[main_node - i].set_v_force(v_new_force);

		// Derecha/Abajo
		if (main_node + i < nodes_len)
			mra[main_node + i].set_v_force(v_new_force);

		d += delta;
    }
}

void Spring::set_resolution(int val) {
	int prev_resolution = this->resolution;
	this->resolution = val;
	
	switch (this->resolution)
	{
	case 1:
		nodes_len = BASE_NODES;
		if (prev_resolution == 2)
			main_node = main_node/2;
		else if (prev_resolution == 3)
			main_node = main_node/4;
		break;
	case 2:
		nodes_len = (BASE_NODES*2) - 1;
		if (prev_resolution == 1)
			main_node = main_node*2;
		else if (prev_resolution == 3)
			main_node = main_node/2;
		break;
	case 3:
		nodes_len = (BASE_NODES*4) - 3;
		if (prev_resolution == 1)
			main_node = main_node*4;
		else if (prev_resolution == 2)
			main_node = main_node*2;
		break;
	default:
		break;
	}

	init_nodes_position();
}