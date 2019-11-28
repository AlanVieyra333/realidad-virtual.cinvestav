#include "rehilete.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#elif defined __linux__
    #include <GL/glu.h>
#endif 

Rehilete::Rehilete(float l)
{
	l /= 2.0;
	// X										Y									Z
	aspa[0][0] = 0; 			aspa[0][1] = 0; 	aspa[0][2] = 0.0;
	aspa[1][0] = l/2.0; 	aspa[1][1] = l; 	aspa[1][2] = 0.0;
  aspa[2][0] = l/-2.0; 	aspa[2][1] = l; 	aspa[2][2] = 0.0;
}

void Rehilete::dibuja_figura(float angle)
{
	glRotatef(-45.0, 0.0, 1.0, 0.0);
	glRotatef(35.26, 0.0, 0.0, 1.0);
	glTranslated(1.73,0,0);
	glRotatef(90.00, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);

	dibuja_aspa(0.0);
	dibuja_aspa(360.0 / 3.0);
	dibuja_aspa(2 * 360.0 / 3.0);
}

void Rehilete::dibuja_aspa(float angle)
{
	glRotatef(angle, 0.0, 0.0, 1.0);

	static float Mcolores[6][3] = {
		{color[0], color[1], color[2]},
		{color[0], color[1], color[2]},
	};

	static int Mcaras[1][3] = {
			{0, 1, 2}};

	glBegin(GL_QUADS);

	for (int i = 0; i < 2; i++)
	{
		glColor3fv(Mcolores[i]);

		glVertex3fv(aspa[Mcaras[0][0]]);
		glVertex3fv(aspa[Mcaras[0][1]]);
		glVertex3fv(aspa[Mcaras[0][2]]);
	}
	
	glEnd();

	glRotatef(-angle, 0.0, 0.0, 1.0);
}
