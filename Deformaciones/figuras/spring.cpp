#include "spring.h"
#include "../utils/geom_func.h"
#include <cstdio>

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#elif defined _WIN32 || defined _WIN64
    #include <GL/glu.h>
#endif 

Spring::Spring(vector<float> v_start, vector<float> v_end)
{
	float x,y,z;

	this->v_start = v_start;
	this->v_end = v_end;

	nodes_len = BASE_NODES;
	current_node = (nodes_len / 2);
	d_nodes = distance(v_start, v_end) / (nodes_len - 1);

	//printf("%f\n", angle(v_start, v_end));
	vector<float> v_dir = vector_sub(v_end, v_start);
	float angle = vectors_angle(v_dir, {1,0,0});
	for(int i = 0; i < nodes_len; i++) {
		x = v_start[0] + i * d_nodes * cos(deg_to_rad(angle));
		y = v_start[1];
		z = v_start[2] + i * d_nodes * sin(deg_to_rad(angle));

		nodes[i][0] = x;
		nodes[i][1] = y;
		nodes[i][2] = z;

		// mra[i].x0 = x;
		// mra[i].x0 = y;
		// mra[i].x0 = z;
	}
}

void Spring::dibuja_figura(float t)
{
	float x, y, z;

	if (t != 0) {
		mra[current_node].apply_force();
	} else {
		mra[current_node].quit_force();
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
		
		glVertex3d(nodes[0][0], nodes[0][1], nodes[0][2]);

		x = nodes[current_node][0] + mra[current_node].x;
		y = nodes[current_node][1] + mra[current_node].y;
		z = nodes[current_node][2] + mra[current_node].z;
		glVertex3d(x, y, z);

		glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	glEnd();
}

void Spring::step_deformation() {
	for( int i=0; i < nodes_len; i++ ) { 
		mra[i].step_deformation();
	}
}