#include "spring.h"
#include "../utils/geom_func.h"
#include <OpenGL/glu.h>

Spring::Spring(vector<float> v_start, vector<float> v_end)
{
	float x,y,z;

	this->v_start = v_start;
	this->v_end = v_end;

	nodes_len = BASE_NODES;
	current_node = (nodes_len / 2);
	d_nodes = distance(v_start, v_end) / (nodes_len - 1);
	for(int i = 0; i < nodes_len; i++) {
		x = v_start[0] + i * d_nodes;
		y = v_start[1];
		z = v_start[2];

		nodes[i][0] = x;
		nodes[i][1] = y;
		nodes[i][2] = z;

		// mra[i].x0 = x;
		// mra[i].x0 = y;
		// mra[i].x0 = z;
	}
}

void Spring::step_deformation() {
	// for( int i=0; i<mra2d.nodos; i++ ) { 
	// 	mra2d.s[i].x1 = mra2d.k1 * mra2d.s[i].x - mra2d.k2 * mra2d.s[i].x_1 + mra2d.s[i].k3x;
	// 	mra2d.s[i].x_1 = mra2d.s[i].x;
	// 	mra2d.s[i].x   = mra2d.s[i].x1;

	// 	mra2d.s[i].y1 = mra2d.k1 * mra2d.s[i].y - mra2d.k2 * mra2d.s[i].y_1 + mra2d.s[i].k3y;
	// 	mra2d.s[i].y_1 = mra2d.s[i].y;
	// 	mra2d.s[i].y   = mra2d.s[i].y1;

	// 	mra2d.s[i].z1 = mra2d.k1 * mra2d.s[i].z - mra2d.k2 * mra2d.s[i].z_1 + mra2d.s[i].k3z;
	// 	mra2d.s[i].z_1 = mra2d.s[i].z;
	// 	mra2d.s[i].z   = mra2d.s[i].z1;
	// }
}

void Spring::dibuja_figura(float t)
{
	step_deformation();
	float x, y, z;

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 0.0, 0.0);

		for (int i = 0; i < nodes_len; i++)
		{
			x = nodes[i][0] + mra[i].x0;
			y = nodes[i][1] + mra[i].y0;
			z = nodes[i][2] + mra[i].z0;
			
			glVertex3d(x, y, z);
		}
	glEnd();
	glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 1.0);
		
		glVertex3d(nodes[0][0], nodes[0][1], nodes[0][2]);

		x = nodes[current_node][0] + mra[current_node].x0;
		y = nodes[current_node][1] + mra[current_node].y0;
		z = nodes[current_node][2] + mra[current_node].z0;
		glVertex3d(x, y, z);

		glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	glEnd();
}
