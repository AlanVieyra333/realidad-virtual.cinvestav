#include "spring.h"
#include "../utils/geom_func.h"
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

	nodes_len = BASE_NODES;
	node_force = (nodes_len / 2);

	init();
}

void Spring::init() {
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

void Spring::dibuja_figura(float t)
{
	float x, y, z;

	if (t != 0) {
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

		x = nodes[node_force][0] + mra[node_force].x;
		y = nodes[node_force][1] + mra[node_force].y;
		z = nodes[node_force][2] + mra[node_force].z;
		glVertex3d(x, y, z);

		//glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	glEnd();
}

void Spring::step_deformation() {
	for( int i=0; i < nodes_len; i++ ) { 
		mra[i].step_deformation();
	}
}

void Spring::set_node_force(int node) {
	node_force = node;
}

void Spring::set_force(float force) {
	this->force = force;
	mra[node_force].set_force(force);
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
		float f = force / pow(2.0, d);

		// Izquierda/Arriba
		if (node_force - i >= 0)
			mra[node_force - i].set_force(f);

		// Derecha/Abajo
		if (node_force + i < nodes_len)
			mra[node_force + i].set_force(f);

		d += delta;
    }
}

void Spring::set_resolution(int val) {
	int val_anterior;
	if (nodes_len == BASE_NODES)
	{
		val_anterior = 1;
	} else if (nodes_len == (BASE_NODES*2) - 1)
	{
		val_anterior = 2;
	} else {
		val_anterior = 3;
	}
	
	switch (val)
	{
	case 1:
		nodes_len = BASE_NODES;
		if (val_anterior == 2)
			node_force = node_force/2;
		else if (val_anterior == 3)
			node_force = node_force/4;
		break;
	case 2:
		nodes_len = (BASE_NODES*2) - 1;
		if (val_anterior == 1)
			node_force = node_force*2;
		else if (val_anterior == 3)
			node_force = node_force/2;
		break;
	case 3:
		nodes_len = (BASE_NODES*4) - 3;
		if (val_anterior == 1)
			node_force = node_force*4;
		else if (val_anterior == 2)
			node_force = node_force*2;
		break;
	default:
		break;
	}

	init();
}