#include "cubo.h"
#if defined(__APPLE__) || defined(MACOSX)
  #include <GLUT/glut.h>
#else
    #include <gl/glut.h>
#endif

Cubo::Cubo(float l)
{
	// X							Y								Z
	cubo[0][0] = l; cubo[0][1] = l; cubo[0][2] = l;
	cubo[1][0] = l; cubo[1][1] = l; cubo[1][2] = 0;
  cubo[2][0] = 0; cubo[2][1] = l; cubo[2][2] = 0;
  cubo[3][0] = 0; cubo[3][1] = l; cubo[3][2] = l;
	
	cubo[4][0] = l; cubo[4][1] = 0; cubo[4][2] = l;
  cubo[5][0] = l; cubo[5][1] = 0; cubo[5][2] = 0;
  cubo[6][0] = 0; cubo[6][1] = 0; cubo[6][2] = 0;
  cubo[7][0] = 0; cubo[7][1] = 0; cubo[7][2] = l;
}

void Cubo::dibuja_figura(float angle)
{
	/*glRotatef(-45.00, 0.0, 1.0, 0.0);
	glRotatef(35.26, 0.0, 0.0, 1.0);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glRotatef(-35.26, 0.0, 0.0, 1.0);
	glRotatef(45.00, 0.0, 1.0, 0.0);*/

	static float Mcolores[6][3] = {
			{1.0, 0.0, 0.0},	// rojo
			{0.0, 1.0, 0.0},	// verde
			{0.0, 0.0, 1.0},	// azul
			{1.0, 1.0, 0.0},	// amarillo
			{1.0, 1.0, 1.0},	// blanca
			{1.0, 0.0, 1.0}}; // magenta

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
