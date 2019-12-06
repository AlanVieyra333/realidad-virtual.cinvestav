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

	set_resolution(1);
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
	float x, y, z;
	dataMesh* data_mesh = (dataMesh*) data;

	if(data_mesh->resolution != this->resolution) set_resolution(data_mesh->resolution);
	calculate_main_node(data_mesh->v_main_node);

	//printf("%f %f %f %d\n", data_mesh->force, data_mesh->alpha, data_mesh->beta, data_mesh->resolution);

    // Dibuja resortes
    for (int i = 0; i < springs_len; i++)
    {
		springs[0][i]->set_dir(0);
		springs[0][i]->dibuja_figura(data);

		springs[1][i]->set_dir(1);
		springs[1][i]->dibuja_figura(data);
    }

	// Dibuja punto en nodo principal de fuerza.
	glBegin(GL_POINTS);
		glColor3f(0.0, 0.0, 1.0);
		
		//glVertex3d(nodes[0][0], nodes[0][1], nodes[0][2]);

		x = data_mesh->v_main_node[0];
		y = springs[1][main_node[0]]->nodes[main_node[1]][1] + springs[1][main_node[0]]->mra[main_node[1]].y;
		z = data_mesh->v_main_node[2];
		glVertex3d(x, y, z);

		//glVertex3d(nodes[nodes_len - 1][0], nodes[nodes_len - 1][1], nodes[nodes_len - 1][2]);
	glEnd();
}

/*	#########################################################	*/

/**
 * Recalcula el numero de cuerdas, el nodo principal (x,y), .
*/
void Mesh::set_resolution(int resolution) {
	this->resolution = resolution;
	
	switch (this->resolution)
	{
	case 1:
		springs_len = BASE_SPRINGS;
		break;
	case 2:
		springs_len = (BASE_SPRINGS*2) - 1;
		break;
	case 3:
		springs_len = (BASE_SPRINGS*4) - 3;
		break;
	default:
		break;
	}

	init_springs_position();
}

/**
 * Calcula el nodo principal al que se le aplica la fuerza.
*/
void Mesh::calculate_main_node(float *v_main_node) {
	float length_x = abs(v_end[0] - v_start[0]);
	float length_z = abs(v_end[2] - v_start[2]);

	// Calcular el nodo i-esimo & j-esimo
	main_node[0] = (springs_len/2.0) + ((v_main_node[0] / 2.0) * springs_len);
	main_node[1] = (springs_len/2.0) + ((v_main_node[2] / 2.0) * springs_len);

	if(main_node[0] > springs_len - 1) main_node[0] = springs_len - 1;
	if(main_node[1] > springs_len - 1) main_node[1] = springs_len - 1;

	v_main_node[0] *= (length_x / 2.0);
	v_main_node[1] *= 0;
	v_main_node[2] *= (length_z / 2.0);
}
