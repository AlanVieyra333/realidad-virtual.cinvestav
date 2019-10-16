#ifndef CUBO_H
#define CUBO_H

#include "figura.h"
#include <vector>

using namespace std;

class Cubo : public Figura
{
public:
	Cubo(vector<float> v1, vector<float> v2, float color[]);
	void dibuja_figura(float angle);

private:
	float cubo[8][3]; // Una instacia de un cubo se almacena aquí:
};

#endif // CUBO_H
