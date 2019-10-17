#include <GL/glu.h>

#include "cubo.h"

Cubo::Cubo(vector<float> v1, vector<float> v2, float color[]):Figura(color)
{
	// X										Y											Z
	cubo[0][0] = v2[0]; 	cubo[0][1] = v2[1]; 	cubo[0][2] = v2[2];
  cubo[1][0] = v2[0]; 	cubo[1][1] = v2[1]; 	cubo[1][2] = v1[2];
  cubo[2][0] = v1[0]; 	cubo[2][1] = v2[1]; 	cubo[2][2] = v1[2];
  cubo[3][0] = v1[0]; 	cubo[3][1] = v2[1]; 	cubo[3][2] = v2[2];
	
	cubo[4][0] = v2[0];		cubo[4][1] = v1[1];		cubo[4][2] = v2[2];
	cubo[5][0] = v2[0]; 	cubo[5][1] = v1[1]; 	cubo[5][2] = v1[2];
  cubo[6][0] = v1[0]; 	cubo[6][1] = v1[1]; 	cubo[6][2] = v1[2];
  cubo[7][0] = v1[0]; 	cubo[7][1] = v1[1]; 	cubo[7][2] = v2[2];
}

void Cubo::dibuja_figura(float angle)
{
	/*glRotatef(-45.00, 0.0, 1.0, 0.0);
	glRotatef(35.26, 0.0, 0.0, 1.0);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glRotatef(-35.26, 0.0, 0.0, 1.0);
	glRotatef(45.00, 0.0, 1.0, 0.0);*/

	float darkColor[3] = {
		color[0] * (float) 0.65,
		color[1] * (float) 0.65,
		color[2] * (float) 0.65,
	};

	float middColor[3] = {
		color[0] * (float) 0.85,
		color[1] * (float) 0.85,
		color[2] * (float) 0.85,
	};

	float Mcolores[6][3] = {
		{darkColor[0], darkColor[1], darkColor[2]},
		{darkColor[0], darkColor[1], darkColor[2]},
		{middColor[0], middColor[1], middColor[2]},
		{color[0], color[1], color[2]},
		{middColor[0], middColor[1], middColor[2]},
		{color[0], color[1], color[2]},
	};

	static int Mcaras[6][4] = {
			{0, 1, 2, 3},
			{4, 7, 6, 5},
			{0, 4, 5, 1},
			{1, 2, 6, 5},
			{2, 6, 7, 3},
			{0, 3, 7, 4}};

	glBegin(GL_QUADS);

	for (int i = 0; i < 6; i++)
	{
		glColor3fv(&Mcolores[i][0]);

		glVertex3fv(cubo[Mcaras[i][0]]);
		glVertex3fv(cubo[Mcaras[i][1]]);
		glVertex3fv(cubo[Mcaras[i][2]]);
		glVertex3fv(cubo[Mcaras[i][3]]);
	}

	glEnd();
}
