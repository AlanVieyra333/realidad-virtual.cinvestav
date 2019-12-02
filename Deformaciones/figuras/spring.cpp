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

	v_force = {0,0.2,0};
	v_main_node = {0,0,0};
	nodes_len = BASE_NODES;

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
	set_v_force(data_mesh->v_force);
	set_v_main_node(data_mesh->v_main_node);

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
	// glBegin(GL_POINTS);
	// 	glColor3f(0.0, 0.0, 1.0);
		
	// 	//glVertex3d(nodes[0][0], nodes[0][1], nodes[0][2]);

	// 	x = nodes[main_node][0] + mra[main_node].x;
	// 	y = nodes[main_node][1] + mra[main_node].y;
	// 	z = nodes[main_node][2] + mra[main_node].z;
	// 	glVertex3d(x, y, z);

	// 	//glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	// glEnd();
}

void Spring::step_deformation() {
	for( int i=0; i < nodes_len; i++ ) { 
		mra[i].step_deformation();
	}
}

void Spring::set_v_force(float v_force[3]) {
	this->v_force[0] = v_force[0];
	this->v_force[1] = v_force[1];
	this->v_force[2] = v_force[2];
}

void Spring::apply_force() {
	for (int i = 0; i < nodes_len; i++)
		mra[i].apply_force();
}

void Spring::quit_force() {
	for (int i = 0; i < nodes_len; i++)
		mra[i].quit_force();
}

void Spring::set_dir(int dir) {
	this->dir = dir;
}

void Spring::replicate_force() {
	float delta = (BASE_NODES - 1.0)/(nodes_len - 1.0);	// Distancia entre resortes
	float d = 0.0;

	for (int i = 0; i < nodes_len; i++)
    {
		vector<float> v_node = {0,0,0};

		if(dir == 0) {	// Horizontal
			float length_x = abs(v_end[0] - v_start[0]);
			float unity = length_x / (nodes_len - 1);

			v_node[0] = v_start[0] + (unity * i);
			v_node[1] = v_start[1];	
			v_node[2] = v_start[2];	
		}else {
			float length_x = abs(v_end[2] - v_start[2]);
			float unity = length_x / (nodes_len - 1);

			v_node[0] = v_start[0];
			v_node[1] = v_start[1];
			v_node[2] = v_start[2] + (unity * i);	
		}
		
		vector<float> v_new_force = calculate_force(v_node);
		//vector<float> v_new_force = escalar_product(v_force, 1.0 / pow(2.0, d));
		//printf("val: %f %f %f\n", v_new_force[0], v_new_force[1], v_new_force[2]);
		//printf("vectores: %f %f %f    %f %f %f\n", v_node[0], v_node[1], v_node[2], v_main_node[0], v_main_node[1], v_main_node[2]);

		mra[i].set_v_force(v_new_force);

		d += delta;
    }
}

void Spring::set_resolution(int resolution) {
	this->resolution = resolution;
	
	switch (this->resolution)
	{
	case 1:
		nodes_len = BASE_NODES;
		break;
	case 2:
		nodes_len = (BASE_NODES*2) - 1;
		break;
	case 3:
		nodes_len = (BASE_NODES*4) - 3;
		break;
	default:
		break;
	}

	init_nodes_position();
}

void Spring::set_v_main_node(float v_main_node[3]) {
	this->v_main_node[0] = v_main_node[0];
	this->v_main_node[1] = v_main_node[1];
	this->v_main_node[2] = v_main_node[2];
}

vector<float> Spring::calculate_force(vector<float> v_node) {
	vector<float> result;
	float dist = distance(v_node, v_main_node);
	float length_x = abs(v_end[0] - v_start[0]);
	float unity = length_x / (nodes_len - 1);

	if(dir == 1) {
		length_x = abs(v_end[2] - v_start[2]);
		unity = length_x / (nodes_len - 1);
	}

	float dist_relative = dist / unity;

	result = escalar_product(v_force, 1.0 / pow(2.0, dist_relative));

	if(dir == 1) {
		printf("v_node: %f %f %f\n", result[0], result[1], result[2]);
		printf("v_node: %f %f %f\n", dist, unity, dist_relative);
		//printf("      v_main_node: %f %f %f\n", v_main_node[0], v_main_node[1], v_main_node[2]);
	}

	return result;
}
