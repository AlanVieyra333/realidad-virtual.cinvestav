#ifndef CUBO_H
#define CUBO_H

#include "figura.h"
#include <vector>

using namespace std;

class Cubo : public Figura
{
public:
	Cubo(vector<float> v1, vector<float> v2, float color[]);
	void dibuja_figura(void* data);

private:
	float cubo[8][3];				// Vectores (x,y,z) para cada vértice.
	float Mcolores[6][3];		// COlores (RGB) para cada cara.
	int Mcaras[6][4] = {		// Indices (4) de vectores que conforman cada cara.
		{0, 1, 2, 3},
		{4, 7, 6, 5},
		{0, 4, 5, 1},
		{1, 2, 6, 5},
		{2, 6, 7, 3},
		{0, 3, 7, 4},
	};
};

#endif // CUBO_H
