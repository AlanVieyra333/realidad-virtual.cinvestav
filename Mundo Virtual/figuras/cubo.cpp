#include <GL/glu.h>

#include "cubo.h"

Cubo::Cubo(vector<float> v1, vector<float> v2, float color[3]):Figura(color)
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

	Mcolores[0][0] = darkColor[0];	Mcolores[0][1] = darkColor[1];	Mcolores[0][2] = darkColor[2];
	Mcolores[1][0] = darkColor[0];	Mcolores[1][1] = darkColor[1];	Mcolores[1][2] = darkColor[2];
	Mcolores[2][0] = middColor[0];	Mcolores[2][1] = middColor[1];	Mcolores[2][2] = middColor[2];
	Mcolores[3][0] = color[0];			Mcolores[3][1] = color[1];			Mcolores[3][2] = color[2];
	Mcolores[4][0] = middColor[0];	Mcolores[4][1] = middColor[1];	Mcolores[4][2] = middColor[2];
	Mcolores[5][0] = color[0];			Mcolores[5][1] = color[1];			Mcolores[5][2] = color[2];
}

void Cubo::dibuja_figura(float angle)
{
	// Rotar sobre la diagonal principal.
	/*glRotatef(-45.00, 0.0, 1.0, 0.0);
	glRotatef(35.26, 0.0, 0.0, 1.0);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glRotatef(-35.26, 0.0, 0.0, 1.0);
	glRotatef(45.00, 0.0, 1.0, 0.0);*/

	glBegin(GL_QUADS);

	for (int i = 0; i < 6; i++)
	{
		glColor3fv(Mcolores[i]);

		glVertex3fv(cubo[Mcaras[i][0]]);
		glVertex3fv(cubo[Mcaras[i][1]]);
		glVertex3fv(cubo[Mcaras[i][2]]);
		glVertex3fv(cubo[Mcaras[i][3]]);
	}

	glEnd();
}
