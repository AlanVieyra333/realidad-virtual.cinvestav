#ifndef MESH_H
#define MESH_H

#include "figura.h"
#include "spring.h"
#include <vector>

#define BASE_SPRINGS 7
#define MAX_SPRINGS (((BASE_SPRINGS>>1) << RESOLUTION_LEVEL) + 1)		// 25  -> 7 resortes y resolucion 3

using namespace std;

class Mesh : public Figura
{
public:
	Mesh(vector<float> v_start, vector<float>  v_end);
	void dibuja_figura(float t);

private:
	vector<float> v_start, v_end;
	Spring *springs[MAX_SPRINGS];
	int springs_len, current_spring;
	float d_spring;
};

#endif // MESH_H
